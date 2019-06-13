/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <unistd.h>

#include <memory>

#include "modules/drivers/radar/conti_eth_radar/driver/socket_input.h"

namespace apollo {
namespace drivers {
namespace conti_eth_radar {

////////////////////////////////////////////////////////////////////////
// InputSocket class implementation
////////////////////////////////////////////////////////////////////////

/** @brief constructor
 *
 *  @param private_nh private node handle for driver
 *  @param udp_port UDP port number to connect
 */
SocketInput::SocketInput() : sockfd_(-1), port_(0) {}

/** @brief destructor */
SocketInput::~SocketInput(void) { (void)close(sockfd_); }

void SocketInput::init(const int &port) {
  if (sockfd_ != -1) {
    (void)close(sockfd_);
  }

  // connect to conti-ethernet-radar UDP port
  AINFO << "Opening UDP socket: port " << uint16_t(port);
  port_ = port;
  sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);

if (sockfd_ == -1) {
    AERROR << "Init socket failed, UDP port is " << port;
    return;
  }

  sockaddr_in my_addr;                       // my address information
  memset(&my_addr, 0, sizeof(my_addr));      // initialize to zeros
  my_addr.sin_family = AF_INET;              // host byte order
  my_addr.sin_port = htons(uint16_t(port));  // short, in network byte order
  my_addr.sin_addr.s_addr = INADDR_ANY;      // automatically fill in my IP
  // my_addr.sin_addr.s_addr = inet_addr("192.168.1.100");

  if (bind(sockfd_, reinterpret_cast<sockaddr *>(&my_addr), sizeof(sockaddr)) ==
      -1) {
    AERROR << "Failed to bind socket on local address. Port " << port_;
    return;
  }

  if (fcntl(sockfd_, F_SETFL, O_NONBLOCK | FASYNC) < 0) {
    AERROR << "non-block! Port " << port_;
    return;
  }

  AINFO << "Conti-ethernet-radar socket fd is " << sockfd_ << ", port " << port_;
} // SocketInput::init

/** @brief Get one conti-ethernet-radar RDI packet. */
int SocketInput::get_radar_scan_packet(ContiRDI_Packet *pkt) {
  double time1 = apollo::cyber::Time().Now().ToSecond();
  while (true) {
    if (!input_available(POLL_TIMEOUT)) {
      return SOCKET_TIMEOUT;
    }
    // Receive packets that should now be available from the
    // socket using a blocking read.
    uint8_t bytes[MAX_DATA_PACKET_SIZE];
    ssize_t nbytes =
        recvfrom(sockfd_, bytes, MAX_DATA_PACKET_SIZE, 0, nullptr, nullptr);
        // change sockaddr_in from (set to nullptr)

		/*
		print nbytes to check communication status
		*/
		AERROR << "Number of bytes (from-radar): " << nbytes;

    if (nbytes < 0) {
      if (errno != EWOULDBLOCK) {
        AERROR << "recvfail from port " << port_;
        return RECIEVE_FAIL;
      }
    }

    if ((size_t)nbytes == MAX_DATA_PACKET_SIZE) {
      // read successful, done now
      pkt->set_data(bytes, MAX_DATA_PACKET_SIZE);
      break;
    }

    AERROR << "Incomplete Continental-radar data packet read: " << nbytes
           << " bytes from port " << port_;
  }
  double time2 = apollo::cyber::Time().Now().ToSecond();
  pkt->set_stamp(apollo::cyber::Time((time2 + time1) / 2.0).ToNanosecond());

  return 0;
} // SocketInput::get_radar_scan_packet

bool SocketInput::input_available(int timeout) {
  struct pollfd fds[1];
  fds[0].fd = sockfd_;
  fds[0].events = POLLIN;
  // Unfortunately, the Linux kernel recvfrom() implementation
  // uses a non-interruptible sleep() when waiting for data,
  // which would cause this method to hang if the device is not
  // providing data.  We poll() the device first to make sure
  // the recvfrom() will not block.
  //
  // Note, however, that there is a known Linux kernel bug:
  //
  //   Under Linux, select() may report a socket file descriptor
  //   as "ready for reading", while nevertheless a subsequent
  //   read blocks.  This could for example happen when data has
  //   arrived but upon examination has wrong checksum and is
  //   discarded.  There may be other circumstances in which a
  //   file descriptor is spuriously reported as ready.  Thus it
  //   may be safer to use O_NONBLOCK on sockets that should not
  //   block.

  // poll() until input available
  do {
    int retval = poll(fds, 1, POLL_TIMEOUT);

    if (retval < 0) {  // poll() error?
      if (errno != EINTR) {
        AWARN << "Conti-Eth-Radar port " << port_
              << "poll() error: " << strerror(errno);
      }
      return false;
    }

    if (retval == 0) {  // poll() timeout?
      AWARN << "Conti-Eth-Radar port " << port_ << " poll() timeout";
      // AERROR << "Conti-Eth-Radar port " << port_ << " poll() timeout";
      return false;
    }

    if ((fds[0].revents & POLLERR) || (fds[0].revents & POLLHUP) ||
        (fds[0].revents & POLLNVAL)) {  // device error?
      AERROR << "Conti-Eth-Radar port " << port_ << "poll() reports Conti-Eth-Radar error";
      return false;
    }
  } while ((fds[0].revents & POLLIN) == 0);
  return true;
} //  SocketInput::input_available

}  // namespace conti_eth_radar
}  // namespace drivers
}  // namespace apollo

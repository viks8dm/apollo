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

#pragma once

#include <stdio.h>
#include <unistd.h>

#include "modules/drivers/radar/conti_eth_radar/driver/input.h"

namespace apollo {
namespace drivers {
namespace conti_eth_radar {

using apollo::drivers::conti_eth_radar::ContiRDI_Packet;

static const int POLL_TIMEOUT = 1000;  // one second (in msec)

/** @brief Live Continental ethernet radar input from socket. */
class SocketInput : public Input {
 public:
  SocketInput();
  virtual ~SocketInput();
  void init(const int& port) override;
  int get_radar_scan_packet(ContiRDI_Packet* rdi_pkt);

 private:
  int sockfd_;
  int port_;
  bool input_available(int timeout);
};	// SocketInput

}  // namespace conti_eth_radar
}  // namespace drivers
}  // namespace apollo

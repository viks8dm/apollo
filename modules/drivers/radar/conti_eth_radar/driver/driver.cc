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

 #include <cmath>
 #include <ctime>
 #include <string>

 #include "cyber/cyber.h"

 #include "modules/drivers/radar/conti_eth_radar/driver/driver.h"
 #include "modules/drivers/radar/conti_eth_radar/proto/config.pb.h"
 #include "modules/drivers/radar/conti_eth_radar/proto/conti_eth_radar.pb.h"

 namespace apollo {
 namespace drivers {
 namespace conti_eth_radar {

 void ContiEthRadarDriver::Init() {
   input_.reset(new SocketInput());
   input_->init(contiradar_config_.source_port());
 } // ContiEthRadarDriver::Init


bool ContiEthRadarDriver::Poll(const std::shared_ptr<ContiEthRadarScan> &scan) {
	int poll_result = PollByScan(scan);
  std::cout << poll_result;
	if (poll_result == SOCKET_TIMEOUT || poll_result == RECIEVE_FAIL) {
   return false;  // poll again
 }

	if (scan->rdi_pkt_size() <= 0) {
   AINFO << "Getting a empty scan from port: " << contiradar_config_.source_port();
   return false;
 }

	// publish message using time of last packet read
 ADEBUG << "Publishing a full conti_eth_radar scan.";
 scan->mutable_header()->set_timestamp_sec(cyber::Time().Now().ToSecond());
 scan->mutable_header()->set_frame_id(contiradar_config_.frame_id());
 scan->set_model(contiradar_config_.model());

	return true;
} // ContiEthRadarDriver::Poll


int ContiEthRadarDriver::PollByScan(std::shared_ptr<ContiEthRadarScan> scan) {

	while (true) {
    ContiRDI_Packet* packet = scan->add_rdi_pkt();

		int rc = input_ ->get_radar_scan_packet(packet);
		if (rc == 0) {
			break;  // got a full packet?
		} else if (rc < 0) {
			return rc;
		}
	}

	return 0;
} // ContiEthRadarDriver::PollByScan


ContiEthRadarDriver* ContiRadarDriver::CreateDriver(const ContiEthRadarConfig& contiradar_config) {

	ContiEthRadarDriver* driver = nullptr;

	// following setup defined to accommodate future models
	switch (contiradar_config.model()) {
		case ARS430: {
			driver = new ContiEthRadarDriver(contiradar_config);
      break;
			//driver->SetParams()
		}
		default:
      AERROR << "invalid radar-model, must be ARS430";
      break;
	}

	return driver;
} // ContiEthRadarDriver::CreateDriver


 }  // namespace conti_eth_radar
 }  // namespace drivers
 }  // namespace apollo

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

#include <memory>
#include <string>
#include <thread>

#include "cyber/cyber.h"

#include "modules/common/util/message_util.h"
#include "modules/drivers/radar/conti_eth_radar/driver/conti_eth_radar_driver_component.h"

namespace apollo {
namespace drivers {
namespace conti_eth_radar {

bool ContiEthRadarDriverComponent::Init() {
	AINFO << "Conti ethernet radar driver component init";
  ContiEthRadarConfig contiradar_config;
  if (!GetProtoConfig(&contiradar_config)) {
    return false;
  }
  AINFO << "ContiEthRadar config: " << contiradar_config.DebugString();
	// start the driver
  writer_ = node_->CreateWriter<ContiEthRadarScan>(contiradar_config.scan_channel());
  ContiEthRadarDriver *driver = ContiRadarDriver::CreateDriver(contiradar_config);
  if (driver == nullptr) {
    return false;
  }
  dvr_.reset(driver);
  dvr_->Init();
  // spawn device poll thread
  runing_ = true;
  device_thread_ = std::shared_ptr<std::thread>(
      new std::thread(std::bind(&ContiEthRadarDriverComponent::device_poll, this)));
  device_thread_->detach();

  return true;
} // ContiEthRadarDriverComponent::Init

void ContiEthRadarDriverComponent::device_poll() {
  while (!apollo::cyber::IsShutdown()) {
    // poll device until end of file
    std::shared_ptr<ContiEthRadarScan> scan = std::make_shared<ContiEthRadarScan>();
    bool ret = dvr_->Poll(scan);
    if (ret) {
      common::util::FillHeader("conti_eth_radar", scan.get());
      writer_->Write(scan);
    } else {
      AWARN << "device poll failed";
    }
  }

  AERROR << "CompContiEthRadarDriver thread exit";
  runing_ = false;
} // ContiEthRadarDriverComponent::device_poll

}  // namespace conti_eth_radar
}  // namespace drivers
}  // namespace apollo

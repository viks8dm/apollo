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

#include <memory>

#include "cyber/cyber.h"
#include "modules/drivers/radar/conti_eth_radar/driver/socket_input.h"
#include "modules/drivers/radar/conti_eth_radar/proto/config.pb.h"
#include "modules/drivers/radar/conti_eth_radar/proto/conti_eth_radar.pb.h"

namespace apollo {
namespace drivers {
namespace conti_eth_radar {

class ContiEthRadarDriver {
 public:
  explicit ContiEthRadarDriver(const ContiEthRadarConfig &contiradar_config) : contiradar_config_(contiradar_config) {}
  virtual ~ContiEthRadarDriver() {}

  virtual bool Poll(const std::shared_ptr<ContiEthRadarScan> &scan);
  virtual void Init();
	int Port() { return contiradar_config_.source_port(); }



 protected:
   ContiEthRadarConfig contiradar_config_;
   std::shared_ptr<SocketInput> input_ = nullptr;
	 int PollByScan(std::shared_ptr<ContiEthRadarScan> scan);
};	// ContiEthRadarDriver

class ContiRadarDriver {
  public:
    static ContiEthRadarDriver *CreateDriver(const ContiEthRadarConfig &contiradar_config);
};


}  // namespace conti_eth_radar
}  // namespace drivers
}  // namespace apollo

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
/*
Data parser for Continental's high-def radars
Communication is via ethernet port
current parsers available for selected models only

@author Vikalp Mishra (vikalp@baidu.com)
*/


#pragma once

#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <boost/format.hpp>
#include <limits>
#include <memory>
#include <string>

#include "modules/drivers/proto/conti_rdi_radar.pb.h"
#include "modules/drivers/radar/conti_eth_radar/driver/driver.h"
#include "modules/drivers/radar/conti_eth_radar/proto/config.pb.h"
#include "modules/drivers/radar/conti_eth_radar/proto/conti_eth_radar.pb.h"


namespace apollo {
namespace drivers {
namespace conti_eth_radar {

using apollo::drivers::ContiRDI;
using apollo::drivers::ContiEthRadarStatus;
using apollo::drivers::ContiEthRadarDetList;
using apollo::drivers::conti_eth_radar::ContiEthRadarScan;

/*
RDI parameters
*/

// // Radar Struct
// struct RadarRDI {
//   unsigned int num_of_detections;
//
// }; // RadarRDI struct

class ContiEthRadarParser {
 public:
  ContiEthRadarParser() {}
  explicit ContiEthRadarParser(const ContiEthRadarConfig& config);
  virtual ~ContiEthRadarParser() {}

	static ContiEthRadarParser* CreateParser(ContiEthRadarConfig config);

  virtual void GenerateContiRadarDetList(
                    const std::shared_ptr<ContiEthRadarScan>& scan_msg,
                    std::shared_ptr<ContiRDI> rdi_out) = 0;

  // virtual void setup();

};	// ContiEthRadarParser


class ContiEthRadar430Parser : public ContiEthRadarParser {
 public:
  explicit ContiEthRadar430Parser(const ContiEthRadarConfig& config);
  ~ContiEthRadar430Parser() {}

  // void setup() override;


};	// ContiEthRadar430Parser

}  // namespace conti_eth_radar
}  // namespace drivers
}  // namespace apollo

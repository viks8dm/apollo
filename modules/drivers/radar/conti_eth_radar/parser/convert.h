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

 #include <cmath>
 #include <ctime>
 #include <string>

#include "cyber/cyber.h"

#include "modules/drivers/proto/conti_rdi_radar.pb.h"
#include "modules/drivers/radar/conti_eth_radar/parser/conti_eth_radar_parser.h"
#include "modules/drivers/radar/conti_eth_radar/proto/config.pb.h"
#include "modules/drivers/radar/conti_eth_radar/proto/conti_eth_radar.pb.h"

namespace apollo {
namespace drivers {
namespace conti_eth_radar {

  using apollo::drivers::ContiRDI;
  using apollo::drivers::ContiEthRadarStatus;
  using apollo::drivers::ContiEthRadarDetList;
  using apollo::drivers::conti_eth_radar::ContiEthRadarScan;

// convert Conti-radar data to RDI format and republish
class Convert {
 public:
  Convert() = default;
  virtual ~Convert() = default;

	void init(const ContiEthRadarConfig& contiradar_config);

  // convert scan data to radar data structure
  void ConvertPacketsToRDI(const std::shared_ptr<ContiEthRadarScan>& scan_msg,
                            std::shared_ptr<ContiRDI> rdi_out);

private:
  // raw data class for conversion to RDI
	std::unique_ptr<ContiEthRadarParser> parser_;
  // configuration parameter, get from conti_eth_radar_parser.h
	ContiEthRadarConfig config_;

}; // Convert

}  // namespace conti_eth_radar
}  // namespace drivers
}  // namespace apollo

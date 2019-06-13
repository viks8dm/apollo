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

 #include "modules/drivers/radar/conti_eth_radar/driver/driver.h"
#include "modules/drivers/radar/conti_eth_radar/proto/config.pb.h"
#include "modules/drivers/radar/conti_eth_radar/proto/conti_eth_radar.pb.h"


namespace apollo {
namespace drivers {
namespace conti_eth_radar {





}  // namespace conti_eth_radar
}  // namespace drivers
}  // namespace apollo


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
#include <string>
#include <thread>

#include "cyber/cyber.h"

#include "modules/drivers/radar/conti_eth_radar/driver/driver.h"
#include "modules/drivers/radar/conti_eth_radar/proto/config.pb.h"
#include "modules/drivers/radar/conti_eth_radar/proto/conti_eth_radar.pb.h"

namespace apollo {
namespace drivers {
namespace conti_eth_radar {

using apollo::cyber::Component;
using apollo::cyber::Reader;
using apollo::cyber::Writer;
using apollo::drivers::conti_eth_radar::ContiEthRadarScan;

class ContiEthRadarDriverComponent : public Component<> {
    public:
    ~ContiEthRadarDriverComponent() {
        if (device_thread_->joinable()) {
        device_thread_->join();
        }
    }
    bool Init() override;

    private:
        void device_poll();
        volatile bool runing_;
        uint32_t seq_ = 0;
        std::shared_ptr<std::thread> device_thread_;
        std::shared_ptr<ContiEthRadarDriver> dvr_;
        std::shared_ptr<apollo::cyber::Writer<ContiEthRadarScan>> writer_;

}; // ContiEthRadarDriverComponent

CYBER_REGISTER_COMPONENT(ContiEthRadarDriverComponent)

}  // namespace conti_eth_radar
}  // namespace drivers
}  // namespace apollo

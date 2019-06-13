load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "conti_eth_radar_proto",
    deps = [
        ":sensor_conti_eth_radar_proto",
    ],
)

cc_proto_library(
    name = "sensor_conti_eth_radar_proto",
    deps = [
        ":conti_eth_radar_proto_lib",
    ],
)

proto_library(
    name = "conti_eth_radar_proto_lib",
    srcs = [
        "config.proto",
        "conti_eth_radar.proto",
    ],
    deps = [
        "//modules/common/proto:header_proto_lib",
    ],
)

cpplint()

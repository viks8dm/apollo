load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "libconti_eth_radar_driver_component.so",
    linkopts = ["-shared"],
    linkstatic = False,
    deps = [":conti_eth_radar_driver_component_lib"],
)

cc_library(
    name = "conti_eth_radar_driver_component_lib",
    srcs = ["conti_eth_radar_driver_component.cc"],
    hdrs = ["conti_eth_radar_driver_component.h"],
    copts = ['-DMODULE_NAME=\\"conti_eth_radar\\"'],
    deps = [
        "//cyber",
        "//modules/common/util:message_util",
        "//modules/drivers/radar/conti_eth_radar/driver",
    ],
)

cc_library(
    name = "driver",
    srcs = [
        "driver.cc",
        "socket_input.cc",
    ],
    hdrs = [
        "driver.h",
        "input.h",
        "socket_input.h",
    ],
    copts = ['-DMODULE_NAME=\\"conti_eth_radar\\"'],
    linkopts = [
        "-lpcap",
    ],
    deps = [
        "//cyber",
        "//modules/common/util",
        "//modules/drivers/radar/conti_eth_radar/proto:conti_eth_radar_proto",
    ],
)


cpplint()

load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "libconti_eth_radar_convert_component.so",
    linkopts = ["-shared"],
    linkstatic = False,
    deps = [":conti_eth_radar_convert_component_lib"],
)

cc_library(
    name = "conti_eth_radar_convert_component_lib",
    srcs = ["conti_eth_radar_convert_component.cc"],
    hdrs = ["conti_eth_radar_convert_component.h"],
    copts = ['-DMODULE_NAME=\\"conti_eth_radar\\"'],
    deps = [
        "//cyber",
        "//modules/drivers/radar/conti_eth_radar/parser:convert",
    ],
)

cc_library(
    name = "convert",
    srcs = [
        "convert.cc",
        "conti_eth_radar_parser.cc",
    ],
    hdrs = [
        "convert.h",
        "conti_eth_radar_parser.h",
    ],
    copts = ['-DMODULE_NAME=\\"conti_eth_radar\\"'],
    deps = [
        "//cyber",
        "//modules/drivers/proto:sensor_proto",
        "//modules/drivers/radar/conti_eth_radar/proto:conti_eth_radar_proto",
        "//modules/drivers/radar/conti_eth_radar/driver",
        "@eigen",
        "@yaml_cpp//:yaml",
    ],
)

cpplint()

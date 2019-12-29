cc_library(
    name = "libdiff",
    srcs = ["diff.cc"],
    hdrs = ["diff.h"],
    copts = [ "-std=c++17" ],
    visibility = ["//main:__pkg__"],
)

cc_test(
    name = "diff-test",
    srcs = ["diff-test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":libdiff",
    ],
)

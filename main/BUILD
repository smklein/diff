load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "libdiff",
    srcs = ["diff.cc"],
    hdrs = ["diff.h"],
)

cc_binary(
    name = "diff",
    srcs = ["main.cc"],
    deps = [
      ":libdiff",
    ],
)

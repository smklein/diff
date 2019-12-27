cc_library(
    name = "libdiff",
    srcs = ["diff.cc"],
    hdrs = ["diff.h"],
    copts = [ "-std=c++17" ],
)

cc_binary(
    name = "diff",
    srcs = ["main.cc"],
    deps = [
      ":libdiff",
    ],
    copts = [ "-std=c++17" ],
)

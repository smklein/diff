# diff

A simple example of a diff algorithm, implemented in C++.

This example repo utilizes Bazel and Gtest; in addition to an implementation
of a simple BFS diff algorithm, it strives to provides a "minimal working
example" of both the build system and testing libraries with few external
dependendencies.

## Building

Using bazel to build a specific target:

$ bazel build //main:diff

Using bazel to build all targets:

$ bazel build $(bazel query //...)

Shortcut to build everything:

S ./build.sh

## Testing

Using bazel to test a specific target:

$ bazel build //lib:difftest --test_output=errors

Using bazel to build all targets:

$ bazel test $(bazel query //...)

Shortcut to test everything:

$ ./test.sh

## Running

$ ./bazel-bin/main/diff

Shortcut to binary:

$ ./run.sh

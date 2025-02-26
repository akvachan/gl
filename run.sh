#!/bin/sh

set -euxo pipefail

cmake -B Build
cmake --build Build

build/GL

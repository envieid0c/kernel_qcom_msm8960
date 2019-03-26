#!/bin/bash
# by envieiDoc script compiling kernel for Nexu4 (mako)

cpu="nproc --all"

ccache -M 2G

export "ARCH=arm"
export "CROSS_COMPILE=$(pwd)/toolchain/7.4.1/arm-envieidoc_toolchain-linux-gnueabihf/bin/arm-envieidoc_toolchain-linux-gnueabihf-"

export KBUILD_BUILD_USER="envieiDoc"
export KBUILD_BUILD_HOST="macOS"

make clean
make mrproper
make mako_defconfig
make -j`$cpu`
#!/bin/bash
# by envieiDoc script compiling kernel for Nexu4 (mako)

cpu=4
#"nproc --all"
clean="make clean ; make mrproper"
full="make mako_defconfig ; make -j$cpu"
mini="make mako_mini_defconfig ; -j$cpu"
copy="cp arch/arm/boot/zImage"
home="/home/envieidoc/kernel"

export ARCH=arm
#export CROSS_COMPILE=$(pwd)/toolchain/arm-envieiDoc_tc-linux-gnueabihf/bin/arm-envieiDoc_tc-linux-gnueabihf-
export CROSS_COMPILE=/root/GCC/arm-linux-androideabi-4.9/bin/arm-linux-androideabi-

export KBUILD_BUILD_USER="envieiDoc"
export KBUILD_BUILD_HOST="instance-1"

$clean ; $full
$copy Release/full/
$copy $home/full/

$clean ; $mini
$copy Release/mini/
$copy $home/mini/

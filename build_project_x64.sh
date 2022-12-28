#!/bin/bash

CC=g++
LD=g++
BIN_PATH="bin"
LIB_PATH="3rdparty/lib"
CFLAGS="-O2 -std=c++17"
CFLAGS_DEBUG="-Og -g -std=c++17"

mkdir -p $BIN_PATH
mkdir -p $BIN_PATH/assets

build_release() {
	$CC $CFLAGS -L$LIB_PATH -I3rdparty/include src/*.cpp -o $BIN_PATH/app -lsgg -lGL -lGLEW -lSDL2 -lSDL2_mixer -lfreetype -lstdc++fs
}

run_release() {
	cd bin
	./app
}

build_debug() {
	$CC $CFLAGS_DEBUG -L$LIB_PATH -I3rdparty/include src/*.cpp -o $BIN_PATH/appd -lsggd -lGL -lGLEW -lSDL2 -lSDL2_mixer -lfreetype -lstdc++fs
}

run_debug() {
	cd bin
	./appd
}

while getopts "rd" OPTION; do
	case $OPTION in

		r)
			build_release
			run_release
			;;

		d)
			build_debug
			run_debug
			;;
	esac
done

#!/bin/sh

ABSOLUTE_PATH=`which "$0"`
ABSOLUTE_BOOTSTRAP_PATH=`dirname "$ABSOLUTE_PATH"`
PREFIX=`dirname "$ABSOLUTE_BOOTSTRAP_PATH"`
mkdir -p "$PREFIX/bin"
g++ -std=c++11 "$ABSOLUTE_BOOTSTRAP_PATH/"*.cpp -o "$PREFIX/bin/mutinyc"

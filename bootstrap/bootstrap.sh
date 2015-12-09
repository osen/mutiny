#!/bin/sh

CURRENT_PATH=`pwd`
ABSOLUTE_PATH=`which "$0"`
ABSOLUTE_BOOTSTRAP_PATH=`dirname "$ABSOLUTE_PATH"`
cd "$ABSOLUTE_BOOTSTRAP_PATH"
cd ..
PREFIX=`pwd`
cd "$CURRENT_PATH"
mkdir -p "$PREFIX/bin"

g++ -g "$ABSOLUTE_BOOTSTRAP_PATH/"*.cpp -o "$PREFIX/bin/mutt"


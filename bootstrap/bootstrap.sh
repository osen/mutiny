#!/bin/sh

CURRENT_PATH=`pwd`
ABSOLUTE_PATH=`which "$0"`
ABSOLUTE_BOOTSTRAP_PATH=`dirname "$ABSOLUTE_PATH"`
cd "$ABSOLUTE_BOOTSTRAP_PATH"
cd ..
PREFIX=`pwd`
cd "$CURRENT_PATH"
mkdir -p "$PREFIX/bin"

which g++

if [ $? = 0 ]; then
  g++ -g "$ABSOLUTE_BOOTSTRAP_PATH/src/"*.cpp -o "$PREFIX/bin/mutt"
  exit
fi

which clang++

if [ $? = 0 ]; then
  clang++ -g "$ABSOLUTE_BOOTSTRAP_PATH/src/"*.cpp -o "$PREFIX/bin/mutt"
  exit
fi

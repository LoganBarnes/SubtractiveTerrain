#!/bin/bash

RUN_DIR=$(pwd)

if [[ ! -d _build ]];
  then
  mkdir _build;
fi;

cd _build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$RUN_DIR ../..
make -j12
cd ..

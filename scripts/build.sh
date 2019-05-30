#!/usr/bin/env bash

mkdir -p build
cd src
eosio-cpp stats.cpp -o ../build/stats.wasm -abigen -I ../include -R ../resources

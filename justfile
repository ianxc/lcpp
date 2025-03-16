#!/usr/bin/env just --justfile

list:
  @ls -1 build/bin

conf:
  @cmake -B build -S .

build:
  @cmake --build build

run TARGET:
  @build/bin/{{TARGET}}

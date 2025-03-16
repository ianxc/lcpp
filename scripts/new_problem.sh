#!/usr/bin/env bash

set -e # exit on error
set -C # noclobber

if [ $# -lt 2 ]; then
    echo "Usage: $0 <problem-number> <problem-name>"
    echo "Example: $0 100 'Same Tree'"
    exit 1
fi

P_NUM=$1
P_NAME=$2

P_NAME_FMT=$(echo "$P_NAME" | tr ' ' '-')
P_ID="${P_NUM}-${P_NAME_FMT}"

P_SRC_DIR="src/${P_ID}"
P_TEST_DIR="test/${P_ID}"

mkdir -p P_SRC_DIR
mkdir -p P_TEST_DIR

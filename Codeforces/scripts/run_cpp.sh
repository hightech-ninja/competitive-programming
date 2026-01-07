#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

STDIN=${STDIN:-false}
HACK=${HACK:-false}

read -p "Enter task: " task;

FILE="/dev/stdin"
MSG=""
if [ "$STDIN" = "false" ] || [ "$STDIN" = "0" ]; then
    HACK="true"
    FILE="$task.in.txt"
else
    MSG="Reading input from stdin:"
fi

echo "Hack: $HACK"
if [ "$MSG" != "" ]; then
    echo "$MSG"
fi

CXXFLAGS="$CXXFLAGS -DDEBUG -g -fsanitize=address,undefined -fno-omit-frame-pointer -O1"
if [ "$HACK" = "true" ] || [ "$HACK" = "1" ]; then
    CXXFLAGS="$CXXFLAGS -DHACK"
fi

$CXX $CXXFLAGS $task.cpp -o $task.out
./$task.out < $FILE

$SCRIPT_DIR/clean_cpp.sh
exit 0

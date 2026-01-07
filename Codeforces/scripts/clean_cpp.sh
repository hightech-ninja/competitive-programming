#!/usr/bin/env bash

set -euo pipefail

RUN_DIR="$(pwd)"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

rm -rf ${RUN_DIR}/*.out ${RUN_DIR}/*.out.*

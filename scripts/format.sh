#!/bin/bash

# Navigate to the repository root
cd "$(dirname "$0")/.." || exit 2

# Set the clang-format binary (defaults to 'clang-format')
CLANG_FORMAT_BIN="${CLANG_FORMAT_BIN:-clang-format}"

# Find and format all .hpp and .cpp files in the src directory
find ./src \( -iname '*.hpp' -o -iname '*.cpp' \) -print0 |
  xargs -0 "$CLANG_FORMAT_BIN" -i || {
    echo "Error: clang-format failed." >&2
    exit 1
  }

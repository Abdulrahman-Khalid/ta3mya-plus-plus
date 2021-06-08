#!/bin/bash -e

find tests/should-pass/ | grep '\.ta3$' | xargs -I{} bash -c "./src/ta3myac --only-symbol-table {} >{}sm 2>{}.symtable"
find tests/should-pass/ | grep '\.ta3$' | xargs -I{} bash -c "./src/ta3myac {} >{}sm 2>/dev/null"

find tests/should-fail/ | grep '\.ta3$' | xargs -I{} bash -c "./src/ta3myac {} 2>{}sm"

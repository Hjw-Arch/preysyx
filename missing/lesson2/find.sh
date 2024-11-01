#! /bin/bash

find ./ -type f -printf '%T@ %p\n' | sort -n | tail -n 10 | awk '{ print strftime("%Y-%m-%d %H:%M:%S", $1), $2 }'

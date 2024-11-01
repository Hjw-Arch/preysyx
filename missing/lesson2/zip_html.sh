#! /bin/bash
find ./ -type f -name "*.html" -print0 | xargs -0 zip output.zip

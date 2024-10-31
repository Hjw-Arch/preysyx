#! /bin/bash

cp -r ./exercises$1 ./exercises$2

cd exercises$2
make clean
mv ex$1.c ex$2.c

sed -i "s/ex$1/ex$2/g" Makefile

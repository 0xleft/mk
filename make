#!/bin/bash

if [ -z "$1" ]; then
    # build clean and then make
    make clean
    make
fi

if [ "$1" == "run" ]; then
    make run
fi

if [ "$1" == "test" ]; then
    cd tests
    make clean
    make run
    cd ..
fi
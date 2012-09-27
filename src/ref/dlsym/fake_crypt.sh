#!/bin/bash

# We have a program, ./target, which calls crypt(3). We intend to interpose
# our fake crypt() call which we've put in ./libfake_crypt.so. This function
# calls out to the real crypt(3) with dlsym. This shell script handles
# interposition with the LD_PRELOAD environment variable.

# When LD_PRELOAD is set, the loader will attempt to load libraries listed in
# it before anything else.

LD_PRELOAD=./libfake_crypt.so ./target

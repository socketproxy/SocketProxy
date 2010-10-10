#!/usr/bin/bash

###
# socketproxy/src/scripts/test_nc2.sh
# (c) 2010 Mike Doyle
#

cd /home/ferrous/projects/socketproxy/build/

for port in 50022 50023
do
    ./soxprox \
        --agent="ssh ferrous@localhost /home/ferrous/projects/socketproxy/build/soxprox-agent" \
        --client="nc -vz 209.126.200.67 $port"
done 2>&1 | grep -v Killed

#!/bin/bash

cd $(dirname $0)

ts_list=$(ls translations/*.ts)

for ts in $ts_list
do
    echo "process $ts\n"
    lupdate -no-obsolete src.pro -ts "$ts"
done

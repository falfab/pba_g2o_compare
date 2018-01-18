#!/bin/bash
directory_name=$1

pushd inputs/$directory_name
for file in *.txt
do
    pushd ../../pba/bin/
    ./pba_driver ../../inputs/$directory_name/$file
    popd
    pushd ../../g2o_ba/bin/
    ./g2o_driver ../../inputs/$directory_name/$file
    popd
done

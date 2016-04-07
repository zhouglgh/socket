#!/bin/bash

counts=$1

while [ $counts -gt 0 ];
do
echo $counts
./client  10.166.15.134&
let counts=$counts-1
done

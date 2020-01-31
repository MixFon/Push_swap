#!/bin/bash

for ((i = 1; i < $1; i++))
do
ARG=`ruby -e "puts (1..5).to_a.shuffle.join(' ')"`
./push_swap $ARG | wc -l
echo $ARG
done > temp.txt

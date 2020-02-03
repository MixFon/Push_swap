#!/bin/bash
for ((i = 1; i < $3; i++))
do
ARG=`ruby -e "puts ($1..$2).to_a.shuffle.join(' ')"`
./push_swap $ARG | ./checker $ARG
done

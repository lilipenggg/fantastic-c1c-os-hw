#!/bin/sh

#  HW6.sh
#  
#
#  Created by Lili Peng on 12/3/17.
#  

for input in 1 2 5 10 20 30 40 50 60 70 80 90 100;
do
    for ((counter = 0; counter < 5; counter++));
    do
        ./HW6 $input;
    done
done

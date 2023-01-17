#!/bin/bash


for i in $(ls players)
do 
    x='s'
    if [ -d ./players/$i ]; then
        for j in $(ls ./players/$i)
        do
            if [ -d ./players/$i/$j ]; then
                ls ./players/$i/$j | while read k
                do
                    head -n2 "./players/$i/$j/$k" | tail -n1 | while read x; do
                        echo $x
                        #mkdir ./players/$x 
                    done
                    
                done
            else 
                echo $j
            fi
        done
    fi
done


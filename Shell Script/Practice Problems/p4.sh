#!/bin/bash

for i in $(ls)
do 
    if [[ -d $i ]] ; then
    for j in $(ls $i)
    do
        if [[ -d $i/$j ]] ; then
            chmod +x "$i/$j/$j.sh"
            #x=$(./$i/$j/$j.sh | diff AcceptedOutput.txt - | wc --lines) 
            #if [[ $x -ne 0 ]] ; then 
            #echo $(( x/2 - 1)) 
            #fi
            ./$i/$j/$j.sh | diff -U 0 -w AcceptedOutput.txt - | grep -v ^@ | wc -l
            
        fi
    done
    fi
done

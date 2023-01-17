#!/bin/bash


# cp src dest -i -r    ======= mv srcfile destdir

# rm -i / -r / -v /-f $filename

if [[ $# -ne 0 ]] ; then
    echo "NO ARGUMENT"
fi

for i in $(ls)
do 
    if [[ -f $i ]] ; then
        echo $i
    fi
done
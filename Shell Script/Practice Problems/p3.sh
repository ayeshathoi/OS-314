#!/bin/bash

for i in $(ls)
do 
	if echo $i | grep --color -q [0-9]
	then
		rm -i $i
	fi
done
	

#!/bin/bash

read input
read pattern 

for i in $(ls)
do 
	if file $i | grep -q text$; then
		if [[ (( $(wc --lines < $i) -ge $input )) ]]
		then
			if  head -n $input $i | tail -n 1 | grep --color $pattern ; then
				rm -i $i
			fi
		fi
		
    		
	else
    		echo not tfile
	fi

	
done
	

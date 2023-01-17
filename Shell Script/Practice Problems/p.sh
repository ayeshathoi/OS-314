#!/bin/bash

if [[ $# -lt 1 ]] ; then
	echo "sad"
fi

for i in $*
do 
	if [[ -f $i ]] ; then
		if [[ -x $i ]]  ; then
		echo "$i is currently executable"
		ls -l $i
		chmod -x $i
		else 
			echo "$i is not executable"
			ls -l $i
		fi
	fi
done



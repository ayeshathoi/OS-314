#!/bin/bash

directory()
{
     echo $1
    for i in $(ls $1)
    do
        if [[ -d $1/$i ]] 
        then 
            #echo $i
          directory $1/$i
        fi
        
        if [[ -x $1/$i ]]
        then
            chmod +x $1/$i
            $1/$i
        fi
    done
}

directory "./Submissions"

#!/bin/bash

if [[ $# -lt 1 ]] ; then
	input=100
    maxID=5

elif [[ $# -lt 2 ]]; then
    input=$1
    maxID=5
else input=$1; maxID=$2
fi

if(($maxID>9))
then
    echo max student = 9 
    maxID=9
fi

myArray=()
studentid=()

start=1805121


for ((i=0;i<maxID;i++))
do
studentid[$i]=$start
start=$((start+1))
myArray[$i]=0
done


extraCompare()
{
    if [[ ! -d $1 ]]
    then
    	return
    fi
    
    for i in $(ls $1)
    do
        for ((j=0;j<maxID;j++))
        do
            if [ -d $1/$i ]; then
                if [[ "$i" = "${studentid[j]}" ]];then
                for k in $(ls $1/$i)
                do
                    if [[ ${k##*.} = "sh" && "${k%%*.}"="$i" ]]
                    then

                        g=${k%%.*}
                        df=$((g-1805121))
                        
                        if(($df>=0 && $df<10))
                        then
                        chmod +x $1/$i/$k
                        cp $1/$i/$k temp_1805062_${k%%.*}.txt

                        x=$($1/$i/$k | diff -w AcceptedOutput.txt -| grep -c '>\|<'  )

                        if (($x != 0)) ; then
                        myArray[$df]=$((input - 5*x ))

                        if ((${myArray[$df]} < 0))
                        then
                            myArray[$df]=0
                        fi

                        elif (( $x==0 ))
                        then
                            myArray[$df]=$input
                        fi
                        fi
                fi
                done
            fi
            fi
        done
    done
}

intraCompare(){
for i in $(ls)
do
    if file $i | grep -q temp_1805062_; then
    for j in $(ls)
    do
    if file $j | grep -q temp_; then
        if [[ "$i" != "$j" ]];then
            x=$(diff -w $i $j | grep -c '>\|<' )
            if (($x == 0))
            then

            f=${j##*temp_1805062_}
            g=${f%%.*}
            df=$((g-1805121))

            if(($df>=0 && $df<10))
            then
            marks=${myArray[$df]}
            if(($marks>0)) 
            then
                myArray[$df]=$((marks*-1))
            fi
            fi

            fi
            
        fi
    fi
    done
    fi
done
}

remove()
{
for i in $(ls)
do
    if file $i | grep -q temp_; then
        rm $i
    fi
done
}


save()
{
>output.csv
x="student_id"
y="score"
str=$x","$y
echo $str >> output.csv

for i in ${!studentid[@]}; do
    x=${studentid[$i]}
    y=${myArray[$i]}
    str=$x","$y
    echo $str >> output.csv
done

}



extraCompare "./Submissions"
intraCompare "."
remove "."
save


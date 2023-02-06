#!/bin/bash
#./cooking_runner.sh #number_of_iteration
echo "Running CV"
echo ""
RANDOM=$$
MAXCHAIR=5
MAXCUSTOMER=5
for (( i = 1; i <= $1; i++))
do
    chair=$(($RANDOM % $MAXCHAIR + 1))
    customer=$(($RANDOM % $MAXCUSTOMER + 1))
    echo -en "\rAttempt $i/$1"
    ./test-barber-shop-CV.sh $customer $chair > output
    X=$(awk -f check.awk CHAIR=$chair CUSTOMER=$customer output)
    if [[ $X != 'OK. All test cases passed!' ]]
    then
    	echo $X
        exit
    fi
done
echo ""
echo "CV DONE"

echo "Running ZEMA"
echo ""
for (( i = 1; i <= $1; i++))
do
    chair=$(($RANDOM % $MAXCHAIR + 1))
    customer=$(($RANDOM % $MAXCUSTOMER + 1))
    echo -en "\rAttempt $i/$1"
    ./test-barber-shop-zemaphore.sh $customer $chair > output
    X=$(awk -f check.awk CHAIR=$chair CUSTOMER=$customer output)
    if [[ $X != 'OK. All test cases passed!' ]]
    then
    	echo $X
        exit
    fi
done
echo ""
echo "ZEMA DONE"

touch output
rm output

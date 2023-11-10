#!/bin/bash
fitxer=$1
shift
iteracions=$1
shift
gcc -fopenmp -o codi $fitxer
avg=0;

for tamany in $@
do
    echo -ne "$tamany""x""$tamany, "
done
echo ""

for (( c=1; c<=$iteracions; c++ ))
do
    for tamany in $@
    do
        res=$(./codi $tamany)
        echo -ne "$res, "
    done
    echo ""
done
rm codi

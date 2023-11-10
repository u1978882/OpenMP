#!/bin/bash
iteracions=$1
shift

for file in $(ls *.c)
do
    filename="${file%%.*}"
    ./csv.sh $(echo $file $iteracions $@) > "csv/$filename.csv"
    echo " - Acavat $filename"
done

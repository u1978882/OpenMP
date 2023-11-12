#!/bin/bash
iteracions=$1
shift

for file in $(ls *.c)
do
    filename="${file%%.*}"
    echo -ne " - Executant $filename"
    ./csv.sh $(echo $file $iteracions $@) > "csv/$filename.csv"
    echo -e " - \033[1;32mFinalitzat\033[0m"
done
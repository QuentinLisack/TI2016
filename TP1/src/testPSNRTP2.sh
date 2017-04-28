#!/bin/bash
path1=$1
path2=$2

mkdir -p $path2
mkdir -p ${path2}TP2

echo ""
echo "TP2 time et psnr"

echo "PSNR : " > ${path2}PSNRTP2.txt

for file in $path1*
do
    file=${file#$path1}
    echo $file
    ./testPSNRTP2 ${path1}${file} >> ${path2}PSNRTP2.txt
done

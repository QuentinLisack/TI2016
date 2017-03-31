#!/bin/bash
path1=$1
path2=$2

mkdir -p $path2
mkdir -p ${path2}Lissage

echo "Execution time : " > ${path2}execTimeLissage.txt

echo ""
echo "Lissage"

array=(0.5 1 3 5 7 10)
maskSize=0

for sigma in "${array[@]}"
do
    echo "" >> ${path2}execTimeLissage.txt
    echo "Sigma = $sigma" >> ${path2}execTimeLissage.txt
    for file in ${path1}*
    do
        file=${file#$path1}
        echo $file
        ./testconv ${path1}${file} ${path2}Lissage/conv_${sigma}_${file} $sigma $maskSize >> ${path2}execTimeLissage.txt
        ./testGaussienne ${path1}${file} ${path2}Lissage/FFT_${sigma}_${file} $sigma >> ${path2}execTimeLissage.txt
    done
done

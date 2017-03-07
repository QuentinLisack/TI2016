#!/bin/bash
path1=$1
path2=$2

for file in $path1*
do
    file=${file#$path1}
    echo $file
    ./testDOG ${path1}${file} ${path2}Detection/DOG_${file}
    ./testGaussienne ${path1}${file} ${path2}Lissage/FFT_${file}
    ./testIdealFilter ${path1}${file} ${path2}Detection/idealFilter_${file}
    ./testLoG ${path1}${file} ${path2}Detection/LoG_${file}
    ./testcont ${path1}${file} ${path2}Detection/contGrad_${file}
    ./testconv ${path1}${file} ${path2}Lissage/conv_${file}
done

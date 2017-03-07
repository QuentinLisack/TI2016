#!/bin/bash
path1=$1
path2=$2

for file in $path1*
do
    file=${file#$path1}
    echo $file
    echo ${path1}${file}
    echo ${path2}DOG_${file}
    ./testDOG ${path1}${file} ${path2}DOG_${file}
    ./testGaussienne ${path1}${file} ${path2}lissageFFT_${file}
    ./testIdealFilter ${path1}${file} ${path2}idealFilter_${file}
    ./testLoG ${path1}${file} ${path2}LoG_${file}
done

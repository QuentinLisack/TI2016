#!/bin/bash
path1=$1
path2=$2

for file in $path1*
do
    file=${file#$path1}
    echo $file
    echo ${path1}${file}
    echo ${path2}DOG_${file}
    ./testDOG.c ${path1}${file} ${path2}DOG_${file}
    ./testGaussienne.c ${path1}${file} ${path2}lissageFFT_${file}
    ./testIdealFilter.c ${path1}${file} ${path2}idealFilter_${file}
    ./testLoG.c ${path1}${file} ${path2}LoG_${file}
done

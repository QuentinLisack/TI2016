#!/bin/bash
path1=$1
path2=$2

mkdir -p $path2
mkdir -p ${path2}Detection

echo ""
echo "Detection de contours"

for file in $path1*
do
    file=${file#$path1}
    echo $file
    ./testDOG ${path1}${file} ${path2}Detection/DOG_${file}
    ./testIdealFilter ${path1}${file} ${path2}Detection/idealFilter_${file}
    ./testLoG ${path1}${file} ${path2}Detection/LoG_${file}
    ./testContSobel ${path1}${file} ${path2}Detection/contSobel_${file}
    ./testContPrewitt ${path1}${file} ${path2}Detection/contPrewitt_${file}
done

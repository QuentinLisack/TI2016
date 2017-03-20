#!/bin/bash
path1=$1
path2=$2

echo "PSNR : " > ${path2}PSNR.txt
echo "Execution time : " > ${path2}execTimeLissage.txt

echo ""
echo "Lissage"

array=(1 3 5 7 10)

for sigma in "${array[@]}"
do
    echo "" >> ${path2}PSNR.txt
    echo "sigma = $sigma" >> ${path2}PSNR.txt
    for file in $path1*
    do
        file=${file#$path1}
        echo $file
        ./testconv ${path1}${file} ${path2}Lissage/conv_${sigma}_${file} $sigma >> ${path2}execTimeLissage.txt
        ./testGaussienne ${path1}${file} ${path2}Lissage/FFT_${sigma}_${file} $sigma >> ${path2}execTimeLissage.txt
        ./testPSNR ${path1}$file $sigma >> ${path2}PSNR.txt
    done
done

echo "Execution time : " > ${path2}execTimeDetection.txt

echo ""
echo "Detection de contours"

for file in $path1*
do
    file=${file#$path1}
    echo $file
    ./testDOG ${path1}${file} ${path2}Detection/DOG_${file} >> ${path2}execTimeDetection.txt
    ./testIdealFilter ${path1}${file} ${path2}Detection/idealFilter_${file} >> ${path2}execTimeDetection.txt
    ./testLoG ${path1}${file} ${path2}Detection/LoG_${file} >> ${path2}execTimeDetection.txt
    ./testContSobel ${path1}${file} ${path2}Detection/contSobel_${file} >> ${path2}execTimeDetection.txt
    ./testContPrewitt ${path1}${file} ${path2}Detection/contPrewitt_${file} >> ${path2}execTimeDetection.txt
done

echo ""
echo "Lissage et detection de contours"

for file in ${path2}Lissage/*
do
    file=${file#${path2}Lissage/}
    echo $file
    ./testDOG ${path2}Lissage/${file} ${path2}Lissage_et_detection/DOG_${file} > /dev/null
    ./testIdealFilter ${path2}Lissage/${file} ${path2}Lissage_et_detection/idealFilter_${file} > /dev/null
    ./testLoG ${path2}Lissage/${file} ${path2}Lissage_et_detection/LoG_${file} > /dev/null
    ./testContSobel ${path2}Lissage/${file} ${path2}Lissage_et_detection/contSobel_${file} > /dev/null
    ./testContPrewitt ${path2}Lissage/${file} ${path2}Lissage_et_detection/contPrewitt_${file} > /dev/null
done

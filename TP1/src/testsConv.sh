#!/bin/bash
path1=$1
path2=$2

mkdir -p $path2
mkdir -p ${path2}Lissage

echo "PSNR : " > ${path2}PSNRConv.txt

echo ""
echo "Lissage par convolution"

arraySigma=(0.5 1 3 5 7 10)
arrayMaskSize=(1 2 5)

for sigma in "${arraySigma[@]}"
do
    for maskSize in "${arrayMaskSize[@]}"
    do
        echo "" >> ${path2}PSNRConv.txt
        echo "sigma = $sigma" >> ${path2}PSNRConv.txt
        echo "masksize = $maskSize" >> ${path2}PSNRConv.txt
        for file in ${path1}formes1*
        do
            file=${file#$path1}
            echo $file
            ./testPSNR ${path1}$file $sigma $maskSize >> ${path2}PSNRConv.txt
        done
        for file in ${path1}formes2*
        do
            file=${file#$path1}
            echo $file
            ./testPSNR ${path1}$file $sigma $maskSize >> ${path2}PSNRConv.txt
        done
        for file in ${path1}globulesb*
        do
            file=${file#$path1}
            echo $file
            ./testPSNR ${path1}$file $sigma $maskSize >> ${path2}PSNRConv.txt
        done
    done
done

#!/bin/bash
path1=$1
path2=$2

mkdir -p $path2
mkdir -p ${path2}Lissage

echo "PSNR : " > ${path2}PSNRFFT.txt

echo ""
echo "Lissage par FFT"

arraySigma=(0.5 1 3 5 7 10)


for file in ${path1}formes1*
do
    echo "" >> ${path2}PSNRFFT.txt  
    for sigma in "${arraySigma[@]}"
    do
        file=${file#$path1}
        echo $file
        ./testGaussienne ${path1}${file} ${path2}Lissage/FFT_${sigma}_${file} $sigma >> /dev/null
        ./testPSNRFFT ${path1}$file $path1/formes1.pgm $sigma >> ${path2}PSNRFFT.txt
    done
done
for file in ${path1}formes2*
do
    echo "" >> ${path2}PSNRFFT.txt
    for sigma in "${arraySigma[@]}"
    do
        file=${file#$path1}
        echo $file
        ./testGaussienne ${path1}${file} ${path2}Lissage/FFT_${sigma}_${file} $sigma >> /dev/null
        ./testPSNRFFT ${path1}$file $path1/formes2.pgm $sigma >> ${path2}PSNRFFT.txt
    done
done
for file in ${path1}globulesb*
do
    echo "" >> ${path2}PSNRFFT.txt
    for sigma in "${arraySigma[@]}"
    do
        file=${file#$path1}
        echo $file
        ./testGaussienne ${path1}${file} ${path2}Lissage/FFT_${sigma}_${file} $sigma >> /dev/null
        ./testPSNRFFT ${path1}$file $path1/globules.pgm $sigma >> ${path2}PSNRFFT.txt
    done
done

CFLAGS=-c -g -std=gnu99
LDFLAGS=-lm

TP1:testGaussienne testconv testContSobel testContPrewitt testDOG testLoG testIdealFilter testPSNR testPSNRFFT testMedianFilter testAdaptativeRecursiveFilter testBilateralFilter

testGaussienne: testGaussienne.o pgm.o libFT.o fft.o
	gcc $^ $(LDFLAGS) -o $@
	
testDOG: testDOG.o pgm.o libFT.o fft.o
	gcc $^ $(LDFLAGS) -o $@
	
testIdealFilter: testIdealFilter.o pgm.o libFT.o fft.o contourExtract.o
	gcc $^ $(LDFLAGS) -o $@
	
testLoG: testLoG.o pgm.o libFT.o fft.o contourExtract.o
	gcc $^ $(LDFLAGS) -o $@
	
testconv: testconv.o pgm.o convolution.o
	gcc $^ $(LDFLAGS) -o $@
	
testContSobel: testContSobel.o pgm.o contourGradient.o convolution.o
	gcc $^ $(LDFLAGS) -o $@
	
testContPrewitt: testContPrewitt.o pgm.o contourGradient.o convolution.o
	gcc $^ $(LDFLAGS) -o $@
	
testPSNR: testPSNR.o pgm.o libFT.o convolution.o fft.o divers.o
	gcc $^ $(LDFLAGS) -o $@
	
testPSNRFFT: testPSNRFFT.o pgm.o libFT.o convolution.o fft.o divers.o
	gcc $^ $(LDFLAGS) -o $@
	
testMedianFilter: testMedianFilter.o pgm.o medianFilter.o
	gcc $^ $(LDFLAGS) -o $@
	
testAdaptativeRecursiveFilter: testAdaptativeRecursiveFilter.o pgm.o adaptativeRecursiveFilter.o
	gcc $^ $(LDFLAGS) -o $@
	
testBilateralFilter: testBilateralFilter.o pgm.o bilateralFilter.o
	gcc $^ $(LDFLAGS) -o $@

%.o:%.c
	gcc $(CFLAGS) $<
	
clean:
	rm -f testGaussienne testDOG testIdealFilter testLoG testconv testContPrewitt testContSobel testPSNRFFT testPSNR testMedianFilter testAdaptativeRecursiveFilter testBilateralFilter *.o

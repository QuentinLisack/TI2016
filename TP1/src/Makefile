CFLAGS=-c -g -std=gnu99
LDFLAGS=-lm

all:testGaussienne essai1 essai2 testconv testcont testDOG testLoG testIdealFilter

testGaussienne: testGaussienne.o pgm.o libFT.o fft.o
	gcc $^ $(LDFLAGS) -o $@
	
testDOG: testDOG.o pgm.o libFT.o fft.o
	gcc $^ $(LDFLAGS) -o $@
	
testIdealFilter: testIdealFilter.o pgm.o libFT.o fft.o contourExtract.o
	gcc $^ $(LDFLAGS) -o $@
	
testLoG: testLoG.o pgm.o libFT.o fft.o
	gcc $^ $(LDFLAGS) -o $@

essai1: essai1.o pgm.o
	gcc $^ $(LDFLAGS) -o $@

essai2: essai2.o pgm.o fft.o
	gcc $^ $(LDFLAGS) -o $@
	
testconv: testconv.o pgm.o convolution.o
	gcc $^ $(LDFLAGS) -o $@
	
testcont: testContGrad.o pgm.o contourGradient.o convolution.o
	gcc $^ $(LDFLAGS) -o $@

%.o:%.c
	gcc $(CFLAGS) $<

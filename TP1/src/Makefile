CFLAGS=-c -g -std=gnu99
LDFLAGS=-lm

all:testGaussienne testconv testcont testDOG testLoG testIdealFilter testGlobal

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
	
testcont: testContGrad.o pgm.o contourGradient.o convolution.o
	gcc $^ $(LDFLAGS) -o $@
	
testGlobal: testGlobal.o pgm.o libFT.o fft.o contourExtract.o
	gcc $^ $(LDFLAGS) -o $@

%.o:%.c
	gcc $(CFLAGS) $<
	
clean:
	rm -f testGaussienne testDOG testIdealFilter testLoG testconv testcont testGlobal *.o

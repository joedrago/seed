SRCS=main.o MurmurHash3.o generateData.o

all: seed

.cpp.o:
	gcc $(CPPFLAGS) -c $<

seed: $(SRCS)
	gcc -o seed $(SRCS) -lstdc++

clean:
	rm -rf seed $(SRCS) data1 data2 compress*

run:
	@echo Generating into data1 and data2 with the same seeds...
	@mkdir -p data1
	@./seed 5 1048576 1 data1/5.bin && hexdump -C -v data1/5.bin > data1/5.asc && rm data1/5.bin
	@./seed 6 1048576 1 data1/6.bin && hexdump -C -v data1/6.bin > data1/6.asc && rm data1/6.bin
	@./seed 7 1048576 1 data1/7.bin && hexdump -C -v data1/7.bin > data1/7.asc && rm data1/7.bin
	@./seed 8 1048576 1 data1/8.bin && hexdump -C -v data1/8.bin > data1/8.asc && rm data1/8.bin
	@./seed 9 1048576 1 data1/9.bin && hexdump -C -v data1/9.bin > data1/9.asc && rm data1/9.bin
	@mkdir -p data2
	@./seed 5 1048576 1 data2/5.bin && hexdump -C -v data2/5.bin > data2/5.asc && rm data2/5.bin
	@./seed 6 1048576 1 data2/6.bin && hexdump -C -v data2/6.bin > data2/6.asc && rm data2/6.bin
	@./seed 7 1048576 1 data2/7.bin && hexdump -C -v data2/7.bin > data2/7.asc && rm data2/7.bin
	@./seed 8 1048576 1 data2/8.bin && hexdump -C -v data2/8.bin > data2/8.asc && rm data2/8.bin
	@./seed 9 1048576 1 data2/9.bin && hexdump -C -v data2/9.bin > data2/9.asc && rm data2/9.bin
	@echo There should be no differences listed between the lines below:
	@echo -------------------------------------------------------------------------------------
	@diff -u data1 data2
	@echo -------------------------------------------------------------------------------------
	@echo try running: meld data1 data2
	@echo Generating data with differing compression expectations...
	@./seed 1 1048576 1 compress_1low.bin && gzip compress_1low.bin
	@./seed 1 1048576 5 compress_2med.bin && gzip compress_2med.bin
	@./seed 1 1048576 10 compress_3high.bin && gzip compress_3high.bin
	@ls -l compress*


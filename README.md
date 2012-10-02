git clone https://github.com/joedrago/seed.git
cd seed
make clean all run

should output:

Generating into data1 and data2 with the same seeds...
[5] Generating 1048576 bytes to data1/5.bin
[6] Generating 1048576 bytes to data1/6.bin
[7] Generating 1048576 bytes to data1/7.bin
[8] Generating 1048576 bytes to data1/8.bin
[9] Generating 1048576 bytes to data1/9.bin
[5] Generating 1048576 bytes to data2/5.bin
[6] Generating 1048576 bytes to data2/6.bin
[7] Generating 1048576 bytes to data2/7.bin
[8] Generating 1048576 bytes to data2/8.bin
[9] Generating 1048576 bytes to data2/9.bin
There should be no differences listed between the lines below:
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
try running: meld data1 data2
Generating data with differing compression expectations...
[1] Generating 1048576 bytes to compress_1low.bin
[1] Generating 1048576 bytes to compress_2med.bin
[1] Generating 1048576 bytes to compress_3high.bin
-rw-rw-r-- 1 joe joe 1048772 Oct  2 16:18 compress_1low.bin.gz
-rw-rw-r-- 1 joe joe  231098 Oct  2 16:18 compress_2med.bin.gz
-rw-rw-r-- 1 joe joe  117231 Oct  2 16:18 compress_3high.bin.gz

#include "generateData.h"
#include "MurmurHash3.h"

static void chew(unsigned int seed, unsigned char bytes[16])
{
    unsigned char newBytes[16];
    memset(newBytes, 0, 16);
    MurmurHash3_x64_128(bytes, 16, seed, newBytes);
    memcpy(bytes, newBytes, 16);
}

void generateData(std::vector<unsigned char> &output, size_t size, unsigned int seed, unsigned int compressionFactor)
{
    unsigned char buffer[16];
    memset(buffer, 0, 16);

    output.resize(size);
    unsigned char *dst = &output[0];

    if(compressionFactor == 0)
    {
        compressionFactor = 1;
    }

    unsigned int chewTime = 0;
    size_t sizeLeft = size;
    while(sizeLeft > 0)
    {
        size_t amtToWrite = (sizeLeft > 16) ? 16 : sizeLeft;
        if((chewTime % compressionFactor) == 0)
        {
            chew(seed, buffer);
            chewTime = 0;
        }
        memcpy(dst, buffer, amtToWrite);

        ++chewTime;
        dst += amtToWrite;
        sizeLeft -= amtToWrite;
    }
}

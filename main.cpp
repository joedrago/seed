#include <stdlib.h>
#include <stdio.h>

#include "generateData.h"

int main(int argc, char **argv)
{
    if(argc == 5)
    {
        // error checking is for the WEAK
        unsigned int seed = atoi(argv[1]);
        unsigned int size = atoi(argv[2]);
        unsigned int sizeLeft = size;
        unsigned int compressionFactor = atoi(argv[3]);
        unsigned int chewTime = 0;
        char *filename = argv[4];
        FILE *f;

        printf("[%u] Generating %u bytes to %s\n", seed, size, filename);

        std::vector<unsigned char> data;
        generateData(data, size, seed, compressionFactor);

        f = fopen(filename, "wb");
        if(!f)
        {
            fprintf(stderr, "ERROR: failed to open '%s' for write\n", filename);
            return 1;
        }
        if(fwrite(&data[0], size, 1, f) != 1)
        {
            fclose(f);
            fprintf(stderr, "ERROR: failed to write to '%s'\n", filename);
            return 1;
        }
        fclose(f);
    }
    else
    {
        printf("Syntax: seed [number] [size] [compressionFactor] [filename]\n");
        return 1;
    }
    return 0;
}

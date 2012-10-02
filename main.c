#include <stdint.h>
#include <string.h>
#include <stdio.h>

void chew(uint32_t seed, unsigned char bytes[16]);

int main(int argc, char **argv)
{
    if(argc == 4)
    {
        // error checking is for the WEAK
        uint32_t seed = atoi(argv[1]);
        uint32_t size = atoi(argv[2]);
        uint32_t sizeLeft = size;
        char *filename = argv[3];
        char buffer[16];
        FILE *f;

        printf("[%u] Generating %u bytes to %s\n", seed, size, filename);

        memset(buffer, 0, 16);

        f = fopen(filename, "wb");
        if(!f)
        {
            fprintf(stderr, "ERROR: failed to open '%s' for write\n", filename);
            return 1;
        }
        while(sizeLeft > 0)
        {
            uint32_t amtToWrite = (sizeLeft > 16) ? 16 : sizeLeft;
            chew(seed, buffer);
            if(fwrite(buffer, amtToWrite, 1, f) != 1)
            {
                fclose(f);
                fprintf(stderr, "ERROR: failed to write to '%s'\n", filename);
                return 1;
            }
            sizeLeft -= amtToWrite;
        }
        fclose(f);
    }
    else
    {
        printf("Syntax: seed [number] [size] [filename]\n");
        return 1;
    }
    return 0;
}

// -----------------------------------------------------------------------------------
// Murmur hashing below, beware!

#define	FORCE_INLINE __attribute__((always_inline))
#define	FORCE_INLINE __attribute__((always_inline))

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

inline uint32_t rotl32 ( uint32_t x, int8_t r )
{
    return (x << r) | (x >> (32 - r));
}

inline uint64_t rotl64 ( uint64_t x, int8_t r )
{
    return (x << r) | (x >> (64 - r));
}

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

//-----------------------------------------------------------------------------
// Block read - if your platform needs to do endian-swapping or can only
// handle aligned reads, do the conversion here

FORCE_INLINE uint32_t getblock32 ( const uint32_t * p, int i )
{
    return p[i];
}

FORCE_INLINE uint64_t getblock64 ( const uint64_t * p, int i )
{
    return p[i];
}

//-----------------------------------------------------------------------------
// Finalization mix - force all bits of a hash block to avalanche

FORCE_INLINE uint32_t fmix32 ( uint32_t h )
{
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
}

//----------

FORCE_INLINE uint64_t fmix64 ( uint64_t k )
{
    k ^= k >> 33;
    k *= BIG_CONSTANT(0xff51afd7ed558ccd);
    k ^= k >> 33;
    k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
    k ^= k >> 33;

    return k;
}


void MurmurHash3_x64_128( const void * key, int len, uint32_t seed, void * out )
{
    int i;
    const uint8_t * data = (const uint8_t*)key;
    const int nblocks = len / 16;
    const uint8_t * tail;

    uint64_t h1 = seed;
    uint64_t h2 = seed;

    uint64_t k1 = 0;
    uint64_t k2 = 0;

    const uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
    const uint64_t c2 = BIG_CONSTANT(0x4cf5ad432745937f);

    //----------
    // body

    const uint64_t * blocks = (const uint64_t *)(data);

    for(i = 0; i < nblocks; i++)
    {
        uint64_t k1 = getblock64(blocks,i*2+0);
        uint64_t k2 = getblock64(blocks,i*2+1);

        k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;

        h1 = ROTL64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;

        k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

        h2 = ROTL64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;
    }

    //----------
    // tail

    tail = (const uint8_t*)(data + nblocks*16);

    switch(len & 15)
    {
    case 15: k2 ^= ((uint64_t)tail[14]) << 48;
    case 14: k2 ^= ((uint64_t)tail[13]) << 40;
    case 13: k2 ^= ((uint64_t)tail[12]) << 32;
    case 12: k2 ^= ((uint64_t)tail[11]) << 24;
    case 11: k2 ^= ((uint64_t)tail[10]) << 16;
    case 10: k2 ^= ((uint64_t)tail[ 9]) << 8;
    case  9: k2 ^= ((uint64_t)tail[ 8]) << 0;
        k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

    case  8: k1 ^= ((uint64_t)tail[ 7]) << 56;
    case  7: k1 ^= ((uint64_t)tail[ 6]) << 48;
    case  6: k1 ^= ((uint64_t)tail[ 5]) << 40;
    case  5: k1 ^= ((uint64_t)tail[ 4]) << 32;
    case  4: k1 ^= ((uint64_t)tail[ 3]) << 24;
    case  3: k1 ^= ((uint64_t)tail[ 2]) << 16;
    case  2: k1 ^= ((uint64_t)tail[ 1]) << 8;
    case  1: k1 ^= ((uint64_t)tail[ 0]) << 0;
        k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= len; h2 ^= len;

    h1 += h2;
    h2 += h1;

    h1 = fmix64(h1);
    h2 = fmix64(h2);

    h1 += h2;
    h2 += h1;

    ((uint64_t*)out)[0] = h1;
    ((uint64_t*)out)[1] = h2;
}

void chew(uint32_t seed, unsigned char bytes[16])
{
    unsigned char newBytes[16];
    memset(newBytes, 0, 16);
    MurmurHash3_x64_128(bytes, 16, seed, newBytes);
    memcpy(bytes, newBytes, 16);
}


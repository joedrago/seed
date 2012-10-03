#ifndef GENERATEDATA_H
#define GENERATEDATA_H

#include <cstring>
#include <vector>

void generateData(std::vector<unsigned char> &output, size_t size, unsigned int seed = 0, unsigned int compressionFactor = 1);

#endif

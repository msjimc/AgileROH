#pragma once
#include "string"
#include <vector>
#include <sstream>
#include <string>
#include "Region.h"

class VCFFilter
{
public:
    VCFFilter(void);
    ~VCFFilter(void);
	static int Filter(char* input, char* output, std::vector<Region> Regions, char* offSet);
    
    
};
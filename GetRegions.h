#pragma once
#include <string>
#include <map>
#include <vector>
#include "Region.h"

#include <fstream>
#include <iostream>


using namespace std;

class GetRegions
{
private:
	vector<string> theFiles;
	std::vector<Region> AddToList(std::vector<Region> Current, Region Next);
public:
	GetRegions() {};
	~GetRegions() {};
	map<string, vector<Region> > GetListOfRegions();
};
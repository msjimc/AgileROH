#pragma once
#include <string>
#include <map>
#include <vector>
#include <dirent.h>
#include "Region.h"

using namespace std;

class GetRegions
{
private:
	vector<string> theFiles;
	std::vector<Region> AddToList(std::vector<Region> Current, Region Next);
public:
	GetRegions() {};
	~GetRegions() {};
	GetRegions(string folder);
	map<string, vector<Region> > GetListOfRegions();
};
#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "Region.h"
#include "parameters.h"

using namespace std;

class CompareRegionList{
public:
	static long long compareTheLists(vector<Region> gold, vector<Region> pretender);
	static map<string, parameters> makeNewParametersMap(map<string, parameters> oldMap);

private:


};
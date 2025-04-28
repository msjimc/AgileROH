#pragma once
#include <string>
#include "methods.h"
#include <cstdio>
#include <cstdlib>

class Region
	{
protected: 
    int theStart; 
    int theEnd;
    std::string theChromosome;
 
	int coverage;
public:
    Region(void);
    Region(int Start, int End, std::string Chromosome);
    ~Region(void);
    int Start();
    std::string Chromosome();
    int End();
	std::string writeBrowserString();
	std::string writeHumanString();

 
	int lookForOverlap(std::string chromosome, int Start, int End);
	void resetCoverage() {coverage = theEnd - theStart; }
	void adjustCoverage(int value){ coverage += value; }
	int getCoverage(){ return coverage; }
 };
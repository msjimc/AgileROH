#include "VCFFilter.h"
//#include <cstdio>
//#include <cstdlib>
#include <fstream>
#include "AffyEngine.h"
//#include <iostream>
#include <istream>
//#include <ostream>

VCFFilter::VCFFilter(void){}

VCFFilter::~VCFFilter(void){}

int VCFFilter::Filter(char* input, char* output, std::vector<Region> Regions, char* offSet)
{
    std::string value(offSet);
	int theOffSet = methods::to_Integer(value);

	std::ifstream VCFData (input);
	if (! VCFData)
	{
		std::perror(input);
		return EXIT_FAILURE;
	}

	std::ofstream outputVCF(output);
    if (! outputVCF)
    {
        std::perror(output);
        return EXIT_FAILURE;
    }

	std::string line, item, chromosome;
	std::vector<std::string> items;
	int cm =0;
	int chromosomeInt = 0;
	Region CurrentRegion = Regions[0];
	int chromosomeRegion = methods::to_Integer(CurrentRegion.Chromosome());
	int index = 0;
	bool done = false;

	while (std::getline(VCFData, line)) 
	{
		if(line.substr(0, 1) != "#")
		{
			items = methods::Split(line, '\t');
			cm = methods::to_Integer(items.at(1));

			chromosome = items.at(0);
			if (chromosome.substr(0, 1) == "c" || chromosome.substr(0, 1) == "C")
			{chromosome = chromosome.substr(3, chromosome.size() - 3);}
			chromosomeInt = methods::to_Integer(chromosome);

			done =false;

			while (done == false)
			{
				if (chromosomeInt <  chromosomeRegion)// do nothing}
				{done = true;}
				else if (chromosomeInt > chromosomeRegion)// increment region index and try again
				{
					index++;
					if (index < Regions.size())
					{ 
						CurrentRegion = Regions[index];
						chromosomeRegion = methods::to_Integer(CurrentRegion.Chromosome());
					}
					else {done = true;}
				}
				else if (chromosomeInt = chromosomeRegion)// test position
				{
					if (cm < CurrentRegion.Start() - theOffSet)
					{done = true;}
					else if (cm > CurrentRegion.End() + theOffSet)
					{
						index++;
						if (index < Regions.size())
							{
							CurrentRegion = Regions[index];
							chromosomeRegion = methods::to_Integer(CurrentRegion.Chromosome());
							}
						else {done = true;}
					}
					else
					{
						 outputVCF << line + "\n";
						 done = true;
					}
				}
			}
		}
		else
		{
			outputVCF << line + "\n";
		}
	}

	VCFData.close();
	outputVCF.close();
}
   
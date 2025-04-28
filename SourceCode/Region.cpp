#include "Region.h"


Region::Region(void){}
Region::~Region(void){}
Region::Region(int Start, int End, std::string Chromosome)
{
	theStart = Start;
	theEnd = End;
	theChromosome = Chromosome;
	coverage = theEnd - theStart;;
}


int Region::Start(){return theStart;}
std::string Region::Chromosome(){ return theChromosome;}
int Region::End(){return theEnd;}

std::string Region::writeBrowserString()
{return "chr" + theChromosome + ":" + methods::To_NiceString(theStart) + "-" + methods::To_NiceString(theEnd)  + "\n";}
	
std::string Region::writeHumanString()
{return theChromosome + '\t' + methods::To_NiceString(theStart) + '\t' + methods::To_NiceString(theEnd) + '\t' + methods::To_NiceString(theEnd - theStart) + "\n";}

int Region::lookForOverlap(std::string chromosome, int start, int end)
{
	int covered = 0;
	if (theChromosome.compare(chromosome) == 0)
	{
		if (start >= theStart && end <= theEnd )// inside this region
		{ covered = end - start; }
		else if (start < theStart && end > theEnd)// contains this region
		{ covered = theEnd - theStart; }
		else if (start > theStart && start < theEnd && end > theEnd)// contains end of region
		{ covered = theEnd - start; }
		else if (end > theStart && end < theEnd && start < theStart)// contains start of region
		{ covered = end - theStart; }
	}
	return covered;
}


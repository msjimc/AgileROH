#include "CompareRegionList.h"

long long CompareRegionList::compareTheLists(vector<Region> gold, vector<Region> pretender)
{
	long long coverage=0;
	for (int index = 0; index < pretender.size(); index++)
	{ pretender[index].resetCoverage(); }

	for (int index = 0; index < gold.size(); index++)
	{ gold[index].resetCoverage(); }

	int indexG = 0;
	int indexP = 0;

	while (indexG < gold.size() && indexP < pretender.size())
	{
		int com = methods::to_Integer(gold[indexG].Chromosome()) - methods::to_Integer((pretender[indexP].Chromosome()));
		
		if (com == 0)
		{
			if (gold[indexG].Start() > pretender[indexP].End())
			{				
				//cout << indexP << "\t" << pretender[indexP].getCoverage() << "P\n";
				indexP++; 
			}
			else if (pretender[indexP].Start() > gold[indexG].End())
			{				
				//cout << indexG << "\t" << gold[indexG].getCoverage() << "G\n";
				indexG++; 
			}
			else
			{
				int one = pretender[indexP].lookForOverlap(gold[indexG].Chromosome(), gold[indexG].Start(), gold[indexG].End());
				int two = gold[indexG].lookForOverlap(pretender[indexP].Chromosome(), pretender[indexP].Start(), pretender[indexP].End());

				pretender[indexP].adjustCoverage(-one);
				gold[indexG].adjustCoverage(-two);

				if (pretender[indexP].End() > gold[indexG].End())
				{ 
					//cout << indexG << "\t" << gold[indexG].getCoverage() << "G\n";
					indexG++; 
				}
				else
				{ 					
					//cout << indexP << "\t" << pretender[indexP].getCoverage() << "P\n";
					indexP++; 
				}
			}
		}
		else if (com < 0)
		{ 
			//cout << indexG << "\t" << gold[indexG].getCoverage() << "G\n";
			indexG++; 
		}
		else if (com > 0)
		{ 			
			//cout << indexP << "\t" << pretender[indexP].getCoverage() << "P\n";
			indexP++; 
		}
	}


	for (int index = 0; index < pretender.size(); index++)
	{ coverage += pretender[index].getCoverage(); }

	for (int index = 0; index < gold.size(); index++)
	{ coverage += gold[index].getCoverage(); }

	return coverage;

}

 map<string, parameters> CompareRegionList::makeNewParametersMap(map<string, parameters> oldMap)
 {
	map<string, parameters> newMap;

	vector<long long> scores;
	for (map<string, parameters>::iterator it = oldMap.begin(); it != oldMap.end(); it++)
	{
		if (it->second.getScore() > 0)
		{ scores.push_back(it->second.getScore()); }
	}

	std::sort(scores.begin(), scores.end());
	long long cutoff = scores[9];
	cerr << "Best: " << scores[0] << " CutOff: " << cutoff << "\n";
	
	vector<parameters> goodParameters;
	for (map<string, parameters>::iterator it = oldMap.begin(); it != oldMap.end(); it++)
	{
		if (it->second.getScore() <= cutoff)
		{ 
			goodParameters.push_back(it->second);
			newMap.insert(pair<string, parameters>(it->first, it->second)); 
			cerr << "Added: " << it->second.getScore() << "\t" << it->second.to_EXCEL();
		}
	}	

	int size = goodParameters.size();
	for (int index = 0; index < size; index++)
	{
		for (int inner = index + 1; inner < size; inner++)
		{	
			parameters p(true);
			p.combineTwoSets(goodParameters[index], goodParameters[inner]);
			p.mutate();
			map<string, parameters>::iterator it = newMap.find(p.to_EXCEL());
			if (it == newMap.end())
			{ newMap.insert(pair<string, parameters>(p.to_EXCEL(), p)); }

		}
	}

	for (int index = 0; index < 40; index++)
	{
		parameters p(true);		
		map<string, parameters>::iterator it = newMap.find(p.to_EXCEL());
		if (it == newMap.end())
		{ newMap.insert(pair<string, parameters>(p.to_EXCEL(), p)); }
	}

	return newMap;

 }
#include "GetRegions.h"


map<string, vector<Region> > GetRegions::GetListOfRegions()
{
	map<string, vector<Region> > fileRegions;

	for (vector<string>::iterator it = theFiles.begin(); it != theFiles.end(); it++)
	{
		string file = *it ;
		std::ifstream input(file.c_str());
		if (!input)
		{
			std::perror(file.c_str());
			std::cerr << "Can not open the 'input file'";			
		}
		else
		{
			Region thisRegion(1, 1, "1");
			vector<Region> regions;
			regions.push_back(thisRegion);
			string line;
			getline(input, line);
			while (getline(input, line))
			{
				vector<string> items = methods::Split(line, '\t');
				Region r(methods::to_Integer(items[1]), methods::to_Integer(items[2]), items[0]);
				regions = AddToList(regions, r);
			}
			fileRegions.insert(std::pair<string, vector<Region> >(file.substr(0, file.length() - 4), regions));
		}
		input.close();
	}

	return fileRegions;
}

std::vector<Region> GetRegions::AddToList(std::vector<Region> Current, Region Next)
	{

	if (Current.size() == 1 && Current[0].End() == 1) 		 
		{Current[0] = Next;}
	else
		{
		Region Last = Current.back();
		if (Last.Chromosome() != Next.Chromosome())
			{Current.push_back(Next);}
		else if(Last.End() + 100000 > Next.Start())
			{
			Region newRegion(Last.Start(), Next.End(), Last.Chromosome());
			Current[Current.size()-1] = newRegion;
			}
		else
			{Current.push_back(Next);}
		}
				
	return Current;

	}

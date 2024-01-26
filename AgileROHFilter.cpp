// AutozygousFilter.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include "SNP.h"
#include "AffyEngine.h"
#include "Region.h"
#include "VCFFilter.h"

int main(int argc, char* argv[])
{

    if (argc < 6 || argc > 8)
    {   
        std::cerr << "Usage: 'input VCF file' 'output VCF file' 'output regions text file' 'n' 'export file format option' 'optional use SNP without RS ID (-Y)' 'optional use genotypes in VCF file (-V)\nWhere 'n' retains variants with in n bp of a region (n = 0 to 1000000)\nExport regions file options (select 1):\n-t Tabular data\n-b Genome browser strings\n-a Both outputs\n";
        return EXIT_FAILURE;
    }

    std::ifstream input(argv[1]);
    if (! input)
    {
        std::perror(argv[1]);
        return EXIT_FAILURE;
    }
        input.close();

	std::ofstream outputVCF(argv[2]);
    if (! outputVCF)
    {
        std::perror(argv[2]);
        return EXIT_FAILURE;
    }

    std::ofstream output(argv[3]);
    if (! output)
    {
        std::perror(argv[3]);
        return EXIT_FAILURE;
    }

    input.exceptions(input.badbit);
    output.exceptions(output.badbit);
    outputVCF.exceptions(outputVCF.badbit);

	bool noRS = false;
	bool genotype = false;
	if (argc == 7)
	{ 
		string optional(argv[6]);		
		
		if (optional == "-Y" || optional == "-y")
		{ noRS = true; }		
		else if (optional == "-V" || optional == "-v")
		{ genotype = true; }		
	}	
	
	if (argc == 8)
	{ 
		string optional(argv[7]);		
		
		if (optional == "-Y" || optional == "-y")
		{ noRS = true; }		
		else if (optional == "-V" || optional == "-v")
		{ genotype = true; }		
	}	
	
	
	
    try
    {
		parameters firstP(true);
		firstP.AA = 0.64f;
		firstP.BB = 0.17f;
		firstP.AB = 0.17f;
		firstP.Fraction = 0.1f;
		firstP.readDepth = 5;
		firstP.iterationNumber = 3;
		firstP.RunsCutOffProportion = 386;
		firstP.ExclusionCutOffProportion = 575;

        std::cout << "Reading data file " << argv[1] << '\n';
		
        AffyEngine worker(argv[1], firstP, noRS, genotype);
       	if (worker.status != 0)
		{ 
			return -1;
		}
		
        std::cout << "Processing data and finding autozygous regions\n";
        
		int errorStatus = worker.AnalyseDataAffy();
		if (errorStatus == -1)
		{ 
			std::cout << "Could not process file (" << errorStatus << "\n";
			return -1;
		}
		else{ std::cout << "Created homozygous run data\n";}
		
		std::vector<Region> Regions = worker.GetRegions();
	
		std::cout << "Filtering the VCF file\n";
		VCFFilter::Filter(argv[1], argv[2], Regions, argv[4]);
		 		
        std::string sb, sbInterval;
		sb = "Chromosome\tStart\tEnd\tLength\n";

		if (Regions[0].End() != 1)
		{
			for (int index = 0; index < Regions.size(); index++) 
			{
				sb += Regions[index].writeHumanString();
				sbInterval += Regions[index].writeBrowserString();
			}
		}
		else
		{
			sb = "No regions";
			sbInterval = "No regions";
		}

       std::string option(argv[5]);
       if (option == "-t" || option == "-T")
       {output << sb;}
       else if (option == "-b" || option == "-B")
       {output << sbInterval;}
       else
       {
			output << "Tabular data\n";
			output << sb;	
			output << '\n';
			output << "Genome browser\n";
			output << sbInterval;
			output.close();
			input.close();
        }
        
        output.close();
        std::cout << "Completed task";
    }
    catch (std::ios_base::failure const& ex)
    {
        std::cerr << "Error analysing file: " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

return 0;

}




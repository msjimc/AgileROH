// AgileROHFinder.cpp : Defines the entry point for the console application.
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
#include "parameters.h"

int main(int argc, char* argv[])
{

	if (argc < 4 || argc > 6)
	{
		std::cerr << "Usage: 'input file' 'output file' 'export file option' 'optional use SNP without RS ID (-Y)' 'optional use genotypes in VCF file (-V)'\nExport file options:\n-t Tabular data\n-b Genome browser strings\n-a Both outputs\nWhen processing VCF files";
		return EXIT_FAILURE;
	}

	std::ifstream input(argv[1]);
	if (!input)
	{
		std::perror(argv[1]);
		std::cerr << "Can not open the 'input file'\n";
		return EXIT_FAILURE;
	}
	input.close();

	std::ofstream output(argv[2]);
	if (!output)
	{
		std::perror(argv[2]);
		std::cerr << "Can not create the 'output file'\n";
		return EXIT_FAILURE;
	}

	input.exceptions(input.badbit);
	output.exceptions(output.badbit);

	bool noRS = false;
	bool genotype = false;
	if (argc == 5 || argc == 6)
	{
		string option4(argv[4]);

		if (option4 == "-Y" || option4 == "-y")
		{ noRS = true; }
		else if (option4 == "-V" || option4 == "-v")
		{ genotype = true; }
	}
	if (argc == 6)
	{
		string option4(argv[5]);

		if (option4 == "-Y" || option4 == "-y")
		{
			noRS = true;
		}
		else if (option4 == "-V" || option4 == "-v")
		{
			genotype = true;
		}
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

		std::cout << "Processing data\n";
		int errorStatus = worker.AnalyseDataAffy();
		if (errorStatus == -1)
		{
			std::cout << "Could not process file (" << errorStatus << "\n";
			return -1;
		}
		else { std::cout << "Created homozygous run data\n"; }

		std::vector<std::string> answer = worker.WriteNewDescription();

		std::string option(argv[3]);
		if (option == "-t" || option == "-T")
		{
			output << answer[0];
		}
		else if (option == "-b" || option == "-B")
		{
			output << answer[1];
		}
		else
		{
			output << "Tabular data\n";
			output << answer[0];
			output << '\n';
			output << "Genome browser\n";
			output << answer[1];
			output.close();
			input.close();
		}

		output.close();
		std::cout << "Completed task\n";
	}
	catch (char)
	{
		std::cerr << "Error analysing file: " << argv[1] << '\n';
		return EXIT_FAILURE;
	}
	catch (std::ios_base::failure const& ex)
	{
		std::cerr << "Error analysing file: " << argv[1] << '\n';
		return EXIT_FAILURE;
	}


	return 0;
}

#include "AffyEngine.h"
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include "methods.h"
#include "Region.h"
#include <cstring>
#include <algorithm>

void AffyEngine::SortArrays()
{
	std::sort(c1.begin(), c1.end());
	std::sort(c2.begin(), c2.end());
	std::sort(c3.begin(), c3.end());
	std::sort(c4.begin(), c4.end());
	std::sort(c5.begin(), c5.end());
	std::sort(c6.begin(), c6.end());
	std::sort(c7.begin(), c7.end());
	std::sort(c8.begin(), c8.end());
	std::sort(c9.begin(), c9.end());
	std::sort(c10.begin(), c10.end());
	std::sort(c11.begin(), c11.end());
	std::sort(c12.begin(), c12.end());
	std::sort(c13.begin(), c13.end());
	std::sort(c14.begin(), c14.end());
	std::sort(c15.begin(), c15.end());
	std::sort(c16.begin(), c16.end());
	std::sort(c17.begin(), c17.end());
	std::sort(c18.begin(), c18.end());
	std::sort(c19.begin(), c19.end());
	std::sort(c20.begin(), c20.end());
	std::sort(c21.begin(), c21.end());
	std::sort(c22.begin(), c22.end());
}

AffyEngine::AffyEngine(void)
{}

AffyEngine::AffyEngine(const char* dataFilename, parameters p)
{
	setValues(p);

	theFilename = dataFilename;
	int length = (int)std::strlen(theFilename);
	std::string s(theFilename); 
	std::string extension = s.substr(length - 3, 3);
	if (extension == "txt" || extension == "TXT")
	{ 		
		p.iterationNumber = 5;
		p.RunsCutOffProportion = 100;
		p.ExclusionCutOffProportion = 700;
		AffyEngine::ReadBirdSeed(theFilename);
	}
	else if (extension == "xls" || extension == "XLS")
	{ 
		p.iterationNumber = 5;
		p.RunsCutOffProportion = 100;
		p.ExclusionCutOffProportion = 700;
		AffyEngine::ReadAffyXls(theFilename); 		
	}
	else if (extension == "vcf" || extension == "VCF")
	{ AffyEngine::ReadVCF(theFilename); }
}

AffyEngine::~AffyEngine(void)
{}

int AffyEngine::ReadBirdSeed(const char* dataFilename)
{
	std::ifstream input(dataFilename);
	if (!input)
	{
		std::perror(dataFilename);
		return EXIT_FAILURE;
	}
	else
	{

		if (AffyEngine::searchBirdSeedFile(dataFilename) == false)
		{
			return -1;
		}

		double cm = 0;
		int cutOff = 100;
		std::vector<int> count(26);
		std::vector<std::string> items;
		std::string line, item, name, chromosome, genotype;
		std::getline(input, line);
		while (std::getline(input, line))
		{
			int counter = 0;
			std::stringstream sss(line);
			while (std::getline(sss, item, '\t'))
			{
				if (counter == cmPIndex)
				{
					cm = methods::to_Double(item);
				}
				else if (counter == SNPRSIndex)
				{
					name = item;
				}
				else if (counter == GenotypeIndex)
				{
					if (item.length() != 2 || item[0] == '-')
					{ genotype = "noCall"; }
					else if (item[0] == item[1])
					{ genotype = "AA"; }
					else
					{ genotype = "AB"; }					
				}
				else if (counter == ChromoIndex)
				{
					chromosome = item;
				}
				counter++;
			}

			SNP aSNP(cm, name, genotype, chromosome);// , cutOff);
			if (aSNP.getFailedData() == false)
			{
				count[aSNP.getChromosome()]++;
			}
			genotype = "";
		}
		input.close();
		setVectorSizes(count);
		std::vector<int> newCount(26);
		count = newCount;

		std::ifstream input(dataFilename);
		while (std::getline(input, line))
		{
			int counter = 0;
			std::stringstream sss(line);
			while (std::getline(sss, item, '\t'))
			{
				if (counter == cmPIndex)
				{
					cm = methods::to_Double(item);
				}
				else if (counter == SNPRSIndex)
				{
					name = item;
				}
				else if (counter == GenotypeIndex)
				{
					if (item.length() != 2 || item[0] == '-')
					{ genotype = "noCall"; }
					else if (item[0] == item[1])
					{ genotype = "AA"; }
					else
					{ genotype = "AB"; }
				}
				else if (counter == ChromoIndex)
				{
					chromosome = item;
				}
				counter++;
			}

			SNP aSNP(cm, name, genotype, chromosome);//, cutOff);
			if (aSNP.getFailedData() == false)
			{
				AddtoArray(aSNP.getChromosome(), aSNP, count[aSNP.getChromosome()]);
				count[aSNP.getChromosome()]++;
			}
			genotype = "";
		}
		input.close();
	}

	SortArrays();

	return 1;
}

int AffyEngine::ReadAffyXls(const char* dataFilename)
{
	std::ifstream input(dataFilename);
	if (! input)
	{
		std::perror(dataFilename);
		return EXIT_FAILURE;
	}
	else
	{

		if (AffyEngine::searchFile(dataFilename) == false)
		{return -1;}

		double cm =0;
		int cutOff = 100;
		std::vector<int> count(26);
		std::vector<std::string> items;
		std::string line, item, name, chromosome, genotype;
		std::getline(input, line);
		while (std::getline(input, line)) 
		{
			int counter = 0;
			std::stringstream sss(line);
			while (std::getline(sss, item, '\t')) 
			{
				if (counter == cmPIndex)
				{cm = methods::to_Double(item);}
				else if (counter == SNPRSIndex)
				{name = item;}
				else if (counter == GenotypeIndex)
				{genotype = item;}
				else if (counter == ChromoIndex)
				{chromosome = item;}
				counter++;
			}

			SNP aSNP(cm, name, genotype, chromosome);//, cutOff);
			if (aSNP.getFailedData() == false)
			{count[aSNP.getChromosome()]++;}
			genotype = "";
		}
		input.close();
		setVectorSizes(count);
		std::vector<int> newCount(26);
		count = newCount;

		std::ifstream input(dataFilename);
		while (std::getline(input, line)) 
		{
			int counter = 0;
			std::stringstream sss(line);
			while (std::getline(sss, item, '\t')) 
			{
				if (counter == cmPIndex)
				{cm = methods::to_Double(item);}
				else if (counter == SNPRSIndex)
				{name = item;}
				else if (counter == GenotypeIndex)
				{genotype = item;}
				else if (counter == ChromoIndex)
				{chromosome = item;}
				counter++;
			}


			SNP aSNP(cm, name, genotype, chromosome);//, cutOff);
			if (aSNP.getFailedData() == false)
			{
				AddtoArray(aSNP.getChromosome(), aSNP, count[aSNP.getChromosome()]);
				count[aSNP.getChromosome()]++;
			}
			genotype = "";
		}
		input.close();
	}

	SortArrays();

	return 1;
}

int AffyEngine::ReadVCF(const char* dataFilename)
{
	std::ifstream input(dataFilename);
	if (! input)
	{
		std::perror(dataFilename);
		return EXIT_FAILURE;
	}
	else
	{

		if (AffyEngine::searchVCFFile(dataFilename) == false)
		{return -1;}

		double cm = 0;
		int cutOff = 100;
		int minimumReadDepth = readDepth;

		std::vector<int> count(26);
		std::vector<std::string> items;

		std::string line, item, name, chromosome, genotype;
		int counter = 0;

		while (std::getline(input, line)) 
		{
			if(line.substr(0, 1) != "#")
			{

				counter++;
				items = methods::Split(line, '\t');
				name = items.at(SNPRSIndex);

				if (name.substr(0,1) != ".")
				{
					genotype = AffyEngine::getGenotype(items.at(GenotypeIndex), minimumReadDepth);
					cm = methods::to_Double(items.at(cmPIndex));
					chromosome = items.at(ChromoIndex);

					SNP aSNP(cm, name, genotype, chromosome);//, cutOff);
					if (aSNP.getFailedData() == false)
					{count[aSNP.getChromosome()]++;}

				}

			}
		}
		input.close();
		setVectorSizes(count);
		std::vector<int> newCount(26);
		count = newCount;

		std::ifstream input(dataFilename);

		while (std::getline(input, line)) 
		{
			if(line.substr(0, 1) != "#")
			{
				items = methods::Split(line, '\t');
				name = items.at(SNPRSIndex);
				
				if (name.substr(0,1) != ".")
				{
					genotype = AffyEngine::getGenotype(items.at(GenotypeIndex), minimumReadDepth);
					cm = methods::to_Double(items.at(cmPIndex));
					chromosome = items.at(ChromoIndex);


					SNP aSNP(cm, name, genotype, chromosome);//, cutOff);
					if (aSNP.getFailedData() == false)
					{
						AddtoArray(aSNP.getChromosome(), aSNP, count[aSNP.getChromosome()]);
						count[aSNP.getChromosome()]++;							
					}											
				}
			}
		}
		input.close();
		SortArrays();

	}
	return 1;
}

std::string AffyEngine::getGenotype(std::string item, int minimumReadDepth)
{
	std::vector<std::string> subitems = methods::Split(item, ':');
	std::vector<std::string> values = methods::Split(subitems.at(AD), ',');
	int reference = methods::to_Integer(values.at(0));
	int	variant = methods::to_Integer(values.at(1));
	int readDepth = methods::to_Integer(subitems.at(DP)); 
	float ratio = (float)(readDepth - variant) / (float)readDepth;

	std::string answer = "noCall";

	if (values.size() > 2)
	{answer = "triallelic";}
	else if (readDepth >= minimumReadDepth)
	{
		if (readDepth == minimumReadDepth)
		{answer = "noCall";}
		else if (ratio > AA)
		{answer = "AA";}
		else if (ratio < BB)
		{ answer = "BB";}
		else if (ratio > lowerAB && ratio < higherAB)
		{answer = "AB";}
	}
	else
	{answer = "lower";}

	return answer;

}

bool AffyEngine::searchBirdSeedFile(const char* filename)
{
	bool answer = false;
	std::string strData = "";
	int intStrArray = 0;
	std::vector<std::string> strRow, strDataArray;
	bool bcmP = false;

	GenotypeIndex = -1;
	SNPRSIndex = -1;
	ChromoIndex = -1;
	cmPIndex = -1;

	std::ifstream input(filename);
	if (!input)
	{
		std::perror(filename);
		return answer;
	}
	else
	{
		std::string line;
		int place = 0;
		bool gotTitles = false;
		while (gotTitles == false)
		{
			std::getline(input, line);
			if (line[0] != '#')
			{ gotTitles = true; }
		}
		std::vector<std::string> items = methods::Split(line, '\t');
		for (std::vector<std::string>::iterator i(items.begin()); i != items.end(); ++i)
		{
			std::string item(*i);

			if (item == "Chromosome")
			{ ChromoIndex = place; }
			else if (item == "Chromosomal Position")
			{ cmPIndex = place; }
			else if (item == "dbSNP RS ID")
			{ SNPRSIndex = place; }
			else if (item.find("Call") != std::string::npos)
			{ GenotypeIndex = place; }			

			place++;
		}
	}

	std::string sError = "";

	if (ChromoIndex == -1) {
		if (sError == "")
			sError = "Chromosome";
		else {
			sError += "\nChromosome";
		}
	}
	if (cmPIndex == -1) {
		if (sError == "")
			sError = "Position";
		else {
			sError += "\nPosition";
		}
	}

	if (SNPRSIndex == -1) {
		if (sError == "")
			sError = "dbSNP RS ID";
		else {
			sError += "\ndbSNP RS ID";
		}
	}
	if (GenotypeIndex == -1) {
		if (sError == "")
			sError = "Genotype";
		else {
			sError += "\nGenotype";
		}
	}

	input.close();
	answer = true;
	if (!(sError == ""))
	{
		sError = "This file does not contain all the data needed please include the following data:\n" + sError;
	}

	return answer;

}

bool AffyEngine::searchFile(const char* filename)
{
	bool answer = false;
	std::string strData = "";
	int intStrArray =0;
	std::vector<std::string> strRow, strDataArray;
	bool bcmP = false;

	GenotypeIndex = -1;
	SNPRSIndex = -1;
	ChromoIndex = -1;
	cmPIndex = -1;

	std::ifstream input(filename);
	if (! input)
	{
		std::perror(filename);
		return answer;
	}
	else
	{
		std::string line;
		int place =0;
		std::getline(input, line);
		std::vector<std::string> items = methods::Split(line, '\t');
		for (std::vector<std::string>::iterator i(items.begin()); i != items.end();++i)
		{
			std::string item(*i);

			if (item == "Chromosome")
			{ChromoIndex = place;}
			else if (item == "Physical Position")
			{cmPIndex = place;}
			else if (item == "dbSNP RS ID")
			{SNPRSIndex = place;}
			else if (item.find("Call") != std::string::npos)
			{ GenotypeIndex = place; }

			place++;
		}
	}

	std::string sError = "";

	if (ChromoIndex == -1){
		if (sError == "")
			sError = "Chromosome";
		else{
			sError += "\nChromosome";
		}
	}
	if (cmPIndex == -1){
		if (sError == "")
			sError = "Position";
		else{
			sError += "\nPosition";
		}
	}

	if (SNPRSIndex == -1){
		if (sError == "")
			sError = "dbSNP RS ID";
		else{
			sError += "\ndbSNP RS ID";
		}
	}
	if (GenotypeIndex == -1){
		if (sError == "")
			sError = "Genotype";
		else{
			sError += "\nGenotype";
		}
	}

	input.close();
	answer = true;
	if (! (sError == ""))
	{sError = "This file does not contain all the data needed please include the following data:\n" + sError;}

	return answer;

}

bool AffyEngine::searchVCFFile(const char* filename)
{
	bool answer = false;
	std::string strData = "";
	int intStrArray =0;
	std::vector<std::string> strRow, strDataArray;
	bool bcmP = false;

	GenotypeIndex = 9;
	SNPRSIndex = 2;
	ChromoIndex = 0;
	cmPIndex = 1;
	AD=-1;
	DP =-1;
	std::ifstream input(filename);
	if (! input)
	{
		std::perror(filename);
		return answer;
	}
	else
	{
		bool done = false;
		std::string line;
		int place =0;
		while (done == false)
		{
			std::getline(input, line);
			if(line.substr(0, 1) != "#")
			{
				std::vector<std::string> items = methods::Split(line, '\t');
				std::vector<std::string> subItems = methods::Split(items.at(8), ':');
				for (std::vector<std::string>::iterator i(subItems.begin()); i != subItems.end(); ++i)
				{
					std::string item(*i);

					if (item == "AD")
					{AD = place;}
					else if (item == "DP")
					{DP = place;}

					place++;
				}
				done = true;
			}
		}
	}

	std::string sError = "";

	if (AD == -1){
		if (sError == "")
			sError = "Allele depth (AD)";
		else{
			sError += "\nAllele depth (AD)";
		}
	}
	if (DP == -1){
		if (sError == "")
			sError = "Total read depth (DP)";
		else{
			sError += "\nTotal read depth (DP)";
		}
	}


	input.close();
	answer = true;
	if (! (sError == ""))
	{sError = "This file does not contain all the data needed please include the following data:\n" + sError;}

	return answer;

}

void AffyEngine::setVectorSizes(std::vector<int> count)
{
	c1.resize(count[1]);
	c2.resize(count[2]);
	c3.resize(count[3]);
	c4.resize(count[4]);
	c5.resize(count[5]);
	c6.resize(count[6]);
	c7.resize(count[7]);
	c8.resize(count[8]);
	c9.resize(count[9]);
	c10.resize(count[10]);
	c11.resize(count[11]);
	c12.resize(count[12]);
	c13.resize(count[13]);
	c14.resize(count[14]);
	c15.resize(count[15]);
	c16.resize(count[16]);
	c17.resize(count[17]);
	c18.resize(count[18]);
	c19.resize(count[19]);
	c20.resize(count[20]);
	c21.resize(count[21]);
	c22.resize(count[22]);

}

void AffyEngine::AddtoArray(int Chromo, SNP cm, int index)
{
	switch (Chromo)
	{
	case 2:
		c2[index] = cm;
		break; 
	case 1:
		c1[index] = cm;
		break; 
	case 3:
		c3[index] = cm;
		break; 
	case 4:
		c4[index] = cm;
		break; 
	case 5:
		c5[index] = cm;
		break; 
	case 6:
		c6[index] = cm;
		break; 
	case 7:
		c7[index] = cm;
		break; 
	case 8:
		c8[index] = cm;
		break; 
	case 9:
		c9[index] = cm;
		break; 
	case 10:
		c10[index] = cm;
		break; 
	case 11:
		c11[index] = cm;
		break; 
	case 12:
		c12[index] = cm;
		break; 
	case 13:
		c13[index] = cm;
		break; 
	case 14:
		c14[index] = cm;
		break; 
	case 15:
		c15[index] = cm;
		break;
	case 16:
		c16[index] = cm;
		break; 
	case 17:
		c17[index] = cm;
		break; 
	case 18:
		c18[index] = cm;
		break; 
	case 19:
		c19[index] = cm;
		break; 
	case 20:
		c20[index] = cm;
		break; 
	case 21:
		c21[index] = cm;
		break; 
	case 22:
		c22[index] = cm;
		break;
	}
}

std::vector<SNP> AffyEngine::GetSNPs(int Chromosome)
{
	switch (Chromosome)
	{
	case 2:
		return c2;
		break; 
	case 1:
		return c1;
		break; 
	case 3:
		return c3;
		break; 
	case 4:
		return c4;
		break; 
	case 5:
		return c5;
		break; 
	case 6:
		return c6;
		break; 
	case 7:
		return c7;
		break; 
	case 8:
		return c8;
		break; 
	case 9:
		return c9;
		break; 
	case 10:
		return c10;
		break; 
	case 11:
		return c11;
		break; 
	case 12:
		return c12;
		break; 
	case 13:
		return c13;
		break; 
	case 14:
		return c14;
		break; 
	case 15:
		return c15;
		break; 
	case 16:
		return c16;
		break; 
	case 17:
		return c17;
		break; 
	case 18:
		return c18;
		break; 
	case 19:
		return c19;
		break; 
	case 20:
		return c20;
		break; 
	case 21:
		return c21;
		break;
	case 22:
		return c22;
		break;
	}

	std::vector<SNP> empty;
	return empty;

}

void AffyEngine::SetSNPs(int Chromosome, std::vector<SNP> SNPs)
{
	switch (Chromosome)
	{
	case 2:
		c2 = SNPs;
		break;
	case 1:
		c1 = SNPs;
		break; 
	case 3:
		c3 = SNPs;
		break; 
	case 4:
		c4 = SNPs;
		break; 
	case 5:
		c5 = SNPs;
		break; 
	case 6:
		c6 = SNPs;
		break; 
	case 7:
		c7 = SNPs;
		break; 
	case 8:
		c8 = SNPs;
		break; 
	case 9:
		c9 = SNPs;
		break;
	case 10:
		c10 = SNPs;
		break;
	case 11:
		c11 = SNPs;
		break; 
	case 12:
		c12 = SNPs;
		break; 
	case 13:
		c13 = SNPs;
		break; 
	case 14:
		c14 = SNPs;
		break;
	case 15:
		c15 = SNPs;
		break; 
	case 16:
		c16 = SNPs;
		break;
	case 17:
		c17 = SNPs;
		break;
	case 18:
		c18 = SNPs;
		break;
	case 19:
		c19 = SNPs;
		break;
	case 20:
		c20 = SNPs;
		break; 
	case 21:
		c21 = SNPs;
		break; 
	case 22:
		c22 = SNPs;
	}
}

void AffyEngine::AnalyseDataAffy()
{

	if (SetConstants() == -1)
	{return;}

	for (int index = 0; index < iterationNumber; ++index)
	{
		if (HomozygousRun(false) == -1)
		{return;}

		if (CleanUp() == -1)
		{return;}
	}

	if (HomozygousRun(true) == -1)
	{return;}

	if (SetConstants() == -1)
	{return;}

}

int AffyEngine::SetConstants()
{
	int answer = -1;
	int Number = c1.size();
	RunsCutOff = (int)(((RunsCutOffProportion * Number) / 70700.0f) + 0.5f);
	ExclusionCutOff = (int)(((ExclusionCutOffProportion * Number) / 70700.0f) + 0.5f);
	answer = 1;

	return answer;

}

int AffyEngine::HomozygousRun(bool Clean)
{
	std::vector<SNP> cN;
	int Run = 0;
	int answer = 1;

	for (int chromosome = 1; chromosome < 23; chromosome++)
	{
		cN = GetSNPs(chromosome);
		int length = cN.size();
		
		if (Clean == true)
		{
			for (int index = 0; index < length; index++)
			{cN[index].ResetHomozygousRuns();}
		}

		Run = 0;
		
		for (int index = 0; index < length; index++)
		{
			Run = cN[index].HomozygousRuns(Run);			
		}

		Run = 0;
		for (int index = length - 1 ; index > - 1; index--)
		{Run = cN[index].MaximumRun(Run);}

		Run = 0;
		if (RunsCutOff > 20)
		{
			for (int index = 1; index < length - 1; index++)
			{cN[index].WrongCall(cN[index - 1].getMyRuns(), cN[index + 1].getMyRuns(), RunsCutOff);}
		}
		else
		{
			for (int index = 1; index < length -1; index++)
			{cN[index].WrongCallHarsh(cN[index - 1].getMyRuns(), cN[index + 1].getMyRuns(), RunsCutOff, Fraction);}
		}

		SetSNPs(chromosome, cN);

	}
	return answer;
}

int AffyEngine::CleanUp()
{        
	std::vector<SNP> cN, cleanedSNPs;
	int count = 0;

	std::string t ="True";
    std::string f = "False";

	for (int c = 1; c < 23; c++)
	{
		cN = GetSNPs(c);
		int length = cN.size();

		count = 0;
		for (int index = 0; index < length; index++)
		{
			if (cN[index].getFailedData() == false)
			{count += 1;}
		}

		std::vector<SNP> cleanedSNPs(count);

		count = 0;
		for (int index = 0; index < length; index++)
		{
			if (cN[index].getFailedData() == false)
			{cleanedSNPs[count] = cN[index];
			count += 1;}
		}

		SetSNPs(c, cleanedSNPs);

	}
	return 1;
}

std::vector<std::string> AffyEngine::WriteNewDescription() 
{
	std::vector<Region> Current = GetRegions();
	std::string sb, sbInterval;
	sb = "Chromosome\tStart\tEnd\tLength\n";
	std::vector<std::string> answer;
	
	if (Current[0].End() != 1)
		{
		for (int index = 0; index < (int)Current.size(); index++) 
			{
			sb += Current[index].writeHumanString();
			sbInterval += Current[index].writeBrowserString();
			}
		}
	else
		{
		sb = "No regions";
		sbInterval = "No regions";
		}

	answer.push_back(sb);
	answer.push_back(sbInterval);

	return answer;

}

std::vector<Region> AffyEngine::GetRegions()
{

	std::vector<SNP> cN = GetSNPs(1);
	int NumberOfSNPs = cN.size() - 1;

	double LastNo = -1;
	double LastYes = -1;
	double ThisChromosomeLength;
	int here, ThisRegion;
	double RunLength = 0;

	double HomoSize = 0;
	double GenoSize = 0;

	Region thisRegion(1, 1, "1");
	std::vector<Region> Current(1, thisRegion);


	for (int ThisChromosome = 1; ThisChromosome < 23; ++ThisChromosome)
	{
		cN = GetSNPs(ThisChromosome);
		NumberOfSNPs = cN.size() - 1;
		ThisChromosomeLength = cN[NumberOfSNPs].getPosition();
		GenoSize += ThisChromosomeLength - cN[0].getPosition();
		int endOfRun = 0;
		here = 0;
		while (here < NumberOfSNPs + 1)
		{
			if (cN[here].getMyRuns() > ExclusionCutOff)
			{
				ThisRegion = here + cN[here].getMyRuns() - 1;
				if (ThisRegion > NumberOfSNPs) { ThisRegion = NumberOfSNPs; }
				RunLength = (double)(cN[ThisRegion].getPosition() - (double)(cN[here].getPosition()));
				HomoSize += RunLength;

				for (int index = here; index < ThisRegion; index++)
				{
					if (cN[index + 1].getPosition() - cN[index].getPosition() > 5000000)
					{
						HomoSize -= cN[index + 1].getPosition() - cN[index].getPosition();
					}
				}

				endOfRun = here + cN[here].getMyRuns() - 1;
				if (endOfRun > NumberOfSNPs) { endOfRun = NumberOfSNPs; }

				thisRegion = Region((int)cN[here].getPosition(), (int)cN[endOfRun].getPosition(), methods::from_Int(ThisChromosome));
				Current = AddToList(Current, thisRegion);

				/*sb += methods::from_Int(ThisChromosome) + '\t' + methods::To_NiceString(cN[here].getPosition()) + '\t' + methods::To_NiceString(cN[endOfRun].getPosition()) + '\t' + methods::To_NiceString(cN[endOfRun].getPosition() - cN[here].getPosition()) + "\n";
				sbInterval += "chr" + methods::from_Int(ThisChromosome) + ":" + methods::To_NiceString(cN[here].getPosition()) + "-" + methods::To_NiceString(cN[endOfRun].getPosition())  + "\n";
				*/here = here + cN[here].getMyRuns();
			}
			else
			{
				here += 1;
			}
		}

	}
	
	vector<Region> sized;
	for (int index = 0; index < Current.size(); index++)
	{
		if (Current[index].End() - Current[index].Start() >= 1000000)
		{ sized.push_back(Current[index]); }
	}

	return sized;

}

 std::vector<Region> AffyEngine::AddToList(std::vector<Region> Current, Region Next)
	{

	if (Current.size() == 1 && Current[0].End() == 1) 		 
		{Current[0] = Next;}
	else
		{
		Region Last = Current.back();
		if (Last.Chromosome() != Next.Chromosome())
			{Current.push_back(Next);}
		else if(Last.End() + 333000 > Next.Start())
			{
			Region newRegion(Last.Start(), Next.End(), Last.Chromosome());
			if (newRegion.End() - newRegion.Start() > 1000000)
			{ Current[Current.size()-1] = newRegion; }
			}
		else
			{ Current.push_back(Next);}
		}
				
	return Current;

	}

 void AffyEngine::setValues(parameters pars)
 {
	 Fraction = pars.Fraction;
	 AA = pars.AA;
	 BB = pars.BB;
	 setAB(pars.AB);
	 readDepth = pars.readDepth;
	 iterationNumber = pars.iterationNumber;
	 RunsCutOffProportion = pars.RunsCutOffProportion;
	 ExclusionCutOffProportion = pars.ExclusionCutOffProportion;
	 p = pars;
 }


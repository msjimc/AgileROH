#pragma once
#include <string>
#include "SNP.h"
#include <vector>
#include "methods.h"
#include "Region.h"
#include "parameters.h"
#include <cstdio>

#define FLOAT_TOL 0.000001

class AffyEngine
{
private:
    const char* theFilename;
    std::vector<SNP> c1;
    std::vector<SNP> c2;
    std::vector<SNP> c3;
    std::vector<SNP> c4;
    std::vector<SNP> c5;
    std::vector<SNP> c6;
    std::vector<SNP> c7;
    std::vector<SNP> c8;
    std::vector<SNP> c9;
    std::vector<SNP> c10;
    std::vector<SNP> c11;
    std::vector<SNP> c12;
    std::vector<SNP> c13;
    std::vector<SNP> c14;
    std::vector<SNP> c15;
    std::vector<SNP> c16;
    std::vector<SNP> c17;
    std::vector<SNP> c18;
    std::vector<SNP> c19;
    std::vector<SNP> c20;
    std::vector<SNP> c21;
    std::vector<SNP> c22;

    int GenotypeIndex;
    int SNPRSIndex;
    int ChromoIndex;
    int cmPIndex;
    int RunsCutOff;
    int ExclusionCutOff;
	int AD;
	int DP;
    int GT;

	void SortArrays();

	//geneticvaluesAndFunctions
	float Fraction;
	float AA; //0.8
	float BB; //0.2
	float lowerAB; //0.35
	float higherAB; //0.65
	int readDepth; //15
	int iterationNumber; //5
	float RunsCutOffProportion; //100
	float ExclusionCutOffProportion; //600
	parameters p;

	void setAB(float value) { lowerAB = 0.5f - value; higherAB = 0.5f + value; }

public:
    AffyEngine(void);
    AffyEngine(const char* dataFilename, parameters p, bool noRS, bool genotype);
    ~AffyEngine(void);
	int ReadVCF(const char* dataFilename, bool noRS, bool genotype);
	std::string getGenotype(std::string item, int minimumReadDepth, bool genotype);
	int ReadAffyXls(const char* dataFilename);
	int ReadBirdSeed(const char* dataFilename);
	bool searchFile(const char* Filename);
	bool searchBirdSeedFile(const char* Filename);
	bool searchVCFFile(const char* Filename, bool genotype);
	void setVectorSizes(std::vector<int> count);
    void AddtoArray(int Chromo, SNP cm, int index);
    std::vector<SNP> GetSNPs(int Chromosome);
    void SetSNPs(int Chromosome, std::vector<SNP> SNPs);
    int AnalyseDataAffy();
    int SetConstants();
    int HomozygousRun(bool Clean);
    int CleanUp();

    std::vector<std::string> WriteNewDescription(); 
	std::vector<Region> GetRegions();
    std::vector<Region> AddToList(std::vector<Region> Current, Region Next);	
	int status;

	//geneticvaluesAndFunctions
	void setValues(parameters p);
	parameters getParameters() { return p; }
};

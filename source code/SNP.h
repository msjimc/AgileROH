#pragma once
#include <string>
#include "methods.h"
#include <cstdio>
#include <cstdlib>

enum  StateFlag {Unknown = 0, Homozygous = 1};

class SNP
{

protected: 
    int TheGenotype; 
    double snpDistance;
    std::string SNPName;
    bool Failed;
    StateFlag SNPState;
    int Runs;
    bool theInCluster;
    //int RunsCutOff;
    int theChromosome;
public:
    SNP(void);
	SNP(double Distance, std::string Name, std::string Genotype, std::string Chromosome);// , int TheRunsCutOff);
    ~SNP(void);
    int Genotype();
    std::string Name();
    int getChromosome();
    double getPosition() const;
    void setPosition(double value);
    bool getInCluster();
    void setInCluster(bool value);
    StateFlag getStatus();
    bool getFailedData();
    int HomozygousRuns(int CurrentRun);
    int MaximumRun(int CurrentMaximum );
    void WrongCallHarsh(int before, int After, int globalRunsCutOff, float fraction);
    void WrongCall(int before, int After, int globalRunsCutOff);
    int getMyRuns();
    void ResetHomozygousRuns();
    bool operator <(const SNP &a) const;
	
};

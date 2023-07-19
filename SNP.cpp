#include "SNP.h"

SNP::SNP(void)
{
}

SNP::~SNP(void)
{
}

SNP::SNP(double Distance, std::string Name, std::string Genotype, std::string Chromosome)//, int TheRunsCutOff)
	{
	SNPState = Unknown;
	snpDistance = Distance;
	SNPName = Name;
	//RunsCutOff = TheRunsCutOff;
	Failed = false;

	Runs = 0;
	theInCluster = false;

	theChromosome = methods::to_Chromosome(Chromosome);
	if (theChromosome == 0)
		{Failed = true;}

	if (Genotype == "AA" || Genotype == "aa")
		{TheGenotype = 1;}
	else if (Genotype == "BB" || Genotype == "bb")
		{TheGenotype = 2;}
	else if (Genotype == "AB" || Genotype == "ab")
		{TheGenotype = 3;}
	else if(Genotype == "noCall")
		{
		TheGenotype = 0;
		Failed = true;
		}
	else
		{
		TheGenotype = 0;
		Failed = true;
		}  
	}

int SNP::getChromosome()
	{return theChromosome;}

int SNP::Genotype()
	{ return  TheGenotype;}

std::string SNP::Name()
	{return SNPName;}

double SNP::getPosition() const
	{return snpDistance;}

void SNP::setPosition(double value)
	{snpDistance = value;}

bool SNP::getInCluster()
	{return theInCluster;}

void SNP::setInCluster(bool value)
	{theInCluster = value;}

StateFlag SNP::getStatus()
	{return SNPState;}

bool SNP::getFailedData()
	{return Failed;}

int SNP::HomozygousRuns(int CurrentRun)
	{
	if (TheGenotype == 3)
		{CurrentRun = 0;}
	else if (TheGenotype > 0)
		{CurrentRun++;}

	Runs = CurrentRun;

	return CurrentRun;
	}

int SNP::MaximumRun(int CurrentMaximum)
	{ 
	if (Runs == 0)
		{CurrentMaximum = 0;}
	else if (Runs > CurrentMaximum)
		{CurrentMaximum = Runs;}
	else if (CurrentMaximum > Runs)
		{Runs = CurrentMaximum;}

	return CurrentMaximum;
	}

void SNP::WrongCallHarsh(int before, int After, int globalRunsCutOff, float fraction)
	{
	int theTest = (int)((globalRunsCutOff * fraction) + 0.5f);
	if (Runs == 0)
		{
		if (before + After >= globalRunsCutOff)
			{
			if (before > theTest && After > theTest)
				{ Failed = true; }	
			}           
		}
	}

void SNP::WrongCall(int before, int After, int globalRunsCutOff)
	{
	if (Runs == 0)
		{
		if (before + After >= globalRunsCutOff)
			{
				{Failed = true;}
			}
		}
	}
int SNP::getMyRuns() 
	{
	return Runs;
	}

void SNP::ResetHomozygousRuns()
	{Runs = 0;}

bool SNP::operator <(const SNP &a) const
	{ 
	if (snpDistance < a.getPosition())
		{return true;}
	else{return false;}
}


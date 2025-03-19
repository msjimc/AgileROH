#include "parameters.h"

void parameters::combineTwoSets(parameters one, parameters two)
{

	score = 0;
	
	if ((rand() % 100 + 1) > 50)
	{ AA = one.AA; }
	else
	{ AA = two.AA; }

	if ((rand() % 100 + 1) > 50)
	{ BB = one.BB; }
	else
	{ BB = two.BB; }

	if ((rand() % 100 + 1) > 50)
	{ AB = one.AB; }
	else
	{ AB = two.AB; }

	if ((rand() % 100 + 1) > 50)
	{ readDepth = one.readDepth; }
	else
	{ readDepth = two.readDepth; }

	if ((rand() % 100 + 1) > 50)
	{ iterationNumber = one.iterationNumber; }
	else 
	{ iterationNumber = two.iterationNumber; 
	}
		
	if ((rand() % 100 + 1) > 50)
	{ RunsCutOffProportion = one.RunsCutOffProportion; }
	else
	{ RunsCutOffProportion = two.RunsCutOffProportion; }
		
	if ((rand() % 100 + 1) > 50)
	{ ExclusionCutOffProportion = one.ExclusionCutOffProportion; }
	else
	{ ExclusionCutOffProportion = two.ExclusionCutOffProportion; }
	
	if ((rand() % 100 + 1) > 50)
	{ Fraction = one.Fraction; }
	else
	{ Fraction = two.Fraction; }
	
}

void parameters::mutate()
{
	score = 0;
	
	if ((rand() % 100 + 1) > 80)
	{
		float answer = 5.0f + (float)(rand() / (RAND_MAX / 30));
		AA = 1.0f - (answer / 100.0f);
		//AA = (AA + (1.0f - (answer / 100.0f))) / 2;
	}
	
	if ((rand() % 100 + 1) > 80)
	{
		float answer =  5.0f + (float)(rand() / (RAND_MAX / 30));
		BB = answer / 100.0f;
		//BB = (BB + (answer / 100.0f)) / 2;
	}
	
	if ((rand() % 100 + 1) > 80) 
	{
		float answer =  0.0f + (float)(rand() / (RAND_MAX / 35));
		AB = answer / 100.0f;		
		//AB = (answer + AB) / 2;
	}
	
	if ((rand() % 100 + 1) > 80) 
	{
		float answer =  1.0f + (float)(rand() / (RAND_MAX / 40));
		Fraction = answer / 100.0f;		
		//AB = (answer + AB) / 2;
	}
	
	if ((rand() % 100 + 1) > 80)
	{
		readDepth = (5 + rand() / (RAND_MAX / 40));
	}
	
	if ((rand() % 100 + 1) > 80)
	{
		iterationNumber = (3 + rand()/ (RAND_MAX / 5));
	}	

	if ((rand() % 100 + 1) > 80)//
	{
		RunsCutOffProportion = (75 + rand() / (RAND_MAX / 500));
	}	

	if ((rand() % 100 + 1) > 80)// 
	{
		ExclusionCutOffProportion = (400 + rand() / (RAND_MAX / 1100)) ;
	}	
}

void parameters::MakeNewValues()
{
	score = 0;
	
	float answer = 5.0f + (float)(rand() / (RAND_MAX / 30));
	AA = 1.0f - (answer / 100.0f);

	answer =  5.0f + (float)(rand() / (RAND_MAX / 30));
	BB = answer / 100.0f;

	answer = 5.0f + (float)(rand() / (RAND_MAX / 30));
	AB = answer / 100.0f;

	answer = 1.0f + (float)(rand() / (RAND_MAX / 40));
	Fraction = answer / 100.0f;

	readDepth = 0.0f + rand() / (RAND_MAX / 40);

	iterationNumber = 3 + rand()/ (RAND_MAX / 5);

	RunsCutOffProportion = 75 + rand() / (RAND_MAX / 500);

	ExclusionCutOffProportion = 400 + rand() / (RAND_MAX / 1100);

}

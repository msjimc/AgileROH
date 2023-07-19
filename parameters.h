#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include "methods.h"

using namespace std;

class parameters {
public:
	parameters() { score = 0; };
	parameters(bool newOne) { MakeNewValues(); score =0; }
	~parameters() { };
	
	long long score;
	
	float AA; //0.8
	float BB; //0.2
	float AB; //0.65
	float Fraction; //0.2
	int readDepth; //15
	int iterationNumber; //5
	int RunsCutOffProportion; //100
	int ExclusionCutOffProportion; //600
		

	void combineTwoSets(parameters one, parameters two);
	void mutate();
	void MakeNewValues();
	void setScore(long long  value){ score = value; }
	long long getScore(){ return score; }

	std::string to_string(){ return "AA: " + methods::from_Double((double)AA) + 
		" BB: " + methods::from_Double((double)BB) + 
		" AB: " + methods::from_Double((double)AB) + 
		" Fraction: " + methods::from_Double((double)Fraction) +
		" Read depth: " + methods::from_Int(readDepth) + 
		" Iteration Number: " + methods::from_Int(iterationNumber) + 
		" Runs CutOff Proportion: " + methods::from_Int(RunsCutOffProportion) + 
		" ExclusionCutOffProportion: " + methods::from_Int(ExclusionCutOffProportion) + "\n"; }

	std::string to_EXCEL() {
		return methods::from_Double((double)AA) +
			"\t" + methods::from_Double((double)BB) +
			"\t" + methods::from_Double((double)AB) +
			"\t" + methods::from_Double((double)Fraction) +
			"\t" + methods::from_Int(readDepth) +
			"\t" + methods::from_Int(iterationNumber) +
			"\t" + methods::from_Int(RunsCutOffProportion) +
			"\t" + methods::from_Int(ExclusionCutOffProportion) + "\n";
	}

	static std::string excel_title() {
		return "AA\tBB\tAB\tFraction\tRead depth\tIteration Number\tRunsCutOff Proportion\tExclusionCutOff Proportion\n";
	}

private:


};
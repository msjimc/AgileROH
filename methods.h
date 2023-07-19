#pragma once
#include "string"
#include <vector>
#include <sstream>
#include <string>

class methods
{
public:
    methods(void);
    ~methods(void);

    static std::vector<std::string> Split(std::string line, char delimitor);
    static double to_Double(std::string);
    static int to_Integer(std::string s);
	static int to_Chromosome(std::string s);
    static std::string from_Double(double d);
    static std::string from_Int(int i);
    static std::string To_NiceString(double number);
};

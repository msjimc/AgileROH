#include "methods.h"


methods::methods(void)
{
}

methods::~methods(void)
{
}

std::vector<std::string> methods::Split(std::string line, char delimitor)
{
    std::string item;
    int counter =0;
    std::stringstream ss(line);
    while (std::getline(ss, item, delimitor)) {
        counter++;
    }

    std::vector<std::string> items(counter);
    counter=0;
    std::stringstream sss(line);
    while (std::getline(sss, item, delimitor)) {
        items[counter] = item;
        counter++;
    }
    return items;
}

double methods::to_Double(std::string s)
{
    std::istringstream i(s);
    double x;
    if (!(i >> x))
    {return 0;}
   return x;
 } 

int methods::to_Chromosome(std::string s)
	{
	if (s.substr(0, 1) == "c" || s.substr(0, 1) == "C")
		{s = s.substr(3, s.size() - 3);}
	return methods::to_Integer(s);
	}

int methods::to_Integer(std::string s)
{
    std::istringstream i(s);
    int x;
    if (!(i >> x))
    {return 0;}
   return x;
 } 

std::string methods::from_Double(double d)
{
    std::ostringstream strs;
    strs << d;
    std::string str = strs.str();
    return str;
}

std::string methods::from_Int(int i)
{
    std::ostringstream strs;
    strs << i;
    std::string str = strs.str();
    return str;
}

std::string methods::To_NiceString(double number)
{
    double i = 1;
    std::string answer;
    while (i < number)
    {
        i = i * 10;
    }

    while (i >= 1 && number > 0)
    {
        i = i / 10;

        switch ((int)(number / i))
        {
        case 0:
            answer += "0";
            break;
        case 1:
            answer += "1";
            number = number -(i * 1);
            break;
        case 2:
            answer += "2";
            number = number -(i * 2);
            break;
        case 3:
            answer += "3";
            number = number -(i * 3);
            break;
        case 4:
            answer += "4";
            number = number -(i * 4);
            break;
        case 5:
            answer += "5";
            number = number -(i * 5);
            break;
        case 6:
            answer += "6";
            number = number -(i * 6);
            break;
        case 7:
            answer += "7";
            number = number -(i * 7);
            break;
        case 8:
            answer += "8";
            number = number -(i * 8);
            break;
        case 9:
            answer += "9";
            number = number -(i * 9);
            break;
        case 10:
            answer += "1";
            number = number - (i * 10);

        }
    }

while (i >1)
{
    answer += "0";
    i = i / 10;
}

return answer;
}
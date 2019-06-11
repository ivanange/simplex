#ifndef DEF_INEQUATION
#define DEF_INEQUATION

#include<string>
#include<vector>
#include<functional>
#include <limits>

#include "Lineaire.h"

const float INF = std::numeric_limits<float>::infinity(); 

class Equation;

class Inequation : public Lineaire {
	
	public:
	Inequation();
	Inequation(Equation equation, std::string seperator);
	Inequation( std::vector<Terme> leftside, std::vector<Terme> rightside, std::string seperator);
	Inequation(std::string data);
	void subject( char letter);
	std::pair<float, float> solve(char letter, std::map<char, float> substitutes);

	
};

#endif

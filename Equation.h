#ifndef DEF_EQUATION
#define DEF_EQUATION

#include<string>
#include<vector>
#include<functional>

#include "Lineaire.h"

class Inequation;

class Equation : public Lineaire {
	
	public:
	Equation();
	Equation( Inequation inequation, Terme terme);
	Equation( std::vector<Terme>leftside, std::vector<Terme> rightside);
	Equation(std::string data);
	void subject( char letter);
	float solve(char letter, std::map<char, float> substitutes);

	
};

#endif

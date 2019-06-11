#ifndef DEF_LINEAIRE
#define DEF_LINEAIRE

#include<string>
#include<vector>
#include<functional>
#include<algorithm>
#include<map>

#include "Terme.h"


class Lineaire {
	
	public:
	Lineaire();
	Lineaire(std::string data, std::string seperator);
	Lineaire( std::vector<Terme> leftside, std::vector<Terme> rightside, std::string seperator);
	std::vector<Terme> left(void);
	std::vector<Terme> right(void);
	std::string seperator(void);
	void addLeft( Terme terme);
	void addRight( Terme terme);
	std::string toString();
	void substitute(char letter, Terme terme);
	void substitute(Terme terme);
	void substitute( std::map<char, float> substitutes);
	void substitute(char letter, std::vector<Terme> termes);
	std::vector<Terme>::iterator findTerme( char letter, char side);
	std::string& ltrim(std::string& str);
	std::string& rtrim(std::string& str);
	std::string& trim(std::string& str);
	
	protected:
	std::vector<Terme> _leftSide;
	std::vector<Terme> _rightSide;
	std::string _seperator;
	void parse( void );
	
	
};

std::vector<Terme> & operator/( std::vector<Terme> &vectTerme, float number);
std::vector<Terme> & operator*( std::vector<Terme> &vectTerme, float number);
std::vector<Terme> & operator/( float number , std::vector<Terme> &vectTerme );
std::vector<Terme> & operator*( float number , std::vector<Terme> &vectTerme );



#endif

#ifndef DEF_TERME
#define DEF_TERME

#include<iostream>
#include<string>
#include<sstream>

char const DEFAULT_CHAR = '?';

class Terme {
	
	public:
	Terme();
	Terme( float coff, char letter=DEFAULT_CHAR);
	char letter() const;
	void letter( char letter);	
	float coff() const;
	void coff( float number);
	std::string toString() const; 
	
	private:
	char _letter;
	float _coff;

	
	char getLetter() const;
	void setLetter( char letter );
	float getCoff() const;
	void setCoff(float number);
	bool isEmpty() const;

};

Terme  operator+( const Terme &terme1, const Terme &terme2);
Terme  operator-( const Terme &terme1, const Terme &terme2);

#endif

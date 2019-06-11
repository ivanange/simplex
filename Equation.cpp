#include "Equation.h"
#include "Inequation.h"

#include<iostream>

using namespace std;

	Equation::Equation() {}

	Equation::Equation( Inequation inequation, Terme terme) : Lineaire( inequation.left(), inequation.right(), string("=") ) {
		addLeft(terme);
	}
	Equation::Equation( vector<Terme> leftside, vector<Terme> rightside): Lineaire(leftside, rightside, string("=")  )  {	}
	Equation::Equation(std::string data): Lineaire(string(data), string("=") )  {	}
	void Equation::subject( char letter) {
		Terme rightTerme, leftTerme;
		
		auto right = findTerme(letter, 'R');
		auto left = findTerme(letter, 'L');
		
		if(left == _leftSide.end() && right == _rightSide.end()) {	 throw( string("Trying to make inexistent ") + letter + string(" terme the subject") );	}
		if(  left == _leftSide.end() ) {	leftTerme = 	Terme(0, letter); 	}
		else { leftTerme =  (*left); _leftSide.erase(left);  }
		if( right == _rightSide.end() ) {  rightTerme = Terme(0, letter);	}
		else {  rightTerme = (*right); _rightSide.erase(right); }
		
		Terme subject = leftTerme - rightTerme;
		_leftSide*(-1);
		_rightSide.insert( _rightSide.end(), _leftSide.begin(), _leftSide.end() );
		_rightSide/subject.coff();
		_leftSide.clear(); 
		subject.coff(1);
		_leftSide.push_back(subject);
		parse();
		

	}
	float Equation::solve(char letter, map<char, float> substitutes) {
		try {	subject(letter);	} catch(...){	}
		substitute(substitutes);
		if(_rightSide.size() != 1) {	cout<< toString();  throw("Not enough substitutes");	}
		return _rightSide[0].coff();
		
	}

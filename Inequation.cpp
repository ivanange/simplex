#include "Inequation.h"
#include "Equation.h"

#include<iostream>

using namespace std;

	Inequation::Inequation() {	}
	Inequation::Inequation(Equation equation, std::string seperator) : Lineaire(equation.left(), equation.right(), seperator  ) {}												
	Inequation::Inequation( std::vector<Terme> leftside, std::vector<Terme> rightside, string seperator): Lineaire(leftside, rightside, seperator  ) {}
	Inequation::Inequation(std::string data) : Lineaire(data, data.find("<=") != string::npos ? "<=" : ( data.find(">=") != string::npos ? ">=" : (data.find("<") != string::npos ? "<" : ">"))) {}
	void Inequation::subject( char letter) {
		Terme rightTerme, leftTerme;
		
		auto right = findTerme(letter, 'R');
		auto left = findTerme(letter, 'L');
		
		if(left == _leftSide.end() && right == _rightSide.end()) {	cout<< toString();	throw( string("Trying to make inexistent ") + letter + string(" terme the subject of inequation") );	}
		if(  left == _leftSide.end() ) {	leftTerme = 	Terme(0, letter); 	}
		else { leftTerme =  (*left); _leftSide.erase(left);  }
		if( right == _rightSide.end() ) {  rightTerme = Terme(0, letter);	}
		else {  rightTerme = (*right); _rightSide.erase(right); }
		
		Terme subject = leftTerme - rightTerme;
		_leftSide*(-1);
		_rightSide.insert( _rightSide.end(), _leftSide.begin(), _leftSide.end() );
		if(subject.coff() < 0 ){
			_seperator[0] =  _seperator[0]=='>' ? '<' : '>';		
		}
		_rightSide/subject.coff();
		_leftSide.clear(); 
		subject.coff(1);
		_leftSide.push_back(subject);
		parse();
	}
	std::pair<float, float> Inequation::solve(char letter, std::map<char, float> substitutes) {
		std::pair<float, float> minMax;
		try {	subject(letter);	} catch(...){	}
		substitute(substitutes);
		if(_rightSide.size() != 1) {	cout<< toString(); throw("Not enough substitutes");	}
		if( _seperator[0] == '>'){
			minMax.first = _rightSide[0].coff();
			minMax.second = INF;
		}
		else {
			minMax.first = INF;
			minMax.second = _rightSide[0].coff();
		}
		
		return minMax;
	}

#include "Lineaire.h"

#include<iostream>
 
using namespace std;

	Lineaire::Lineaire() {}
	
	Lineaire::Lineaire( vector<Terme> leftside, vector<Terme> rightside, std::string seperator) {
		_leftSide = leftside;
		_rightSide = rightside;
		_seperator = seperator;
		parse();
	}
	
	Lineaire::Lineaire(std::string data, std::string seperator) {
		
		string leftString , rightString;
		vector<string> seperators = { "<", "<=", ">", ">=", "="};
		
		
		if( std::find(seperators.begin(), seperators.end(), seperator) != seperators.end() ) { 
			_seperator = seperator;
		}
		else {	throw("Separateur non valide");	}
		
		function<vector<Terme>(string &)> parser = [=]( string & side ) -> vector<Terme> {  
			vector<Terme> result;
			string strTerme;
			bool fin = true;
			string sign;
			int i;
			char lastchar;
			 
			trim(side);
			if( side.find_first_of("+-") == 0 ) { 	sign = side[0]; side.erase(side.begin());	 } 
			  
			while( fin ) {
			 	trim(side);
			 	i = side.find_first_of("+-");
				i = i != string::npos ? i : ((fin = false), side.size()); 
			 	strTerme = side.substr(0, i);
			 	strTerme = sign + trim(strTerme);
			 	sign = side[i];
			 	if( i < side.size() ) { side = side.substr(i+1); }
			 	string::iterator it  = strTerme.end(); it--;
			 	lastchar = (char)(*it);
			 	
			 	
			 	if( lastchar >= 'A' && lastchar <= 'z') {
			 		strTerme.erase(it);
			 		i = strTerme.find_first_of("+-");
			 		if( i != string::npos && strTerme.size() == 1 ) { strTerme += "1";	 }
			 		result.push_back( Terme( ( strTerme.size() == 0 ? 1 : stoi(strTerme) ), lastchar) );
				}
				else { result.push_back( Terme( stoi(strTerme) ) );		 }
			}
			return result;
		}; 
				
		unsigned seperatorPosition = data.find(_seperator);
		
		leftString = data.substr(0, seperatorPosition );
		rightString = data.substr(seperatorPosition + _seperator.size() );
		_leftSide = parser(leftString);
		_rightSide = parser(rightString);
		parse();
	}
	
	std::vector<Terme> Lineaire::left() {
		return _leftSide;
	}
	
	std::vector<Terme> Lineaire::right() {
		return _rightSide;
	}
	
	std::string Lineaire::seperator(void) {
		return _seperator;
	}
	
	
	void Lineaire::addLeft( Terme terme) {
		_leftSide.push_back(terme);
		parse();
	}
	
	void Lineaire::addRight( Terme terme) {
		_rightSide.push_back(terme);
		parse();
	}
	
	std::string Lineaire::toString() {
		
		function<string(vector<Terme>)> serializer = []( const vector<Terme> & side ) -> string {  
			 string result;
			 for( auto it = side.begin(); it!= side.end(); ++it) {
			 	result += (*it).toString()+" ";
			 }
			 result =  (result.find_first_of("+") ==0 ) ?  result.substr(1) : result; 
			 return result;
		};
		
		return serializer(_leftSide) + _seperator + " " + serializer(_rightSide);		
	}
	
	void Lineaire::substitute(char letter, Terme terme) {
	
		function<void( vector<Terme> &)> substitutor = [=](  vector<Terme> & side ) {  
			for( vector<Terme>::iterator it = side.begin(); it!= side.end(); ++it) {
			 	if( (*it).letter() == letter ) {
			 		(*it).letter(terme.letter());
			 		(*it).coff( (*it).coff() * terme.coff() );
				 } 
			}
		};
		
		substitutor(_leftSide);
		substitutor(_rightSide);
		parse();
			 
	}
	
	void Lineaire::substitute(Terme terme) {
		substitute(terme.letter(), terme);
	}
	
	void Lineaire::substitute( map<char, float> substitutes) {
		for( map<char, float>::iterator it = substitutes.begin(); it!= substitutes.end(); it++ ) {
			substitute((*it).first, Terme((*it).second) );
		}
	}
	
	void Lineaire::substitute(char letter, std::vector<Terme> termes) {
		vector<Terme> copy = termes;
		auto left = Lineaire::findTerme(letter, 'L');
		if( left != _leftSide.end()) {
			termes*(*left).coff();
			_leftSide.erase(left);
			_leftSide.insert( _leftSide.end(), termes.begin(), termes.end() );
		}
		
		auto right = Lineaire::findTerme(letter, 'R');
		if( right != _rightSide.end()) {
			copy*(*right).coff();
			_rightSide.erase(right);
			_rightSide.insert( _rightSide.end(), copy.begin(), copy.end() );
		}
		
		parse();
	}
	
	std::vector<Terme>::iterator Lineaire::findTerme( char letter, char side) {
		switch(side){
			parse();
			case 'L' : 
				for( vector<Terme>::iterator it = _leftSide.begin(); it!= _leftSide.end(); ++it) {
					if( (*it).letter() == letter ) {
					return it;
					}
				}
				return _leftSide.end();
				break;
				
			case 'R' : 
				for( vector<Terme>::iterator it = _rightSide.begin(); it!= _rightSide.end(); ++it) {
					if( (*it).letter() == letter ) {
						return it;
					}
				}
				return _rightSide.end();
				
		
			default : throw("No side given"); break;
		}
		
	}
	
	void Lineaire::parse() {
	
		function<vector<Terme>(vector<Terme> &)> parser = [=](  vector<Terme> & side ) -> vector<Terme> { 
		
			vector<char> letters;
			vector<Terme> result; 
			char ref;
			for( vector<Terme>::iterator it = side.begin(); it!= side.end(); ++it) {
				ref = (*it).letter();
				if( std::find(letters.begin(), letters.end(), ref ) == letters.end() ) {
					letters.push_back(ref);
				}
			}
			
			for( vector<char>::iterator cit = letters.begin(); cit!= letters.end(); ++cit) {
				Terme anchor(0, (*cit));
				for( vector<Terme>::iterator it = side.begin(); it!= side.end(); ++it) {
					
				 	if( (*cit) == (*it).letter() ) {
						anchor = anchor + (*it);
				 	}
				}
				result.push_back(anchor);
			}
			
			return result;
		};
			
		_leftSide = parser(_leftSide);
		_rightSide = parser(_rightSide);
		
	}
	
	std::string& Lineaire::ltrim(std::string& str) {
		const std::string chars = "\t\n\v\f\r ";
    	str.erase(0, str.find_first_not_of(chars));
    	return str;
	}
 
	std::string& Lineaire::rtrim(std::string& str) {
		const std::string chars = "\t\n\v\f\r ";;
    	str.erase(str.find_last_not_of(chars) + 1);
    	return str;
	}
 
	std::string& Lineaire::trim(std::string& str){
    	return ltrim(rtrim(str));
	}
	
	vector<Terme> & operator/( vector<Terme> &vectTerme, float number) {
		for( vector<Terme>::iterator it = vectTerme.begin(); it!= vectTerme.end(); ++it) {
			(*it).coff( (*it).coff() / number );
		}
		return vectTerme;
	}
	
	vector<Terme> & operator*( vector<Terme> &vectTerme, float number) {
		for( vector<Terme>::iterator it = vectTerme.begin(); it!= vectTerme.end(); ++it) {
			(*it).coff( (*it).coff() * number );
		}
		return vectTerme;
	}
	
	vector<Terme> & operator/( float number , vector<Terme> &vectTerme ) {
		for( vector<Terme>::iterator it = vectTerme.begin(); it!= vectTerme.end(); ++it) {
			(*it).coff( (*it).coff() / number );
		}
		return vectTerme;
	}
	
	vector<Terme> & operator*( float number , vector<Terme> &vectTerme ) {
		for( vector<Terme>::iterator it = vectTerme.begin(); it!= vectTerme.end(); ++it) {
			(*it).coff( (*it).coff() * number );
		}
		return vectTerme;
	}
	
	
	
	

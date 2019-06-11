 
#include "Terme.h"

using namespace std;


	Terme::Terme() {
	}
	Terme::Terme(float coff, char letter) {
		_coff = coff;
		_letter = letter;
	}
	
	char Terme::getLetter() const {
		return ( _letter);
	}
	
	void Terme::setLetter( char letter ) {
		if( (letter >= 'A' and letter <= 'z') || letter==DEFAULT_CHAR ) {
			_letter =  letter;
		}	
	}
	
	float Terme::getCoff() const {
		return _coff;
	}
	
	void Terme::setCoff(float number) {
			_coff =  number;
	}
	
	char Terme::letter() const {
		return getLetter();
	}
		
	void Terme::letter( char letter ) {
		setLetter(letter);
	}
	
	float Terme::coff() const {
		return getCoff();
	}
	
	void Terme::coff( float number) {
		setCoff(number);
	}
	
	bool Terme::isEmpty() const {
		return _letter==DEFAULT_CHAR;
	}
	
	string Terme::toString() const{
		stringstream coff;
		coff<<_coff;
		return ( _coff>=0 ? "+ " : "") + ( (_coff ==1 && _letter != DEFAULT_CHAR) ? "" :   (_coff ==-1 && _letter != DEFAULT_CHAR) ? "-" : coff.str()) + (isEmpty() ? ' ' : _letter);
	} 
	
	Terme  operator+( const Terme &terme1, const Terme &terme2) {
		if(terme1.letter() != terme2.letter() ) {	throw("Erreur, on ne peut additioner deux terme different ");}
		return Terme( (terme1.coff() + terme2.coff()),  terme1.letter() );
	}
	
	Terme  operator-( const Terme &terme1, const Terme &terme2) {
		if(terme1.letter() != terme2.letter() ) {	throw("Erreur, on ne peut soustraire deux terme different ");}
		return Terme( (terme1.coff() - terme2.coff()),  terme1.letter() );
	}


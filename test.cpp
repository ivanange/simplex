#include<iostream>
#include "Terme.h"

using namespace std;


int main () {
	int i;
	char a = 'e';
	std::string c, b = "yes";
	a = 'b';
	c = "yes";
	Terme test(3);
	cout<<test.coff()<<test.letter()<<endl;
	test.letter('Y');
	test.coff(0);
	cout<<test.toString()<<endl;	
	std::cout<<a<<endl<<( c == b)<<endl<<(char)b[0]<<std::endl;

}



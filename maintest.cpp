/*

#include<iostream>
#include<string>
#include<map>
#include "Equation.h"
#include "Inequation.h"



using namespace std;

int main () {
	try {
		
	map<char, float> values;
	values['y'] = 1;
	values['E'] = 0;
		
	Equation Z( string("7x + 3y + 5x = 4z + 2x + 6 "));
	Equation W( string("7x + 3y + 5x =  2x + 6 + 8"));
	Inequation Y( string("7x + 3y + 5x >=  2x + 6 + 8"));
	W = Equation(Y, Terme(1, 'E'));
	Y = Inequation(W, ">=");
	Z.subject('y');
	Y.subject('y');
	pair<float, float> result = Y.solve('x', values);
	cout<<"Z :"<<Z.toString()<<endl<<"W: "<<W.toString()<<endl;
	cout<<"W: "<<W.solve('x', values)<<endl<<"Y : "<<Y.toString()
		<<endl<<"Y: min:"<<result.first<<" max:"<<result.second<<endl<<(char)('A'+1);
	
	}
	catch(char const* const& err) {
		string error = err;
		cout<<error;
	}
	
}
*/

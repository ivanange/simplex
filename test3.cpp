#include<iostream>
#include<string>
#include<map>

using namespace std;

void f( char, int);
void f(int, char);

int main() {
	string s ="hello0";
	map<char , int> etat;
	etat['X'] = 4;
	etat.erase('X');


	
	
	string::iterator it = s.end();
	it--;
	cout<<((char)(*it));
	//cout<<s.size()<<*it<<stoi("-200")<<(etat.find('X') == etat.end())<<((char)s.c_str()[0])<<s.find_first_of("l")<<( s.find_first_of("r") == string::npos);
	
	int i = s.find_first_of("+-o");	
	i = s.size();
	cout<<s[i]<<stoi("-34-");
	if( i < s.size() ) { s = s.substr(i); }
	string s2 = "f"+s;
	cout<<s2[0];
	s2.erase(0);
	cout<<endl<<s<<s.size()<<endl<<s2;

}

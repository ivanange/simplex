#include<iostream>
#include<string>

using namespace std;

int main() {
	string a = to_string(134);
	char b = (char)a[0];
	cout<<a<<"\t"<<b;
}

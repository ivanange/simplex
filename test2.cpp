#include<iostream>
#include<string>
#include "Terme.h"

#include "json.hpp"

using json = nlohmann::json;
using namespace std;

    void to_json(json &j,  const Terme &terme ) {
    	float coff = terme.coff() ;
    	char letter = terme.letter();
        j = json{{"coff", coff}, {"letter", std::string(1, letter) } };
    }

    void from_json(const json &j, Terme &terme) {
    	float a=j.at("coff");;
    	char b=j.at("letter").get<std::string>()[0];
        terme.coff((float)(a));
        terme.letter((char)b);
    }
    
    std::vector<Terme> create() {
    	std::vector<Terme> vect = {Terme (4, 'Y'), Terme(10, 'Z') };
    	return vect;
	} 
json fjson( json &embed, string key)  {
	
	/* json* me = embed[key]; */
	
	nlohmann::json::iterator it = embed[key].begin();
	cout<<(*it).get<Terme>().letter()<<endl;
	return *it;

}

int main () {
	
	json embed = { {"client", {Terme (4, 'Y'), Terme(10, 'Z')} }, {"something", 4} };
	string key("client");

	Terme terme(3, 'X'), test;
	std::vector<Terme> test2;
	test2 = create();
	json jterme = terme;
	
	Terme term = terme;
	
	term.coff(15);
	std::cout<<test2[0].toString()<<"\n"<<term.toString()<<"\n"<<terme.toString()<<"\n";
	
	jterme["termes"] = { (Terme (4, 'Y')), (Terme(10, 'Z'))};
	
	Terme terme3 = jterme["termes"][1].get<Terme>();
	terme3.coff(9);
	jterme["termes"][1] = terme3;
	std::vector<Terme> terms = jterme["termes"].get<std::vector<Terme>>();
	
	std::cout<<jterme<<"\n"<<terms[0].toString()<<"\n";
	
	Terme terme2 = jterme.get<Terme>(); 
	std::cout<<terme2.toString()<<"\n";
	cin>>jterme;
	
	
json j2 = {
  {"pi", 3.141},
  {"happy", 34},
  {"name", "Niels"},
  {"nothing", nullptr},
  {"answer", {
    {"everything", 42}
  }},
  {"list", {1, 0, 2}},
  {"object", {
    {"currency", "USD"},
    {"value", 42.99}
  }}
};
	j2["list"].push_back(4);

	std::cout<<j2;
}



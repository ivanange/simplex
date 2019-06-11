#include<iostream>
#include<string>
#include <algorithm>
#include<map>

#include "Equation.h"
#include "Inequation.h"
#include "utility.h"

using namespace std;

  
int main () {
	

	
	try {
		
		initialize();  
		//mets sous forme standard et on fait une copie 
		contrainteStansard = standardize( contrainteCanonique ); 
		 
		
		while(  !negatif(fonctionEconomique ) ) { 
			
			
			i=0;
			// determine la variable entrante(VE)  
			copyEquations = contrainteStansard; 
			entrant = max(VHBCoff);
			VB.insert(entrant);  
			VHB.erase( entrant.first);
			VHBCoff.erase( entrant.first); 
			
			
			// on resou les nouvelle equations avec la VE avec VB >= 0  
			solveInequations(); 
			VB[entrant.first] = entrantValue;
		 
			// reecrit les equation en fonction des nouvelles VB  
			substitute();   
			
			cout<<endl<<fonctionEconomique.toString()<<endl;    
			 
		}   

		for( i=0; i<contrainteStansard.size(); i++ ) {
			VB[ciVB[i]] = contrainteStansard[i].solve(ciVB[i], VHB );
		}
		
		VHB.insert(result.begin(), result.end());
		std::swap(VHB, result);
		VB.insert(result.begin(), result.end());
		std::swap(VB, result); 

		/*  ***** ***** FIN, FAIRE QUELQUES CHOSE AVEC LES RESULTAT DANS result   dans result  ************/

		cout<<"W : "<<vraie_fonctionEconomique.solve('w', result)<<endl;
		for( auto it = result.begin(); it!= result.end(); it++) {
			cout<<(*it).first<<" : "<<(*it).second<<" ";
		}

	} 
	
		
	// ON attrape toute les erreurs
	
	catch(char const* const& err) {
		string error = err; 
		cout<<error;
	}
	
	catch(string const& err) {
		string error = err;
		cout<<error;
	}   
	 
	catch(...) {
		cout<<"Something Went wrong";
	} 
	
	
}

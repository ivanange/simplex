using namespace std;

const string MAX = "MAX";
const string MIN = "MIN";

// global variables
string operation;
Equation fonctionEconomique;
Equation vraie_fonctionEconomique;
vector<Terme> substitution;
vector<Equation> contrainteStansard;
vector<Equation> copyEquations;
vector<Inequation> contrainteCanonique;
map<char, float> VHB ;
map<char, float> VHBCoff ;
map<char, float> VB;
map<char, float> result;
pair<char, float> sortant;
pair<char, float> entrant;
pair<float, float> minMax;	
vector<char> ciVB;
float entrantValue;
int ci, i = 0;	
bool (* fonction)( Equation & );

// utility fonctions

vector<Equation> standardize( vector<Inequation> vect ) {
	
	vector<Equation> result;
	int i = 0, number; 
	char letter;
	
	function<void(Inequation &)> transform = [&]( Inequation & inequation )  {
		letter = (char)('A'+i++); 
		number = inequation.seperator().find("<") != string::npos ?  1 : -1 ;
		Equation Y = Equation( inequation, Terme(number, letter) ) ;
		Y.subject(letter);
		cout<<endl<<Y.toString()<<endl;
		result.push_back(Y);
		VB[letter] = 0;
		ciVB.push_back(letter);
	};
	
	for_each( vect.begin(), vect.end(), transform);
	
	return result;
	
}

pair<char, float> max(map<char, float> results) {
	return (*std::max_element(results.begin(), results.end(), [] (const pair<char,float>& a, const pair<char, float>& b)->bool{ return a.second < b.second; } ));
}

pair<char, float> min(map<char, float> results) {
	return (*std::min_element(results.begin(), results.end(), [] (const pair<char,float>& a, const pair<char, float>& b)->bool{ return a.second < b.second; } ));
}

bool positif( Equation & equation ) {
	bool test = true;
	for( auto it = VHB.begin(); it != VHB.end(); it++) {
		
		if( (*equation.findTerme((*it).first , 'R') ).coff() < 0  )  {
			test = false;
			break;
		}
	}
	return test;
}

bool negatif( Equation & equation ) {
	bool test = true;
	for( auto it = VHB.begin(); it != VHB.end(); it++) {
		
		if( (*equation.findTerme((*it).first , 'R') ).coff() > 0  )  {
			test = false;
			break;
		}
	}
	return test;
}


// initialization, and simplexe fonctions

void solveInequations() {
	ci = 0;
	minMax = Inequation( copyEquations[0].right(), vector<Terme>{ Terme(0) }, string(">=") ).solve( entrant.first, VHB );
	for_each( copyEquations.begin() +1, copyEquations.end(), 
		[&](Equation & eq) {
			pair<float, float> next;
			i++;
			next = Inequation(eq.right(), vector<Terme>{ Terme(0) }, string(">=")  ).solve(entrant.first, VHB);
			if( next.second != INF and next.second >= 0 ) {	minMax = minMax.second > next.second ? ((ci=i), next) : minMax;	}			
		});
	entrantValue =  minMax.second;
}

void substitute() {
	contrainteStansard[ci].subject(entrant.first);
	substitution = contrainteStansard[ci].right();
	fonctionEconomique.substitute(entrant.first, substitution);
	
	i=0;
	for_each( contrainteStansard.begin(), contrainteStansard.end(),
		[&](Equation & eq) {
			if( ci != i) {
				eq.substitute(entrant.first, substitution);
				cout<<eq.toString()<<endl;
			}
			else {
				
				sortant.first= ciVB[i];
				ciVB[i] = entrant.first;
				VHB[sortant.first] = 0;
				cout<<eq.toString()<<endl;
				
			} 
			i++;
			
		});
	for( auto it = VHB.begin(); it!= VHB.end(); ++it ) {
		VHBCoff[ (*it).first] = (*fonctionEconomique.findTerme( (*it).first, 'R')).coff();
	}
}

void initialize() {
	
	operation = MIN;	// opretation MAX ou MIN
	vraie_fonctionEconomique = Equation(" w =  -x + y "); // fontion economique
	contrainteCanonique =  { Inequation("2x - y >= -2"), Inequation("-x + 3y >= -2 "), Inequation(" -x -y >= -4")	};	// initialise les contraintes

/*
	vraie_fonctionEconomique = Equation(" w =  x - 7y + 3z "); // fontion economique
	contrainteCanonique =  { Inequation("2x + y -z <= 4"), Inequation("4x - 3y <= 2"), Inequation("-3x + 2y + z <= 3")	};	// initialise les contraintes

	vraie_fonctionEconomique = Equation(" w = 3x + 2y"); // fontion economique
	contrainteCanonique =  { Inequation("2x + y <= 6"), Inequation("x - y <= 1"), Inequation("x + y <= 4")	};	// initialise les contraintes
	
	vraie_fonctionEconomique = Equation(" w =  -x + y + 2z "); // fontion economique
	contrainteCanonique =  { Inequation("x + 2y -z <= 20"), Inequation("-2x + 4y + 2z <= 60"), Inequation("2x + 3y + z <= 50")	};	// initialise les contraintes
	
	, {'z', 0}
*/	
	
	// les inconnues
	VHB = { {'x', 0}, {'y', 0} };
	
	
	//logique initialization ( a ne pas enlever
	result = VHB;	// premiere solution admissible
	
	if( operation == MIN ) {
		vector<Terme> right = vraie_fonctionEconomique.right();
		vector<Terme> left = vraie_fonctionEconomique.left();
		string seperator ;
		
		fonctionEconomique = Equation( left, ( right*(float)(-1) ) ) ;
		for( i=0; i<contrainteCanonique.size(); i++ ) {
			right = contrainteCanonique[i].right();
			left = contrainteCanonique[i].left();
			seperator = contrainteCanonique[i].seperator();
			seperator[0] = seperator[0]=='>' ? '<' : '>';
			contrainteCanonique[i] = Inequation( left*(float)(-1), right*(float)(-1), seperator ) ;
			cout<<endl<<contrainteCanonique[i].toString()<<endl;
		}
		operation = MAX;
	} 
	else {
		fonctionEconomique = vraie_fonctionEconomique;
	}
	
	// recupere le coefficient des varaibles hors base VHB, et on le stock dans VHBCoff
	for( auto it = VHB.begin(); it!= VHB.end(); ++it ) {
		VHBCoff[ (*it).first] = (*fonctionEconomique.findTerme( (*it).first, 'R')).coff();
	}
	

	// test pour MAXIMIZATION 
	
/*

	// initialization, ici qu'on va interfacer le Qt avec le programme 
	operation = MAX;	// opretation MAX ou MIN
	fonctionEconomique = Equation(" w = 3x + 2y"); // fontion economique
	contrainteCanonique =  { Inequation("2x + y <= 6"), Inequation("x - y <= 1"), Inequation("x + y <= 3")	};	// initialise les contraintes
	
	VHB = { {'x', 0}, {'y', 0} };	// initialise les inconuues comme variable hors base avec valeur 0
	result = VHB;	// premiere solution admissible
	
	// recupere le coefficient des varaibles hors base VHB, et on le stock dans VHBCoff
	for( auto it = VHB.begin(); it!= VHB.end(); ++it ) {
		VHBCoff[ (*it).first] = (*fonctionEconomique.findTerme( (*it).first, 'R')).coff();
	}
	

*/


}


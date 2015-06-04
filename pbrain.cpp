#include <fstream> 

#include "pbrain.hpp"


using namespace std;

ifstream in;
ofstream out;

string source;

void check_input(int argc);
void load_source(char* filename);
void eternal_performing();

int main(int argc, char* argv[])
{	
	setlocale(LC_ALL, "");
	
	
	check_input(argc);
	load_source(argv[1]);
	pbrain bf_1;
	bf_1.go(source);
	eternal_performing();
	
	return 0;
}

void check_input(int argc) {
	if (argc <= 1) {
    	cout << "no arguments." << "\n";
    	eternal_performing();
	}
    
}

void load_source(char* filename) {

string line;

in.open(filename);

while (getline(in,line)) {   
	source += line;
}
	
in.close();
}

void eternal_performing() {
	pbrain bf_1;
	while(1) {
		cout << "\n";
		cin >> source;
		if (source != "reset"){
			bf_1.go(source);
		}
		else {
			bf_1.reset();
		}

	}
}


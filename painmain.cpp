#include "painpain.h"
#include <locale.h>


int main(int argc, char* argv[]) {


if (argc <= 1) {
	cout << "Not enough arguments";
    getch();
    return 0;
}
 
painpain pp_interpreter;
       
string arg1(argv[1]);
       
setlocale(LC_ALL, "");

string line;

in.open(arg1.c_str());

while ( getline(in,line)) {   
	pp_interpreter.source.push_back(line);
}

in.close();
 
pp_interpreter.current_line = 0;

while ( pp_interpreter.source[pp_interpreter.current_line] != "endmod"){
	pp_interpreter.analyse (pp_interpreter.source[pp_interpreter.current_line]);
	++pp_interpreter.current_line;
}

_getch();

return 0;
}


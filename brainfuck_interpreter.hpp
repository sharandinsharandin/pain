#include <iostream>
#include <stack>
#include <string.h>


class brainfuck_interpreter
{
public:

int go(std::string source){
	loaded_source = source;
	current_cell = 0;
	current_character = 0;
	execute();
	
	return 1;
}

void reset();
    
private:
	
	void pass_condition();
	void execute();
	

	char cells[30000];

	

	unsigned int current_cell = 0;
	unsigned int current_character = 0;

	std::stack<int> loop_adresses;
	
	std::string loaded_source;

};


void brainfuck_interpreter::pass_condition() {
while (loaded_source[current_character] != ']'){
++current_character;
}
}

void brainfuck_interpreter::execute () {
	while (current_character < loaded_source.length())
	{	
		switch(loaded_source[current_character]) 
		{
		case '>': current_cell == 29999 ? current_cell = 0 : ++current_cell;break;
		case '<': current_cell == 0 ? current_cell = 29999 : --current_cell;break;
		case '+': ++cells[current_cell]; break;
		case '-': --cells[current_cell]; break;
		case '.': std::cout << cells[current_cell];break;
		case ',': std::cin >> cells[current_cell];break;
		case '[': cells[current_cell] == 0 ? pass_condition() : loop_adresses.push(current_character);break;
		case ']': cells[current_cell] == 0 ? 1  : current_character = loop_adresses.top() - 1; loop_adresses.pop();break;
		//default :  cout << "unknown operator at cell number " << current_character; 
		}
		
		++current_character;
		
	}
}

void brainfuck_interpreter::reset() {
	memset(cells, 0, sizeof(char));
}

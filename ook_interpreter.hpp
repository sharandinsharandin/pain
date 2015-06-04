#include <iostream>
#include <stack>
#include <string.h>

class ook_interpreter
{
public:

int go(std::string source){
	loaded_source = source;
	translate();
	current_cell = 0;
	current_character = 0;
	execute();
	
	return 1;
}

void reset();
    
private:
	
	
	void translate();
	void pass_condition();
	void execute();
	

	char cells[30000];

	

	unsigned int current_cell = 0;
	unsigned int current_character = 0;

	std::stack<int> loop_adresses;
	
	std::string loaded_source;
	std::string translated_source;
};


void ook_interpreter::pass_condition() {
while (loaded_source[current_character] != ']'){
++current_character;
}
}

void ook_interpreter::translate(){
	const std::string ook_commands[] = {"Ook.Ook.", "Ook!Ook!", "Ook.Ook?", "Ook?Ook.", "Ook!Ook?", "Ook?Ook!", "Ook!Ook.", "Ook.Ook!"}; 
	const std::string bf_commands[] = {"+", "-", ">", "<", "[", "]", ".", ","} ;
	
	std::string buffer_string;
	
	
	
	while (current_character < loaded_source.length()){
		if ((loaded_source[current_character] != ' ') && (buffer_string.length() != 8)){
			buffer_string += loaded_source[current_character];
		}
		else {
			for (int i = 0; i < 8; ++i){
				if (ook_commands[i] ==  buffer_string){
					translated_source += bf_commands[i]; 
					buffer_string = "";
				}
			}
		}
	++current_character;
	}
	current_character = 0;
	
}

void ook_interpreter::execute () {
	while (current_character < translated_source.length())
	{	
		switch(translated_source[current_character]) 
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
current_character = 0;
}

void ook_interpreter::reset() {
	memset(cells, 0, sizeof(char));
}

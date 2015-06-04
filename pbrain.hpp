#include <iostream>
#include <stack>
#include <string.h>
#include <vector>


class pbrain
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
	void declare_procedure();
	void call_procedure(int index);

	char cells[30000];

	std::vector<int> proc_addr;
	std::stack<int> ret_addr;

	unsigned int current_cell = 0;
	unsigned int current_character = 0;

	std::stack<int> loop_adresses;
	
	std::string loaded_source;

};


void pbrain::declare_procedure(){
proc_addr.push_back(current_character);

while (loaded_source[current_character] != ')'){
++current_character;
}

}

void pbrain::call_procedure(int index){
	ret_addr.push(current_character);
	current_character = proc_addr[index];
	
}

void pbrain::pass_condition() {
while (loaded_source[current_character] != ']'){
++current_character;
}
}

void pbrain::execute () {
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
		case '(': declare_procedure(); break;
		case ')': current_character = ret_addr.top(); ret_addr.pop(); break;
		case ':': call_procedure(cells[current_cell]); break;
		//default :  cout << "unknown operator at cell number " << current_character; 
		}
		
		++current_character;
		
	}
}

void pbrain::reset() {
	memset(cells, 0, sizeof(char));
}

#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream> 
#include <sstream>
#include <stack>

using std::vector;
using std::stack;
using std::string;
using std::cout;
using std::cin;
using std::stringstream;
using std::ios;

std::ifstream in;
std::ofstream out;

class painpain
{
public:
	
	
	vector<string> source;
	int current_line = 0;
	stack<int> ret_line;

	int cond_flag = 0;
	


	
	string convert_to_rpn(string line);
	void calculate_expression(string expression);
	string prepare_expression(string line);
	void declare_var(string name, string value);
	void to_assign(string var_name);
	void fun_return();
	void analyse(string line);
	void console_out (string var_name);
	void console_in (string var_name);
	void console_sout (string str);
	void console_fout(string str, string path);
	void str_add(string arg_1, string arg_2);
	void declare_lab(string name, int line );
	void call_lab(string name);
	void import(int start_line );
	void go_goto(string name);
	void process_condition(int op_code, string arg_1, string arg_2, unsigned short int key);

private:
	vector<string> var_name;
	vector<string> var_value;
	


	vector<string> local_var_name;
	vector<string> local_var_value;
	vector<string> import_vector;

	string buffer;
	string lexem_0;


	
	vector<string> lab_name;
	vector<int> lab_addr;

	
	static const string operatorz[17];
	int op_size = 17;

};

const string painpain::operatorz[] = {"=", "set", "out", "sout", "nout", "fout", "in", "add", "lab", "call", "import", "==", ">", ">=", "<", "<=", "goto"};

void painpain::analyse(string line) {

vector<string> lexems;
string temporary_lexem;

if (line.length() == 0)
{
return;
}

for (int i = 0; i < line.length(); i++){

 if (line[i] !=  ' '){ //&& (temporary_lexem != "")
    if (line[i] ==  '\''){
    	++i;
    	
    	while (line[i]!='\''){   
    		temporary_lexem += line[i];
		    ++i;
		}
	++i;
	lexems.push_back(temporary_lexem);
	temporary_lexem = "";
	}
	
	else {
	
	temporary_lexem += line[i];

 	}
 } else {   
    
	 lexems.push_back(temporary_lexem);
	 temporary_lexem = "";
   }
}

lexems.push_back(temporary_lexem);


//for (int i = 0; i < lexems.size(); i++ ){
 for (int j = 0; j < op_size ; j++) {
	if(operatorz[j] == lexems[0])
	{
		switch (j){
			case 0:
			to_assign(lexems[1]);
			return;
			case 1:
			declare_var(lexems[1], lexems[2]);
			return;
			case 2:
			console_out (lexems[1]);
			return;
			case 3:
			console_sout (lexems[1]);
			return;
			case 4:
			cout << "\n";
			return;
			case 5:
			console_fout(lexems[1], lexems[2]);
			return;
			case 6:
			console_in (lexems[1]);
			return;
			case 7:
			str_add (lexems[1], lexems[2]);
			return;
			case 8:
			declare_lab (lexems[1], current_line);
			return;
			case 9:
			call_lab (lexems[1]);
			return;
			case 10:
			import (current_line);
			return;
			case 11:
			process_condition(0, lexems[1], lexems[2], 0);
			return;
			case 12:
			process_condition(1, lexems[1], lexems[2], 0);
			return;
			case 13:
			process_condition(2, lexems[1], lexems[2], 0);
			return;
			case 14:
			process_condition(3, lexems[1], lexems[2], 0);
			return;
			case 15:
			process_condition(4, lexems[1], lexems[2], 0);
			return;
			case 16:
			go_goto (lexems[1]);
			return;
		
		}
	}
}
//}
lexem_0 = lexems[0];
calculate_expression(line);
}



string painpain::prepare_expression(string line){

for (int i = 0; i < var_name.size(); i++) {
	while(line.find(var_name[i])!=std::string::npos){
		line.replace(line.find(var_name[i]), var_name[i].length(), var_value[i]);
	}
} 


for (int i = 0; i < line.length(); i++){
	if (i) {
		if (line[i] == '-' && line[i-1] == '('){
		line.insert(i, "0");
		}
	} else {
		if (line[i] == '-'){
		line.insert(i, "0");
		}
		
	  }	
}
	
return line;
}
	
string painpain::convert_to_rpn(string line) {
	
	line = prepare_expression(line);
	
	string output = "";
	
	stack <char> operands;
	
	for (int i = 0; i < line.length(); i++){
		
		if ((line[i] == '+') || (line[i] == '-')) {
		
		if (operands.empty() || (operands.top() == '(') ) {
		    operands.push(line[i]);
            continue;
	    
		}
		else {
			output.push_back(operands.top());
	        output.push_back(' ');
			operands.pop();
			i -= 1;
			continue;
		}
		}
	if ((line[i] == '*') || (line[i] == '/')) {
			if (operands.empty() || (operands.top() != '/' || (operands.top() != '*'))) {
		            operands.push(line[i]);
		            continue;
	    	} 
			else {
		    output.push_back(operands.top());
	        output.push_back(' ');
			operands.pop();
			i -= 1;
			continue;
			}
	}
	
	if (line[i] == '(') {
		            operands.push(line[i]);
	                continue;
	}
	    
	if (line[i] == ')') {
	    while(operands.top() != '('){
		
			output.push_back(operands.top());
	    	output.push_back(' ');
			operands.pop();
	}
		operands.pop();
		continue;
	}
	    
	else {
		output.push_back(line[i]);
	    while((((int)line[i+1] >=48 && (int)line[i+1] <= 57) || (int)line[i+1] == 46 )){
		++i;
		output.push_back(line[i]);
	}
	    	
	    output.push_back(' ');
	}
	    
}

while(!operands.empty()){
	output.push_back(operands.top());
	output.push_back(' ');
	operands.pop();
}

return output;
}

void painpain::calculate_expression(string expression) {
	expression = convert_to_rpn(expression);
	double arg1;
	double arg2;
	
	stack <double> symb;
	
	
	
	for (int i = 0; i < expression.length(); i++){
	
	
	if (expression[i]==' '){
	continue;
	}
	
	if (expression[i] == '+'){
	 arg1 = symb.top();
	 symb.pop();
	 arg2 = symb.top();
	 symb.pop();
	 
	 
	 
	 arg1 += arg2;
	 symb.push(arg1);
	 
	 
	 continue; 	
	}
	
	if (expression[i] == '-'){
	 arg2 = symb.top();
	 symb.pop();
	 arg1 = symb.top();
	 symb.pop();
	 
	 arg1 -= arg2;
	 symb.push(arg1);
	 continue;	
	}
	
	if (expression[i] == '*'){
	
	 arg1 = symb.top();
	 symb.pop();
	 arg2 = symb.top();
	 symb.pop();
	 
	 arg1 *= arg2;
	 symb.push(arg1);
	 continue;	
	}
	
	if (expression[i] == '/'){
	 arg1 = symb.top();
	 symb.pop();
	 arg2 = symb.top();
	 symb.pop();
	 
	 arg1 /= arg2;
	 symb.push(arg1);
	 continue;	
	}
	
	
	else {
		
		string temp_output;
		
		temp_output.push_back(expression[i]);
	    	while(((int)expression[i+1] >=48 && (int)expression[i+1] <= 57 ) || (int)expression[i+1] == 46){
			++i;
			temp_output.push_back(expression[i]);
	
		}
		
		stringstream stream;
		stream << temp_output;
		double dVal;
		stream >> dVal;
		
	    symb.push(dVal);
		
	    
	    continue;
	}
	
	}
	stringstream stream;
    stream << symb.top();
	stream >> buffer;
}

void painpain::declare_var(string name, string value) {
	var_name.push_back(name);
	var_value.push_back(value);
}

void painpain::declare_lab(string name, int line ) {
    lab_name.push_back(name);
	lab_addr.push_back(line+1);
	
	while (source[current_line] != "endlab") {   
		    ++current_line;
	}
		
}

void painpain::import(int start_line ) {
    
++current_line;
	
while (source[current_line] != "/import") {   
	import_vector.push_back(source[current_line]);
          
	++current_line;	    
}

source.erase(source.begin()+current_line);		

for (int i=start_line; i < start_line +  import_vector.size(); ++i) {  
	source.erase(source.begin()+i);
}

source.erase(source.begin()+start_line);

string line;

for (int i=0; i < import_vector.size(); i++)
{

	in.open(import_vector[i].c_str());

	int pos = start_line;

	while ( getline(in,line)) {   
		if (line != "endmod") {
			 source.insert(source.begin()+pos, line);
         	++pos;
    	}
	}

 	in.close();
	
}

current_line = start_line - 1; 

}



void painpain::to_assign(string name) { 
	for (int i = 0; i < var_name.size(); i++ ) {
		if(name == var_name[i]) {
	  		var_value[i] = buffer;
	  
	    }
    }
    
}

void painpain::call_lab(string name) {   

	for (int i = 0; i < lab_name.size(); i++ ) {
	  if(name == lab_name[i]) {
	  	ret_line.push(current_line);
	  	current_line = lab_addr[i];
        break;	  
	  }
    }
    
    	
    while (source[current_line] != "endlab" ) {
    		
    		if (source[current_line] == "return") {
			fun_return();
			return;
			}
			
		    analyse(source[current_line]);
		    ++current_line;
	}
	 
	
	//while (!ret_line.empty()) {
	current_line = ret_line.top();
			ret_line.pop();
	//}
	
	
 
}

void painpain::go_goto(string name) {
	cout << source[current_line];
	for (int i = 0; i < lab_name.size(); ++i ) {
	  if(name == lab_name[i]) {
	  	current_line = lab_addr[i];
        ++current_line;
		break;	  
	  }
    }
    
}

void painpain::console_out (string name) {   
    if (name == "buffer") {
    	cout << buffer;
	}
	if (name == "lexem_0") {
    	cout << lexem_0;
	}
	for (int i = 0; i < var_name.size(); i++ ) {
	  if(name == var_name[i]) {
	  	cout << var_value[i];
	  }
    }

}

void painpain::console_in (string name) {   
    if (name == "buffer") {
    	cin >> buffer;
	}
	for (int i = 0; i < var_name.size(); i++ ) {
	  if(name == var_name[i]) {
	  	cin >> var_value[i];
	  }
    }
}

void painpain::console_sout (string str) {
	cout << str;
}

void painpain::console_fout(string str, string path) {   
	out.open(path.c_str(), ios::out);
	out << str;
	out.close();
}

void painpain::str_add(string arg_1, string arg_2) {
	 for (int j = 0; j < var_name.size(); j++) {
	 
	  if(arg_1 == var_name[j]) {
	  	arg_1 = var_value[j];
	  }
	  if(arg_2 == var_name[j]) {
	  	arg_2 = var_value[j];
	  }
	 }
	arg_1 += arg_2;
	buffer = arg_1;
}

void painpain::process_condition(int op_code, string arg_1, string arg_2, unsigned short int key) {


 	int start_line = current_line;
 	
	cond_flag = 0;
	
	double d_arg_1;
	double d_arg_2;
	
	int declared_1 = 0;
	int declared_2 = 0;

	
	for (int j = 0; j < var_name.size(); j++) {
	 
	  if(arg_1 == var_name[j])
	  {
	  	
       stringstream stream;	  	
		stream << var_value[j];
		stream >> d_arg_1;
		declared_1 = 1;
		break;
	  }
}
for (int j = 0; j < var_name.size(); j++) {
	
	  if(arg_2 == var_name[j])
	  {
	  	stringstream stream;
		stream << var_value[j];
		stream >> d_arg_2;
		declared_2 = 1;
		break;
		}
	 }
	 
	 if(declared_1 == 0)
	  {
	  	stringstream stream;
		stream << arg_1;
		stream >> d_arg_1;
	
		}
		
		 if(declared_2 == 0)
	  {
	  	stringstream stream;
		stream << arg_2;
		stream >> d_arg_2;
	
		}
	 
	

	switch (op_code){
		case 0:
			d_arg_1 == d_arg_2 ? cond_flag = 1 : 1;
			break;
			case 1:
			d_arg_1 > d_arg_2 ? cond_flag = 1 : 1;
			break;
			case 2:
			d_arg_1 >= d_arg_2 ? cond_flag = 1 : 1;
			break;
			case 3:
			d_arg_1 < d_arg_2 ? cond_flag = 1 : 1;
			break;
			case 4:
			d_arg_1 <= d_arg_2 ? cond_flag = 1 : 1;
			break;
			
	}
	
	++current_line;
	
	if (cond_flag == 0) {
		while (source[current_line] != "endcond"){
			++current_line;
		}
	
	}
	else {
		while (source[current_line] != "endcond"){
			analyse(source[current_line]);
			++current_line;
		}
	
		if(key == 1) {
			analyse(source[start_line]);
		}
	}
}


/* void ifor(string arg_1, string arg_2, string step, int* i) {
	int iarg_1 = atoi(arg_1.c_str());
	int iarg_2 = atoi(arg_2.c_str());
	int istep = atoi(step.c_str());
	
	if (iarg_2 > iarg_1)
	{
		iarg_1 ^= iarg_2;
		iarg_2 ^= iarg_1;
		iarg_1 ^= iarg_2;
	}
	
	for (iarg_1; iarg_1 <= iarg_2; iarg_1 += istep )
	{
	 while (source[current_line] != "endfor")
    	{   
    		analyse(source[current_line]);
		    ++i;
		}
	++i;
	}
	}
*/

void painpain::fun_return() {
	
	while (!ret_line.empty()) {
	current_line = ret_line.top();
	ret_line.pop();
	}
}

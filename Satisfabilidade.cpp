#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "util.h"

using namespace std;

bool parse(char* filename,vector<vector<int>>& clause_contents,
			map<int,int>& variable_values, int& num_vars, int& num_clauses);

int one_clause_bool(vector<vector<int>>& clause_content,
					map<int,int>& variable_values, int clause_index);

int all_clause_bool(vector<vector<int>>& clause_content,
					map<int,int>& variable_values);

void output_variables(map<int,int>& variable_values, ofstream& ofile);

bool search(int index,vector<vector<int>>& clause_contents,
		map<int,int>& variable_values, int& num_vars);

int main(int argc, char* argv[]){
	if(argc < 3){
		cerr << "Usage ./sat_solver input_file output_file" << endl;
	}
	vector<vector<int>> clause_contents;
	map<int, int> variable_values;
	int num_vars = 0;
	int num_clauses = 0;

	// Parse the file
	// 0 = false
	// 1 = true
	// -1 = unassigned
	if(parse(argv[1], clause_contents, variable_values,
			 num_vars, num_clauses) == false){
		cerr << "Unable to open input file" << endl;
		return 1;
	}

	// Open the output file
	ofstream ofile(argv[2]);

	//if no clauses or variables
	if(num_vars < 1 || num_clauses < 1){
		ofile << "No solution";
		cerr << "Input file requires atleast " 
			 << "one variable or one clause" << endl;
		return 1;
	}

	//recursive function to find a solution
	bool temp = search(1, clause_contents, variable_values, num_vars);
	if(temp == true){
		output_variables(variable_values,ofile);
	}
	else{
		ofile << " No solution";
	}
	

	ofile.close();

	return 0;
}

// function to parse
bool parse(char* filename,vector<vector<int>>& clause_contents,
			map<int,int>& variable_values, int& num_vars, int& num_clauses){
	//read in input file
	ifstream ifile(filename);
	if(ifile.fail()){
		return false;
	}
	//make variable values
	string whole_line;
	while(getline(ifile,whole_line)){
		whole_line = trim(whole_line);
		if(whole_line[0] == 'p'){
			break;
		}
	}
	stringstream ss(whole_line);
	string misc;
	for(int i = 0; i < 2; i++){
		ss >> misc;
	}
	//read in num of variables and clauses
	ss >> num_vars;
	ss >> num_clauses;
	int unassigned = -1;
	for(int i = 1; i <= num_vars; i++){
		variable_values.insert({ i, unassigned});
	}
	//make clauses
	for(int i = 0; i < num_clauses; i++){
		getline(ifile,whole_line);
		whole_line = trim(whole_line);
		if(whole_line.empty() == false){
			stringstream ss(whole_line);
			int num;
			vector<int> temp;
			while(ss >> num){
				//if delimiiter is read in
				if(num == 0){
					break;
				}
				temp.push_back(num);
			}
			clause_contents.push_back(temp);
		}
	}
	return true;
}

//function that checks if a single clause is true
//return 1 if true
//return 0 if all variables are false
//return -1 if some variables are false and others are unassigned
int one_clause_bool(vector<vector<int>>& clause_content,
					map<int,int>& variable_values, int clause_index){
	//create a vector of the values of the clause
	int vector_size = clause_content[clause_index].size();
	vector<int> clause_values;
	for(int i = 0; i < vector_size; i++){
		bool invert = false;
		int temp_var_index = clause_content[clause_index][i];
		if(temp_var_index < 0){
			invert = true;
		}
		temp_var_index = abs(temp_var_index);
		map<int,int>::iterator it = variable_values.find(temp_var_index);
		int temp_var_val = it -> second;
		if(invert == true){
			if(temp_var_val == 0){
				clause_values.push_back(1);
			}
			else if(temp_var_val == 1){
				clause_values.push_back(0);
			}
			else{
				clause_values.push_back(-1);
			}
		}
		else{
			clause_values.push_back(temp_var_val);
		}
	}

	//iterate through vector to see its truth value
	int num_variables = clause_values.size();
	int current_clause_state = 0;
	int num_false = 0;
	for(int i = 0; i < num_variables; i++){
		if(clause_values[i] == 1){
			current_clause_state = 1;
			return current_clause_state;
		}
		else if(clause_values[i] == 0){
			num_false++;
		}
	}
	if(num_false != num_variables){
		current_clause_state = -1;
	}
	return current_clause_state;
}

//function to check if all the clauses are true or not
//return 1 if true
//return 0 if all clauses are false
//return -1 if some clauses are false and others are unassigned
int all_clause_bool(vector<vector<int>>& clause_content,
					map<int,int>& variable_values){
	int clause_count = clause_content.size();
	vector<int> all_clause;
	for(int i = 0; i < clause_count; i++){
		int clause_bool = one_clause_bool(clause_content,
									 variable_values, i);
		all_clause.push_back(clause_bool);
	}
	int all_clause_status = 0;
	int num_true = 0;
	for(unsigned int i = 0; i < all_clause.size(); i++){
		if(all_clause[i] == 0){
			all_clause_status = 0;
			return all_clause_status;
		}
		else if(all_clause[i] == 1){
			num_true++;
		}
	}
	if(num_true != clause_count){
		all_clause_status = -1;
		return all_clause_status;
	}
	else{
		all_clause_status = 1;
		return all_clause_status;
	}
}

//function to output variable values to a file
//doesn't out a variable if its value is unassigned
void output_variables(map<int,int>& variable_values, ofstream& ofile){
	map<int,int>::iterator it;
	for(it = variable_values.begin(); it != variable_values.end(); ++it){
		int temp_idx = it -> first; 
		int temp_val = it -> second;
		if(temp_val != -1){
			ofile << temp_idx << " = " << temp_val << endl;
		}
	}
}

//recursive function to find a solution
bool search(int index,vector<vector<int>>& clause_contents,
		map<int,int>& variable_values, int& num_vars){
	//check the truth value of all the clauses
	int temp = all_clause_bool(clause_contents,variable_values);
	if(temp == 1){
		return true;
	}
	//if there is def no answer
	else if(temp == 0){
		return false;
	}
	//if a solution is still possible
	else if(temp == -1){
		//make sure it doesn't go beyond the num of variables
		if(index <= num_vars){
			
			//search all solutions where the current variable is 
			//set to 0
			variable_values[index] = 0;
			bool search_status = search(index + 1, clause_contents, 
										variable_values, num_vars);
			if(search_status == true){
				return true;
			}
			//search all solutions where the current variable is 
			//set to 1
			variable_values[index] = 1;
			search_status = search(index + 1, clause_contents, 
										variable_values, num_vars);
			if(search_status == true){
				return true;
			}
			//when backtracking you need to unassign the current
			//variable and go back
			variable_values[index] = -1;
		}
	}
	return false;
}
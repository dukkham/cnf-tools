#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <random>
#include <map>

const int BUFFSIZE = 50000;




std::uniform_int_distribution<int> bin_dist(0, 1);
std::random_device rd1; // uses RDRND or /dev/urandom

bool hasPrefix_String(std::string str, std::string prefix, std::string &value )
{
	int found = str.find( prefix );
	if ( found != -1 ) {
		value = str.substr( found + prefix.length( ) );
		return true;
	}
	return false;
}

const int VARMODE = 1;


void checkFunctionValue (std::vector<std::string> input_string) {

	std::map<int,int> var_map;
	std::map<int,int>::iterator it_map;

	for (int i = 0; i < input_string.size(); i++) {
		std::string s = input_string[i];
		std::cout << s << " ";
		if (s[0] == 'x') {
			// std::cout << s << " ";
			int val = 0;
            try {
                s = s.substr(1);
                val = std::stoi(s);
            }
            catch (std::invalid_argument const &e) {
                std::cout << "bad input" << '\n';
            }
                // st.insert(std::make_pair(val,0));
                var_map.insert(std::make_pair(val,0));
                // std::cout << val << " ";
		}
	}
	printf("\n");

	printf("var vec: ");
    for(it_map = var_map.begin(); it_map != var_map.end(); it_map++) {
    	// it_map->second++;	
    	it_map->second = bin_dist(rd1);
    	printf("%d(%d) ",it_map->first, it_map->second);	
    }

	printf("\n");

	std::vector<int> val_st;

// read ls equation from '='
	for (int i = 2; i < input_string.size(); i++) {
		std::string s = input_string[i];
		// std::cout << s << " ";
		if (s[0] == 'x') { //if variable -- push it's value to stack
			std::cout << s << " ";
			int val = 0;
			int var_id = 0;
            try {
                s = s.substr(1);
                var_id = std::stoi(s);
            }
            catch (std::invalid_argument const &e) {
                std::cout << "bad input" << '\n';
            }

			// val = bin_dist(rd1); 

			it_map = var_map.find(var_id);
			if (it_map != var_map.end()) {
				val = it_map->second;
			}			

            val_st.push_back(val); // val-id -> get value
            printf("c:%d\n", val);
		}
		else {
			int v1;
			int v2;
			switch (s[0]) {
                case '^' : 
                	v1 = val_st[val_st.size()-1];
                	val_st.pop_back();   
                	v2 = val_st[val_st.size()-1];
                	val_st.pop_back(); 
                	val_st.push_back(v1 ^ v2);
                	printf("f:%d ^ %d = %d\n", v1, v2, v1^v2);
                         break;
                    case '&' : 
                	v1 = val_st[val_st.size()-1];
                	val_st.pop_back();   
                	v2 = val_st[val_st.size()-1];
                	val_st.pop_back(); 
                	val_st.push_back(v1 & v2);
                	printf("f:%d & %d = %d\n", v1, v2, v1&v2);
                         break;
                    case '|' : 
                	v1 = val_st[val_st.size()-1];
                	val_st.pop_back();   
                	v2 = val_st[val_st.size()-1];
                	val_st.pop_back(); 
                	val_st.push_back(v1 | v2);
                	printf("f:%d | %d = %d\n", v1, v2, v1|v2);
                         break;     

            }
		}
		
	}

	// printf("stack size() = %d\n", val_st.size());
	int f = val_st[0];
	printf("stack value = %d\n", f);

	int l = 0;
	it_map = var_map.end();
	it_map--;
	l = it_map->second;
	printf("last var_map value = %d\n", l);

	// check f value:
	if (f == l)
		printf("match\n");

}

std::set<int> readVarMap() {

	std::stringstream bit_stream;
	char buff[ BUFFSIZE ]; // a buffer to temporarily park the data

	std::set<int> return_message;

	std::ifstream infile("var_map");
	if(!infile)
		return return_message;

  	for (int i = 0; i < 2; i++)
  	{
  		infile.getline(buff, BUFFSIZE);
  		if (i != 0) {
	  		bit_stream << buff;

	  		while( bit_stream.getline(buff, 10, ' ') ) {
	  			// std::cout << buff << " ";
  				std::string message = buff;
	  			int val = 0;
				try {
					val = std::stoi(message);
					// std::cout << val << " ";
				}
				catch (std::invalid_argument const &e) {
					std::cout << "bad input" << '\n';
				}
				if (val != 0) {
					return_message.insert(std::abs(val));
				}
			}
			
			bit_stream << "";
			bit_stream.clear();
		}
	}
	// std::cout << std::endl; 
	infile.close();
	std::cout << return_message.size() << std::endl;
	return return_message;
}




std::vector <std::vector< std::string > > readStringStream( char* arg) {

	std::stringstream bit_stream;
	char buff[ BUFFSIZE ]; // a buffer to temporarily park the data

  	// ifstream infile("input.txt");
  	std::cout << "open file " << arg << std::endl;
	std::vector <std::vector< std::string > > return_message;

	std::ifstream infile(arg);
	if(!infile)
		return return_message;

  	while ( infile.getline(buff, BUFFSIZE) )
  	{
  		std::vector< std::string > message;
  		// size_t pos = buff.find_first_of(" ");
  		// cout << "[" << buff << "]";
  		// int mode = 0;
  		bit_stream << buff;

		while( bit_stream.getline(buff, 10, ' ') ) {
			message.push_back(buff);
		}
		bit_stream << "";
		bit_stream.clear();
		// }
		return_message.push_back(message);
	}
	infile.close();
	std::cout << return_message.size() << std::endl;
	return return_message;
}


std::vector <std::vector< std::string > > readStringStreamToVector( char* arg, int mode = VARMODE) {

	std::stringstream bit_stream;
	char buff[ BUFFSIZE ]; // a buffer to temporarily park the data

  	// ifstream infile("input.txt");
  	std::cout << "open file " << arg << std::endl;
	std::vector <std::vector< std::string > > return_message;

	std::ifstream infile(arg);
	if(!infile)
		return return_message;

  	while ( infile.getline(buff, BUFFSIZE) )
  	{
  		std::vector< std::string > message;
  		// size_t pos = buff.find_first_of(" ");
  		// cout << "[" << buff << "]";
  		// int mode = 0;
  		bit_stream << buff;
  		//c var_set

  		// bit_stream.get(buff, 4); // first 4 bits
  		// bit_stream.getline(buff, 10, ' '); //first 10 bits before delimetr

  		// bit_stream << "";
		// bit_stream.clear();
		// std::cout << "buff[0] " << buff[0] << std::endl;

		std::stringstream str_stream;
		bit_stream.get(buff, 11);
		str_stream << buff;
		// std::cout << "buff " << str_stream.str() << "." << std::endl; 

		std::string prefix = "c var_set ";
  		if (str_stream.str() == prefix) {
  		
			while( bit_stream.getline(buff, 10, ' ') ) {
				message.push_back(buff);
			}
			bit_stream << "";
			bit_stream.clear();
			// }
			return_message.push_back(message);
		}
		else  {
			// std::cout << "scip line" << std::endl;	
			bit_stream.getline(buff, BUFFSIZE); // scip all line started from !c
			bit_stream << "";
			bit_stream.clear();
		}
	}
	infile.close();
	std::cout << return_message.size() << std::endl;
	return return_message;
}

int main( int argc, char** argv ) {
	// if (argv > 1)

	// map find:
	// std::set<int> example = {1, 2, 3, 4};
 	// auto search = example.find(2);
 	// if (search != example.end()) {

	int program_mode = VARMODE;	
	std::vector <std::vector< std::string > > multiple_input_string;
	std::vector <std::vector< std::string > > multiple_output_string;
	std::vector<std::vector<int> > var_index_vec; 
	multiple_input_string = readStringStream(argv[argc - 1]);
	checkFunctionValue(multiple_input_string[0]);

// 	// std::set<std::pair<int,int> > st;
// 	// std::set<std::pair<int,int> >::iterator it_st;
// 	std::map<int,int> var_map;
// 	std::map<int,int>::iterator it_map;

// 	for (int i = 0; i < multiple_input_string[0].size(); i++) {
// 		std::string s = multiple_input_string[0][i];
// 		std::cout << s << " ";
// 		if (s[0] == 'x') {
// 			// std::cout << s << " ";
// 			int val = 0;
//             try {
//                 s = s.substr(1);
//                 val = std::stoi(s);
//             }
//             catch (std::invalid_argument const &e) {
//                 std::cout << "bad input" << '\n';
//             }
//                 // st.insert(std::make_pair(val,0));
//                 var_map.insert(std::make_pair(val,0));
//                 // std::cout << val << " ";
// 		}
// 	}
// 	printf("\n");


//     // for(it_st = st.begin(); it_st!= st.end(); it_st++) {
//     //     // vec.push_back(*it_st);
//     //     std::cout << it_st->first << " ";
//     //     // it_st->second = 0; // check ++ operation
//     // }

// 	printf("var vec: ");
//     for(it_map = var_map.begin(); it_map != var_map.end(); it_map++) {
//     	// it_map->second++;	
//     	it_map->second = bin_dist(rd1);
//     	printf("%d(%d) ",it_map->first, it_map->second);	
//     }

// 	printf("\n");

// 	std::vector<int> val_st;

// // read ls equation from '='
// 	for (int i = 2; i < multiple_input_string[0].size(); i++) {
// 		std::string s = multiple_input_string[0][i];
// 		// std::cout << s << " ";
// 		if (s[0] == 'x') { //if variable -- push it's value to stack
// 			std::cout << s << " ";
// 			int val = 0;
// 			int var_id = 0;
//             try {
//                 s = s.substr(1);
//                 var_id = std::stoi(s);
//             }
//             catch (std::invalid_argument const &e) {
//                 std::cout << "bad input" << '\n';
//             }

// 			// val = bin_dist(rd1); 

// 			it_map = var_map.find(var_id);
// 			if (it_map != var_map.end()) {
// 				val = it_map->second;
// 			}			

//             val_st.push_back(val); // val-id -> get value
//             printf("c:%d\n", val);
// 		}
// 		else {
// 			int v1;
// 			int v2;
// 			switch (s[0]) {
//                 case '^' : 
//                 	v1 = val_st[val_st.size()-1];
//                 	val_st.pop_back();   
//                 	v2 = val_st[val_st.size()-1];
//                 	val_st.pop_back(); 
//                 	val_st.push_back(v1 ^ v2);
//                 	printf("f:%d ^ %d = %d\n", v1, v2, v1^v2);
//                          break;
//                     case '&' : 
//                 	v1 = val_st[val_st.size()-1];
//                 	val_st.pop_back();   
//                 	v2 = val_st[val_st.size()-1];
//                 	val_st.pop_back(); 
//                 	val_st.push_back(v1 & v2);
//                 	printf("f:%d & %d = %d\n", v1, v2, v1&v2);
//                          break;
//                     case '|' : 
//                 	v1 = val_st[val_st.size()-1];
//                 	val_st.pop_back();   
//                 	v2 = val_st[val_st.size()-1];
//                 	val_st.pop_back(); 
//                 	val_st.push_back(v1 | v2);
//                 	printf("f:%d | %d = %d\n", v1, v2, v1|v2);
//                          break;     

//             }
// 		}
		
// 	}

// 	// printf("stack size() = %d\n", val_st.size());
// 	int f = val_st[0];
// 	printf("stack value = %d\n", f);

// 	int l = 0;
// 	it_map = var_map.end();
// 	it_map--;
// 	l = it_map->second;
// 	printf("last var_map value = %d\n", l);

// 	// check f value:
// 	if (f == l)
// 		printf("match\n");






#if 0 // reading CNF header for c var_map line
	multiple_input_string = readStringStreamToVector(argv[argc - 1], program_mode);
	if (multiple_input_string.size() !=0 )
	{
		std::cout << "multiple_input_string[0].size() = " << multiple_input_string[0].size() << std::endl;

		std::vector<int> vec;
		for (int i = 0; i < multiple_input_string[0].size(); i++) {
			std::string s = multiple_input_string[0][i];
			// std::cout << s << " ";
			int val = 0;
			try {
				val = std::stoi(s);
				std::cout << val << " ";
			}
			catch (std::invalid_argument const &e) {
				std::cout << "bad input" << '\n';
			}
			vec.push_back(val);
			if (vec.size() == 32) {
				// std::cout << vec
				var_index_vec.push_back(vec);
				vec.clear();
			}
		}
		std::cout << std::endl;
	}

	if (var_index_vec.size() != 0)
	for (int i = 0; i < var_index_vec.size(); i++) {
		for (int j = 0; j < var_index_vec[i].size(); j++) {
			int val = var_index_vec[i][j];
				std::cout << val << " ";
		}
		std::cout << std::endl;
	}

    std::stringstream command_prepoc;
    std::string file_name = argv[argc - 1];
    // SatELite_v1.0_linux - md5.cnf md5_preproc.cng var_map

    //TODO check SatELite_v1
    command_prepoc << "SatELite_v1.0_linux - " << file_name << " preproc.cnf var_map";
    const std::string tmp =  std::string{command_prepoc.str()};
    system(tmp.c_str());


    std::set<int> test_set = readVarMap();

	for (int i = 0; i < var_index_vec.size(); i++) {
		bool isKnown = true;
		for (int j = 0; (j < var_index_vec[i].size()&& (isKnown)); j++) {

			int val = var_index_vec[i][j];
		 	auto search = test_set.find(val);
 			if (search == test_set.end()) {
 				isKnown = false;
 			}

		}
		if (isKnown)
			std::cout << "vars " << i << " are known " << std::endl;
	}
#endif


	return 1;
}
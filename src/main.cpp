#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

const int BUFFSIZE = 5000;
// const int MIXMODE = 2;
const int VARMODE = 1;
const int BITMODE = 0;

bool hasPrefix_String(std::string str, std::string prefix, std::string &value )
{
	int found = str.find( prefix );
	if ( found != -1 ) {
		value = str.substr( found + prefix.length( ) );
		return true;
	}
	return false;
}

std::vector<std::string> convertToBits(std::vector<std::string> message )
{
	std::cout << message.size() << std::endl;
	std::vector<std::string> message_bits;

	for ( int i = 0; i < message.size(); i++ )
	{
		// int val = (atoi(char*) > 0)? 1: 0; 
		int val = ( message[i][0] == '-' )? 0: 1; //TODO:
		
		std::ostringstream convert; 
		convert << val; 
		message_bits.push_back(convert.str());
		// message_bits.push_back(to_string(val));
		std::cout << message_bits[i];
	}

	std::cout << std::endl;
	return message_bits;

}

std::vector<int> convertFromBits(std::vector<std::string> message, int start_index = 1, int file_index = 0 )
{
	// xsel -b -i
	std::vector<int> message_vars;

	// std::ofstream outfile("code.alg",std::ofstream::app);
	std::stringstream file_name;
	
	file_name << "test_" << file_index <<".c";

    std::stringstream command_string;
    command_string << "cp test.c " << file_name.str();
    const std::string tmp =  std::string{command_string.str()};
	std::system(tmp.c_str());

	std::ofstream outfile(file_name.str(),std::ofstream::app);
	if (start_index == 0) {
		outfile << "__CPROVER_bool pr_1 = ";
	}

	for ( int i = 0; i < message.size(); i++ )
	{
		int sign = ( message[i] == "0" )? -1: 1;
		int val = ( i + start_index ) * sign;
		// cout << "[" << i << "]"; //DEBUG
		message_vars.push_back(val);

		if (start_index != 0) {
		std::cout << message_vars[i] << " 0\n"; //TODO: end_of_line_formst = 
		// outfile << message_vars[i] << " 0\n"; //TODO: end_of_line_formst = 
		}
		else { // write into file(s)

			std::string st = (sign < 0)?"!":"";
			if ((i < message.size()-1)) {
				printf("%sresult[%d]&&",(sign < 0)?"!":"",i+start_index);
				outfile << st <<"result["<< i+start_index << "]&&";
			}
			else {
				printf("%sresult[%d];\n",(sign < 0)?"!":"",i+start_index);
				outfile << st <<"result["<< i+start_index << "];\n";
			}
		}	
	} //for

	std::cout << std::endl;
	outfile << "__CPROVER_assert(pr_1 == 0, \"test1\");\n}";
	outfile.close();

	std::stringstream smt_file_name;
	smt_file_name << "test_" << file_index <<".smt";

    std::stringstream cbmc_command_string;
    cbmc_command_string << "cbmc --z3 --outfile " << smt_file_name.str() << " "<< file_name.str() << "> out";
    const std::string tmp_2 =  std::string{cbmc_command_string.str()};
	std::system(tmp_2.c_str());

	return message_vars;

}

std::vector<int> convertFromBitsWithVector(std::vector<std::string> message, std::vector<int> vec)
{
	// xsel -b -i
	std::vector<int> message_vars;

	if (message.size() == vec.size()) {

		// std::ofstream outfile("code.alg");
		for ( int i = 0; i < message.size(); i++ )
		{
			int sign = ( message[i] == "0" )? -1: 1;
			int val = ( vec[i] ) * sign;
			// cout << "[" << i << "]"; //DEBUG
			message_vars.push_back(val);
			std::cout << message_vars[i] << " 0\n"; //TODO: end_of_line_formst = 
			// outfile << message_vars[i] << " 0\n"; //TODO: end_of_line_formst = 

		}
		std::cout << std::endl;
		// outfile.close();
	}
	return message_vars;

}


std::vector <std::vector< std::string > > readStringStreamToVector( char* arg, int mode = VARMODE) {

	std::stringstream bit_stream;
	char buff[ BUFFSIZE ]; // a buffer to temporarily park the data

  	// ifstream infile("input.txt");
  	std::cout << "open file " << arg << std::endl;


	//TODO: fstream.open()

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
  		if(mode) //VARMODE
  		{
			while( bit_stream.getline(buff, 10, ' ') )
			{
				// cout << buff; //DEBUG: input.txt
				// cout << endl;
				// if ( buff[0] != '0' ) //TODO only for CNF assigments "-512 0"
					message.push_back(buff);
			}
			bit_stream << "";
			bit_stream.clear();
		}
		else 
		{
			std::cout << "no delimeters" << std::endl;
			while( bit_stream.get(buff, 2) ) {
				// cout << "[" << buff << "]";
				message.push_back(buff);
			}
			bit_stream << "";
			bit_stream.clear();

			//for (int i = 0; i < buff.size(); ++i)
			int i = 0;
			// while (buff[i] != '\n');
			// {
			// 	message.push_back(buff[i]);
			// 	i++;
			// }
			// cout << buff;
			
			// for (int i = 0; i < ; ++i)
			// {
			// 	 code 
			// }
		}
		return_message.push_back(message);
	}
	infile.close();

	// for ( int i = 0; i < message.size(); i++ )
	// {
	// 	// cout << message[i] << " "; //DEBUG
	// }
	std::cout << return_message.size() << std::endl; //TODO: message
	return return_message;
}

int main( int argc, char** argv ) {
	// if (argv > 1)

	std::vector<std::string> input_string, bits;
	std::vector<int> stat_bits;
	std::vector< std::vector <int> > hex_diffs;
	std::vector<std::map<long int,int> > map_hex;

	std::vector <std::vector< std::string > > multiple_input_string;

	if ( argc < 2 ) {
	// cerr << "Using: sat_recompute input_cnf_name -max_solving_time=[max time for solving partucular subproblem]" << std::endl;
	// cerr << "Using: testname.cpp -mode -pnt[=n] input_cnf_name " << endl;
	return 0; //TODO: errno	
	}

	std::string val;
	int program_mode = VARMODE;
	if (hasPrefix_String(argv[1], "-b", val)) {
		program_mode = BITMODE;
	}
	// else if (hasPrefix_String(argv[1], "-m", val)) {
	// 	program_mode = MIXMODE;
	// }

	int counter = 1;
	int vector_size = 100;
	std::stringstream bit_stream;

	// bit_stream << setfill ('0') << setw(1); //+ std::

	multiple_input_string = readStringStreamToVector(argv[argc - 1], program_mode);
	hex_diffs.resize(27);
	map_hex.resize(27);

	// int bits_size = multiple_input_string[0].size();
	// for (int i = 0; i < bits_size; i++) {
	// 	stat_bits.push_back(0);
	// }

	std::cout << "msize " << multiple_input_string.size() << std::endl;
	// int cond_counter = 0;
	// // int* p = &cond_counter; ///???
	for (int i = 0; i < multiple_input_string.size(); i++)
	// for (int i = 0; i < 1; i++)
	{
		input_string = multiple_input_string[i];
		// cout << "//step "<< i+3 << " "; // For Stivens/Klima conditons
		std::cout << "c "<< i+1 << " "; 
		for (int j = 0; j < input_string.size(); j++)
			std::cout << input_string[j]; // << " ";
		std::cout << std::endl;
		switch (program_mode)
		{
			// case MIXMODE:

			// 	convertFromConditions(input_string, (i+2)%4, cond_counter++);
			// 	break;
			case VARMODE: 
				bits = convertToBits(input_string);
				if (bits.size() >= 32) 
				{
					// TODO: redo options!
					for (int k = 1; k*32 <= bits.size(); k++) 
					{
						bit_stream << std::dec << "["<<k-1<<"] 0x";
						// cout << k << endl;

						// 32 register:
						std::stringstream hex_value;
						for (int i = k*32-1; i >= k*32-1-31; i -= 4) 
						{
							int bit_value = 0;
							int ind = i - 4 + 1;
							// 4-bit variable:
							for (int j = 0; j < 4; j++)
							{
								int val = bits[ind+j] == "0"?0:1; //bits.pow(,2);
								bit_value += val*pow(2,j);
								// cout << val << " ";
							}
							hex_value << std::hex << bit_value;
							bit_stream << std::hex << bit_value;

						}
						bit_stream << std::endl;
						long int b;
						hex_value >> b;
						hex_diffs[k-1].push_back(b);
						std::map<long int,int>::iterator i = map_hex[k-1].find(b);
						if (i != map_hex[k-1].end()) {
							// cout << "double";
						}
						else {
							map_hex[k-1].insert(std::pair<long int,int>(b,1));
						}

					}
					std::cout << bit_stream.str();

				}

				break;
			case BITMODE:
				std::string start_pnt;
				// std::string::size_type sz;
				int i_dec = 513;
				if (hasPrefix_String( argv[2], "-pnt=", start_pnt)) {
					// int i_dec = std::stoi(start_pnt,&sz);
					std::istringstream buffer(start_pnt);
					buffer >> i_dec;
					convertFromBits(input_string, i_dec,i); //16914); //16897);
				}
				else {
					// int vars[27] ={1, 2, 3, 4, 6, 8, 9, 10, 11, 12, 13, 14, 16, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 399};
					int vars[128] ={10659, 10661, 10663, 10601, 10603, 10605, 10607, 10609, 10611, 10613, 10615, 10617, 10619, 10621, 10623, 10625, 10627, 10629, 10631, 10633, 10635, 10637, 10639, 10641, 10643, 10645, 10647, 10649, 10651, 10653, 10655, 10657, 10381, 10383, 10385, 10387, 10389, 10391, 10393, 10395, 10397, 10399, 10401, 10403, 10405, 10407, 10409, 10347, 10349, 10351, 10353, 10355, 10357, 10359, 10361, 10363, 10365, 10367, 10369, 10371, 10373, 10375, 10377, 10379, 11151, 11153, 11155, 11157, 11159, 11161, 11163, 11165, 11167, 11169, 11171, 11109, 11111, 11113, 11115, 11117, 11119, 11121, 11123, 11125, 11127, 11129, 11131, 11133, 11135, 11137, 11139, 11141, 11143, 11145, 11147, 11149, 10901, 10903, 10905, 10907, 10909, 10911, 10913, 10915, 10917, 10855, 10857, 10859, 10861, 10863, 10865, 10867, 10869, 10871, 10873, 10875, 10877, 10879, 10881, 10883, 10885, 10887, 10889, 10891, 10893, 10895, 10897, 10899};
					std::vector<int> var_vector;
					for (int i = 0; i < 128; i++) {
						var_vector.push_back(vars[i]);
					}
					convertFromBitsWithVector(input_string, var_vector);
				}
	
				break;
		}

	}//for




	return 1;
}
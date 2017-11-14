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

std::vector<int> convertFromBits(std::vector<std::string> message, int start_index = 1 )
{
	// xsel -b -i
	std::vector<int> message_vars;

	// std::ofstream outfile("code.alg");
	for ( int i = 0; i < message.size(); i++ )
	{
		int sign = ( message[i] == "0" )? -1: 1;
		int val = ( i + start_index ) * sign;
		// cout << "[" << i << "]"; //DEBUG
		message_vars.push_back(val);
		std::cout << message_vars[i] << " 0\n"; //TODO: end_of_line_formst = 
		// outfile << message_vars[i] << " 0\n"; //TODO: end_of_line_formst = 

	}
	std::cout << std::endl;
	// outfile.close();
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
				if (hasPrefix_String( argv[2], "-pnt", start_pnt ))
					convertFromBits(input_string, 513); //16914); //16897);
				else
					convertFromBits(input_string);
				break;
		}

	}//for




	return 1;
}
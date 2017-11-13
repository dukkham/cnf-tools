#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>

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
	return 1;
}
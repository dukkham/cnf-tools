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
#include <algorithm>
#include <ctime>
#include <cassert>
#include <random>



bool hasPrefix_String(std::string str, std::string prefix, std::string &value )
{
	int found = str.find( prefix );
	if ( found != -1 ) {
		value = str.substr( found + prefix.length( ) );
		return true;
	}
	return false;
}

size_t CalculateDoerAlpha(const size_t core_size, int b) {

	std::random_device rd;
    std::mt19937 gen(rd());


	// const size_t core_size = 10;//n

	if (core_size < 4)
	{
		return 1;
	}


	double aperi_const = 0;
	const size_t array_size = core_size / 2;

	if (b == 1) {

		double p1 = static_cast<double>(1) / core_size;
		double p0 = 1 - p1;

		std::discrete_distribution<> d({p0, p1}); // 0 with probability p0;

		int p = d(gen);
		std::cout << "random p: " << p << std::endl; 
		std::cout << "probabilities for p: " << p1 << ":"<< p0 <<  std::endl; 
		if (p == 0) 
			return 1;
		else 
			return array_size;

		
	}
	else { // for beta = b aperi_const = 1.202056;
		aperi_const = 0;
		for (int i = 0; i < array_size; i++) { //
			int val = (i+1);
			aperi_const += 1/(std::pow(val, b));
		}

	}
	std::cout << "aperi_const = " << aperi_const << std::endl;

	std::vector<size_t> alpha_values;
	std::vector<double> alpha_values_probabilities;

	alpha_values.reserve(array_size);
	alpha_values_probabilities.reserve(array_size);

	for (size_t i = 1; i <= array_size; ++i)
	{
		alpha_values.push_back(i);
		const auto probability = 1 / (std::pow(i, b)*aperi_const);
		alpha_values_probabilities.push_back(probability);
	}

	std::cout << "alpha_values_probabilities: ";
	for (size_t i = 0; i < array_size; ++i) {
		std::cout << alpha_values_probabilities[i] << " ";
	}
	std::cout << std::endl;


// Случайное число из [0, 1]
	const auto p = static_cast<double>(rand()) / RAND_MAX;

	std::cout << "p_rand: " <<  p << std::endl;

	double left_bound = 0.;
	double right_bound = 0.;
	for (size_t index = 0; index < array_size; ++index)
	{
		left_bound = right_bound;
		right_bound += alpha_values_probabilities[index];

		if (left_bound <= p && p < right_bound)
		{
			return alpha_values[index];
		}
	}


	// std::cout << "alpha_values.size(): " << alpha_values.size() << std::endl;
	
	// std::cout << "alpha_values: ";
	// for (size_t i = 0; i < array_size; ++i) {
	// 	std::cout << alpha_values[i] << " ";
	// }
	// std::cout << std::endl;
	
	return alpha_values.back();
}


// void readFromFile() {

// }

int main( int argc, char** argv ) {

	srand (time(NULL));
	std::string str;
	std::stringstream sstream;
	double function_val;

	std::vector<double> known_points_values;

	std::string known_point_file_name = "known_point_values";

	std::ifstream known_point_file( known_point_file_name.c_str() );
	if ( known_point_file.is_open() ) {
		std::cout << "reading known_point_file " << known_point_file_name << std::endl;

		while(std::getline( known_point_file, str )) {
			sstream << str;
			std::cout << "get string line: " << str << std::endl;

			while ( sstream >> function_val ) {
				std::cout << function_val << std::endl;
				known_points_values.push_back( function_val );
			}
			sstream.str( "" ); sstream.clear( );
		}
		known_point_file.close();
	}
	else {
		std::cout << "no file " << known_point_file_name << std::endl;  
	}
	std::cout << "known_points_values.size() " << known_points_values.size() <<  std::endl;


	int iter_count = 1;
	const size_t core_size = 128;//n
	int zero_mutation_count = 0;

	std::map<double, std::vector<int> > population;
	std::map<double, std::vector<int> >::iterator it_population;

	for (int j = 0; j < iter_count; j++ ){
		const auto alpha = CalculateDoerAlpha(core_size, 3); // get last(?) alpha
		// std::cout << "alpha: " << alpha << std::endl;
		
		double p = static_cast<double>(alpha) / core_size;
		std::cout << "p: " << p << std::endl;

		double p_rand = static_cast<double>(rand()) / RAND_MAX;

		// std::vector< std::pair<float, float> > probabilities_vec;
		// std::pair<float, float> probabilities = {1-p, p};

		// probabilities_vec.push_back(probabilities);

		// std::cout << "p1 = " << probabilities_vec[0].first;

		// std::random_device rd;
	 //    std::mt19937 gen(rd());

	 //    unsigned v = gen();
	 //    std::cout << v << "(" << v % 2 << ")" << std::endl;

		const auto doer_probability = p;

		std::vector<int> point;
		point.resize(core_size, 1);

		std::cout << "next_point: ";
		auto next_point = point;
		for (size_t index = 0; index < next_point.size(); ++index)
		{
			const double pm = static_cast<double>(rand()) / RAND_MAX;
			if (pm < doer_probability)
			{
				next_point[index] = (next_point[index] == 0 ? 1 : 0);
			}
			std::cout << next_point[index] << " ";
		}



		if (next_point == point) {
			std::cout << "zero_mutation!" << std::endl;
			zero_mutation_count++;
		}
		else {
			std::cout << std::endl;
			population.insert({p_rand, next_point});
		}
		//return next_point;
	}
	printf("zero_mutation_count = %d\n", zero_mutation_count);

	for (it_population = population.begin(); it_population != population.end(); it_population++) {
		printf("%f\n", it_population->first);
	}
}
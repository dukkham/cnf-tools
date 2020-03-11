#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <climits>
#include <cstdint>
#include <iomanip>
#include <cfloat>
#include <chrono>
#include <cstdio>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <cmath>
#include <mutex>
#include <queue>
#include <list>
#include <map>
#include <set>

#include <sstream>

#define uif8 uint_fast8_t
#define uif32 uint_fast32_t

using namespace std;


uif32 N = 100;

uif32 cores = thread::hardware_concurrency();

uif32 points_cnt = 0;


void task(int j)
{
    std::cout << "task1 says: " << std::endl;
    std::cout << chrono::system_clock::now().time_since_epoch().count() << std::endl;
		std::stringstream command_solve;
        command_solve << "timelimit -t 60 rokk_sat -verb=0 test.cnf > full_output_" << j;
        const std::string tmp_3 =  std::string{command_solve.str()};
        system(tmp_3.c_str());
}


int main(int argc, char *argv[]) {


	// #pragma omp parallel for
	// for (uif32 j = 0; j < cores; ++j) {
	// 	// printf("%d core\n", j);
		
	// }

	thread t1(task, 1);
	thread t2(task, 2);

	t1.join();
	t2.join();

	return 1;

}


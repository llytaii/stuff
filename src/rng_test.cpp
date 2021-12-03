#include <iostream>
#include <fstream>

#include "RNG.h"

int main()
{
	std::fstream f{ "rng_testing.txt", std::ios::out };
	if(!f.is_open()) return -1;
	f << "normalverteilung int\n";

	for (size_t i = 0; i < 201; i++)
		f << RNG::normal_value_int(0, 4) << std::endl;

	f << "normalverteilung float\n";
	for (size_t i = 0; i < 201; i++)
		f << RNG::normal_value_float(0, 4) << std::endl;

	f << "gleichverteilung int\n";
	for (size_t i = 0; i < 201; i++)
		f << RNG::uniform_value_int(0, 9) << std::endl;

	f << "gleichverteilung float\n";
	for (size_t i = 0; i < 201; i++)
		f << RNG::uniform_value_float(0, 9) << std::endl;

	return 0;
}

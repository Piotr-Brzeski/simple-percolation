//
//  main.cpp
//  simple-percolation
//
//  Created by Piotr Brzeski on 2023-02-14.
//

#include "site_percolation.h"
#include "bond_percolation.h"
#include <iostream>
#include <fstream>

template<class P>
void save(P const& p) {
	auto step = p.number_of_added_elements();
	auto file_name = "perc_" + std::to_string(step) + ".txt";
	auto file = std::ofstream(file_name);
	file << p.to_string();
	file << "\nn = " << step;
	file << "\np = " << static_cast<double>(step) / p.size();
	file << "\nc = " << p.biggest_cluster();
	file << "\nd = " << p.is_percolation() << "\n\n";
	file << p.to_array() << '\n';
}

template<class P>
void save_percolation() {
	auto p = P();
	save(p);
	while(!p.is_percolation()) {
		p.add();
		save(p);
	}
}

template<class P>
void test_percolation() {
	auto p = P();
	std::cout << p.to_string() << std::endl;
	std::cout << p.to_array() << std::endl;
	std::string s;
	while(!p.is_percolation()) {
//			std::cin >> s;
		p.add();
		std::cout << p.to_string() << std::endl;
		std::cout << p.to_array() << std::endl;
		std::cout << "Cluster: " << p.biggest_cluster() << std::endl;
		std::cout << "Perc   : " << p.is_percolation() << std::endl;
		std::cout << "---------------\n" << std::endl;
	}
}

int main(int argc, const char * argv[]) {
	try {
		save_percolation<bond_percolation<20>>();
//		test_percolation<bond_percolation<4>>();
		return 0;
	}
	catch(...) {
		std::cerr << "Exception" << std::endl;
	}
	return 1;
}

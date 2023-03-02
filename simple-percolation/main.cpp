//
//  main.cpp
//  simple-percolation
//
//  Created by Piotr Brzeski on 2023-02-14.
//

#include "site_percolation.h"
#include "bond_percolation.h"
#include <iostream>

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
		test_percolation<site_percolation<4>>();
//		test_percolation<bond_percolation<4>>();
		return 0;
	}
	catch(...) {
		std::cerr << "Exception" << std::endl;
	}
	return 1;
}

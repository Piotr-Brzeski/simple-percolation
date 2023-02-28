//
//  bond_percolation.h
//  simple-percolation
//
//  Created by Piotr Brzeski on 2023-02-14.
//

#pragma once

#include "percolation.h"
#include <string>

template<std::uint32_t L>
class bond_percolation: public percolation<2*L*(L+1)> {
public:
	std::string to_string() const {
		std::string str;
//		for(std::size_t i = 0; i < L*L; ++i) {
//			str += ' ';
//			str += to_string(this->m_data[i]);
//			if(i % L == L - 1) {
//				str += '\n';
//			}
//		}
		return str;
	}
	
protected:
	std::vector<std::uint32_t> neighbours(std::uint32_t index) const override {
		auto neighbours = std::vector<std::uint32_t>();
		if(index < L*(L+1)) {
			if(index > L) {
				neighbours.push_back(index - (L+1));
			}
			if(index <= (L-1)*(L+1)) {
				neighbours.push_back(index + (L+1));
			}
		}
		else {
			if(index % (N+1) > 0) {
				
			}
			if(index % (N+1) < L) {
				
			}
		}
//		if(index >= L) {
//			neighbours.push_back(index - L);
//		}
//		if(index < (L-1)*L) {
//			neighbours.push_back(index + L);
//		}
//		if(index % L > 0) {
//			neighbours.push_back(index - 1);
//		}
//		if(index % L < L - 1) {
//			neighbours.push_back(index + 1);
//		}
		return neighbours;
	}
	
	std::array<std::vector<std::uint32_t>, 4> edges() const override {
		auto edges = std::array<std::vector<std::uint32_t>, 4>();
		for(std::uint32_t i = 0; i < L; ++i) {
			edges[0].push_back(i*(L+1));
			edges[1].push_back(i*(L+1) + L);
			edges[2].push_back((L+i)*(L+1));
			edges[3].push_back((L+i)*(L+1) + L);
		}
		return edges;
	}
	
private:
	std::string to_string(std::uint32_t value) const {
		auto str = std::to_string(value);
		return std::string(2 - str.size(), '0') + str;
	}
	
};

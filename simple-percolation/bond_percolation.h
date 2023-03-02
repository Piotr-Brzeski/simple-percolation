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
		auto separator = [](){
			auto str = std::string("\n | ");
			for(std::size_t column = 0; column < L; ++column) {
				str += "    | ";
			}
			str += '\n';
			return str;
		}();
		std::string str;
		for(std::size_t row = 0; row <= L; ++row) {
			for(std::size_t column = 0; column <= L; ++column) {
				if(column == 0) { str += " +-"; } else if(column == L) { str += "-+"; } else { str += "-+-"; }
				if(column < L) {
					str += to_string(this->m_data[column*(L+1) + row]);
				}
			}
			if(row < L) {
				str += separator;
				for(std::size_t column = 0; column <= L; ++column) {
					str += to_string(this->m_data[(L+row)*(L+1) + column]);
					if(column < L) { str += "   "; }
				}
				str += separator;
			}
		}
		str += '\n';
		return str;
	}
	
	std::string to_array() const {
		auto str = std::string("{");
		for(std::uint32_t i = 0; i < 2*L*(L+1); ++i) {
			if(i%(L+1) == 0) {
				if(i > 0) {
					str += ",\n";
				}
				str += "{";
			}
			else {
				str += ", ";
			}
			str += std::to_string(this->m_data[i]);
			if(i%(L+1) == L) {
				str += "}";
			}
		}
		str += "}";
		return str;
	}
	
protected:
	std::vector<std::uint32_t> neighbours(std::uint32_t index) const override {
		auto neighbours = std::vector<std::uint32_t>();
		if(index < L*(L+1)) { // Horizontal
			auto row = index % (L+1);
			auto column = index / (L+1);
			if(column > 0) {
				neighbours.push_back(index - (L+1));
			}
			if(column < L-1) {
				neighbours.push_back(index + (L+1));
			}
			if(row > 0) {
				neighbours.push_back(L*(L+1) + (row-1)*(L+1) + column);
				neighbours.push_back(L*(L+1) + (row-1)*(L+1) + column + 1);
			}
			if(row < L) {
				neighbours.push_back(L*(L+1) + (row)*(L+1) + column);
				neighbours.push_back(L*(L+1) + (row)*(L+1) + column + 1);
			}
		}
		else {	// Vertical
			auto row = (index - L*(L+1)) / (L+1);
			auto column = (index - L*(L+1)) % (L+1);
			if(row > 0) {
				neighbours.push_back(index - (L+1));
			}
			if(row < L-1) {
				neighbours.push_back(index + (L+1));
			}
			if(column > 0) {
				neighbours.push_back((column-1)*(L+1) + row);
				neighbours.push_back((column-1)*(L+1) + row + 1);
			}
			if(column < L) {
				neighbours.push_back(column*(L+1) + row);
				neighbours.push_back(column*(L+1) + row + 1);
			}
		}
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
		return std::string(3 - str.size(), '0') + str;
	}
	
};

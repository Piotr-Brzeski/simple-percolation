//
//  rng.h
//  simple-percolation
//
//  Created by Piotr Brzeski on 2023-02-14.
//

#pragma once

#include <cinttypes>
#include <random>

class random_number_generator
{
public:
	random_number_generator(std::uint32_t max)
		: m_engine(std::random_device()())
		, m_dist(0, max)
	{
		static_assert(sizeof(std::uint32_t) <= sizeof(std::mt19937::result_type));
	}
	
	std::uint32_t get()
	{
		return m_dist(m_engine);
	}
	
private:
	std::mt19937                                  m_engine;
	std::uniform_int_distribution<std::uint32_t > m_dist;
};

//
//  percolation.h
//  simple-percolation
//
//  Created by Piotr Brzeski on 2023-02-14.
//

#pragma once

#include "rng.h"
#include <array>
#include <vector>
#include <set>
#include <map>
#include <cinttypes>
#include <random>
#include <algorithm>

template<std::uint32_t M>
class percolation {
public:
	percolation()
		: m_data{}
		, m_last_cluster(0)
		, m_rng(M-1)
	{
	}
	
	virtual ~percolation() {
	}
	
	void add() {
		auto index = m_rng.get();
		while(m_data[index] > 0) {
			index = m_rng.get();
		}
		auto neighbour_indices = neighbours(index);
		auto neighbours = std::set<std::uint32_t>();
		for(auto neighbour_index: neighbour_indices) {
			auto neighbour = m_data[neighbour_index];
			if(neighbour > 0) {
				neighbours.insert(neighbour);
			}
		}
		if(neighbours.empty()) {
			m_data[index] = ++m_last_cluster;
			return;
		}
		auto begin = neighbours.begin();
		auto cluster = *begin;
		m_data[index] = cluster;
		neighbours.erase(begin);
		if(!neighbours.empty()) {
			merge_clusters(cluster, neighbours);
		}
	}
	
	bool is_percolation() const {
		auto edge_indices = edges();
		auto set = sorted_clusters(edge_indices[0]);
		auto intersection = std::vector<std::uint32_t>(set.size(), 0);
		std::copy(set.begin(), set.end(), intersection.begin());
		for(std::size_t i = 1; i < 4; ++i) {
			if(intersection.empty()) {
				return false;
			}
			set = sorted_clusters(edge_indices[i]);
			if(set.empty()) {
				return false;
			}
			auto new_intersection = std::vector<std::uint32_t>(std::min(set.size(), intersection.size()), 0);
			auto end = std::set_intersection(set.begin(), set.end(), intersection.begin(), intersection.end(), new_intersection.begin());
			new_intersection.erase(end, new_intersection.end());
			intersection.swap(new_intersection);
		}
		return !intersection.empty();
	}
	
	std::uint32_t biggest_cluster() const {
		auto cluster_sizes = std::map<std::uint32_t, std::uint32_t>();
		for(auto cluster: m_data) {
			if(cluster > 0) {
				++cluster_sizes[cluster];
			}
		}
		if(cluster_sizes.empty()) {
			return 0;
		}
		auto it = std::max_element(cluster_sizes.begin(), cluster_sizes.end(), [](auto& p1, auto p2){ return p1.second < p2.second; });
		return it->first;
	}
	
protected:
	virtual std::vector<std::uint32_t> neighbours(std::uint32_t index) const = 0;
	virtual std::array<std::vector<std::uint32_t>, 4> edges() const = 0;
	
	std::array<std::uint32_t, M> m_data;
	
private:
	std::set<std::uint32_t> sorted_clusters(std::vector<std::uint32_t> const& indices) const {
		auto clusters = std::set<std::uint32_t>();
		for(auto index : indices) {
			auto cluster = m_data[index];
			if(cluster > 0) {
				clusters.insert(cluster);
			}
		}
		return clusters;
	}
	
	template<typename collection>
	void merge_clusters(std::uint32_t cluster, collection const& old_clusters) {
		for(auto& cell : m_data) {
			if(old_clusters.contains(cell)) {
				cell = cluster;
			}
		}
	}
	
	std::uint32_t           m_last_cluster;
	random_number_generator m_rng;
};

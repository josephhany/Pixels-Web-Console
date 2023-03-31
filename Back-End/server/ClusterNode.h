#include <list>
#include <vector>
#include <array>
#include "Query.h"
#pragma once

using namespace std;

// Stores data about single node per single unit of time
class ClusterNode
{

private:

	// important: this will be used to distinguish between a lambda worker and a trino worker
	// 1 for lambda worker, 0 for trino worker
	int _node_type;

	double _node_cost_per_hour;

	int _node_id;

	int _node_available_capacity;

	int _node_total_cost;

	int _node_total_used_capacity;
	
	int _node_cpu_usage;

	int _node_max_cpu_usage;

	int _max_runnable_threads;

	float _cost_per_second;

	// it will be set to zero if the node is already running
	// otherwise, it will be set to the time the node takes to start up
	int _startup_time;
	
public:

	ClusterNode();

	// ClusterNode(const int node_type, const int node_id, const int node_max_cpu_usage, const int max_runnable_threads);
	ClusterNode(const int node_type, const int node_id, const int node_max_cpu_usage, const int max_runnable_threads, const float cost_per_second);

	// Initializes class object
	ClusterNode(const int node_type, const double node_cost_per_hour, const int node_id, const int node_available_capacity, const int node_total_cost, const int node_total_used_capacity, const int node_cpu_usage);

	// Frees used memory
	~ClusterNode();
	
	inline const int get_node_type() const { return _node_type; }
	inline const double get_node_cost_per_hour() const { return _node_cost_per_hour; }
	inline const int get_node_id() const { return _node_id; }
	inline const int get_node_available_capacity() const { return _node_available_capacity; }
	inline const int get_node_total_cost() const { return _node_total_cost; }
	inline const int get_node_total_used_capacity() const { return _node_total_used_capacity; }
	inline const int get_node_cpu_usage() const { return _node_cpu_usage; }
	inline const int get_node_max_cpu_usage() const { return _node_max_cpu_usage; }
	inline const int get_max_runnable_threads() const { return _max_runnable_threads; }
	inline const float get_cost_per_second() const { return _cost_per_second; }
	
};

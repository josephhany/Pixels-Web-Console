#include "ClusterNode.h"

ClusterNode::ClusterNode()
{
	_node_id = -1;
}

/*
*	node_type: 1 for lambda worker, 0 for trino worker
*
*/

// ClusterNode::ClusterNode(const int node_type, const int node_id, const int node_max_cpu_usage, const int max_runnable_threads)
ClusterNode::ClusterNode(const int node_type, const int node_id, const int node_max_cpu_usage, const int max_runnable_threads, const float cost_per_second)
{
	_cost_per_second = cost_per_second;
	_node_type = node_type;
	_node_id = node_id;
	_node_max_cpu_usage = node_max_cpu_usage;
	_max_runnable_threads = max_runnable_threads;
	_node_available_capacity = 0;
	_node_total_cost = 0;
	_node_total_used_capacity = 0;
	_node_cpu_usage = 0;
	_startup_time = 0;
}

// Initializes class object
ClusterNode::ClusterNode(const int node_type, const double node_cost_per_hour, const int node_id, const int node_available_capacity, const int node_total_cost, const int node_total_used_capacity, const int node_cpu_usage):
											_node_type(node_type),
											_node_cost_per_hour(node_cost_per_hour),
											_node_id(node_id),
											_node_available_capacity(node_available_capacity),
											_node_total_cost(node_total_cost),
											_node_total_used_capacity(node_total_used_capacity),
											_node_cpu_usage(node_cpu_usage)

{
}

// Frees used memory
ClusterNode::~ClusterNode() { }
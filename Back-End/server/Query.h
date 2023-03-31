#include <list>
#include <vector>
#include <array>
#include <map>
#pragma once

using namespace std;

// Stores data about single class
class Query
{

private:
	
    // estimated execution time of query
    double _estimated_execution_time;

    double _estimated_storage_space;

    double _estimated_cpu_usage;

    double _estimated_network_time;

    string _query_string;
    
    int _query_id_original; // according to the string of the query

    double _issuance_time;

    int _query_fragment_id; // according to the issuance time
    
    double _assignment_time;

    int _parent_id;
	
public:

	// Initializes class object
	// Query(double execution_time, double storage_space, double cpu_usage, double network_time, string query_string, int query_id_original, double issuance_time, int query_fragment_id);
    Query(float execution_time, string query_string, int query_id_original, double issuance_time, int parent_id);

	// Frees used memory
	~Query();

    inline const float get_estimated_execution_time() const { return _estimated_execution_time; } //
    
    inline const double get_estimated_storage_space() const { return _estimated_storage_space; }

    inline const double get_estimated_cpu_usage() const { return _estimated_cpu_usage; }

    inline const double get_estimated_network_time() const { return _estimated_network_time; }

    inline const string get_query_string() const { return _query_string; } //

    inline const int get_query_id_original() const { return _query_id_original; } //

    inline const double get_issuance_time() const { return _issuance_time; } //

    inline const int get_query_fragment_id() const { return _query_fragment_id; }

    inline const double get_assignment_time() const { return _assignment_time; }

    inline void set_assignment_time(double assignment_time) { _assignment_time = assignment_time; }

    inline double get_set_assignment_time() { return _assignment_time; }

    inline double get_parent_id() { return _parent_id; }

};

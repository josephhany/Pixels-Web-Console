//#include <algorithm>
#include <iostream>
#include <iterator>
//#include <list>
#include <vector>
//#include <map>
#include <fstream>
#include <string>
#include <map>
//#include <string.h>
#include <set>
#pragma once

using namespace std;

class Query;
class ClusterNode;

// Reads configration file and stores parsed objects
class Configuration
{
private:
    vector<int> _queries_keys;
    // vector<vector<Query*>> _queries_values;
    vector<Query*> _queries_values;
    vector<ClusterNode*> _cluster_nodes;
    
    vector<int> _cluster_nodes_threads;

    vector<ClusterNode*> _cluster_nodes_cross_threads;

	map<ClusterNode*,int> _cluster_nodes_count;
    

    // set<pair<ClusterNode*,int>> _threads_cluster_nodes;
    // set<int> _threads_cluster_nodes;

    // map<int,ClusterNode*> _threads_cluster_nodes_map;

    // map<ClusterNode*,int> _cluster_nodes_count;


    std::set<pair<int,int>> _queries_unique_ids;

public:
    Configuration(vector<string> queriesStrings, vector<string> queriesFrequncies, int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms, vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect);
	void ParseFile(char* fileName);
	// Returns reference to list of parsed classes
	//inline const map<char*,vector<CourseClass*>>& GetCourseClasses() const { return _courseClasses; }
    inline const vector<int>& GetQueries_keys() const { return _queries_keys; }
    inline const vector<Query*>& GetQueries_values() const { return _queries_values; }
    
    inline const vector<ClusterNode*>& GetCluster_nodes() const { return _cluster_nodes; }

	// Returns number of parsed classes
	inline int GetNumberOfUniqueQueries() const { return (int)_queries_values.size(); }

    inline const std::set<pair<int,int>>& GetQueries_unique_ids() const { return _queries_unique_ids; }

    // inline set<pair<int,ClusterNode*>> GetCluster_nodes_threads() { return _cluster_nodes_threads; }

    inline vector<int> GetCluster_nodes_threads() { return _cluster_nodes_threads; }
    inline vector<ClusterNode*> GetCluster_nodes_cross_threads() { return _cluster_nodes_cross_threads; }


    inline map<ClusterNode*,int> GetCluster_nodes_count() { return _cluster_nodes_count; }

    // inline set<pair<ClusterNode*,int>> GetThreads_cluster_nodes() const { return _threads_cluster_nodes; }
    // inline set<int> GetThreads_cluster_nodes() const { return _threads_cluster_nodes; }
    
    
};

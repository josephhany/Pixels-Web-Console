#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include <list>
#include <map>
#include <set>
//#include <windows.h>
// #include<bits/stdc++.h>
#include<string.h>
#include "ClusterNode.h"
#include "Configuration.h"
#include <limits>
#include <algorithm>
// #include "ChromosomeCreator.h"
#include <thread>
#pragma once


using namespace std;
class Schedule;
class Algorithm;
class ChromosomeCreator;

// Number of working hours per day
#define DAY_HOURS	24

#define time_slot_duration_sec 60

#define TIME_SLOT_DURATION_SEC	60
// Number of days in week
#define DAYS_NUM	5

#define intialPopulation     1

#define crossingOver     2

// Schedule chromosome
class Schedule
{
private:

	// Number of crossover points of parent's class tables
	int _numberOfCrossoverPoints;

	// Number of classes that is moved randomly by single mutation operation
	int _mutationSize;

	// Probability that crossover will occure
	int _crossoverProbability;

	// Probability that mutation will occure
	int _mutationProbability;

	// Fitness value of chromosome
	float _fitness;

	// Flags of class requiroments satisfaction
	vector<bool> _criteria;

	// Time-space slots, one entry represent one hour in one classroom
	// Time-space slots, one entry represent one hour in all the nodes in a cluster
	// vector<vector<ClusterNode*>> _slots;

	vector<list<ClusterNode*>> _slots;

	vector<int> _num_queries_per_sec;
	vector<string> _day_time_in_mins;

	string _overall_cost;

	vector<int> _parents_ids;
	vector<int> _queries_end_time_slot;

	vector<float> _cost_per_sec;

	// vector<vector<pair<Query*,int>>> _slots_decision;

	// vector<map<int,list<Query*>>> _slots_decision;

	// map<Query*,float> queries_left_time;

	// map<Query*,list<int>> queries_random_nodes;

	vector<int> _queries_init_time_slot;
	// map<int,list<Query*>> _time_slot_queries;
	map<int,vector<Query*>> _time_slot_queries;
	map<Query*,float> _queries_estimated_time; // estimated thread execution time

	// set<pair<pair<int,int>,ClusterNode*>> _cluster_nodes_threads;

	// map<ClusterNode*,int> _cluster_nodes_count;


	// Class table for chromosome
	// Used to determine first time-space slot used by class
	// map<ClusterNode*, vector<bool>> _nodes;

	// <node_id, map< time slot, query listt> >
	map<int,map<int,list<Query*>>> _nodes;
	// map<int,map<int,vector<Query*>>> _nodes;

	// create a structure to hold the number of total available threads for each query
	map<Query*,map<int,int>> queries_time_slot_threads_count;

	// vector<int> _queries_per_time_slots;

	bool verbose;

public:

	Configuration* config;

	// Initializes chromosomes with configuration block (setup of chromosome)
	Schedule(int numberOfCrossoverPoints, int mutationSize,int crossoverProbability, int mutationProbability,char* fileName,vector<string> queriesStrings, vector<string> queriesFrequncies,int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime,bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms,vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect);

	// Copy constructor
	Schedule(const Schedule& c, bool setupOnly);

	// Makes copy ot chromosome
	Schedule* MakeCopy(bool setupOnly) const;

	// Makes new chromosome with same setup but with randomly chosen code
	Schedule* MakeNewFromPrototype() const;

    // int rand_from_available_days(ClusterNode * course) const;

    // double rand_from_available_times(ClusterNode * course,int day) const;

	// Performes crossover operation using to chromosomes and returns pointer to offspring
	Schedule* Crossover(const Schedule& parent2) const;

	// populate the schedule based on the decisions
	// void Populate(Schedule& newChromosome, const vector<vector<pair<Query*,int>>> &slots_decision) const;
	void Populate();

	// Performs mutation on chromosome
	void Mutation();

	// Calculates fitness value of chromosome
	void CalculateFitness();

	// Returns fitness value of chromosome
	float GetFitness() const { return _fitness; }

	// Returns a map of nodes in the cluster and a boolean vector for each node indicating if it up or not in a given time slot
	inline map<int,map<int,list<Query*>>> & GetNodes() { return _nodes; }
	// inline map<int,map<int,vector<Query*>>> & GetNodes() { return _nodes; }

	// Returns array of flags of class requiroments satisfaction
	inline const vector<bool>& GetCriteria() const { return _criteria; }

	// Return reference to array of time-space slots
	// inline const vector<map<int,list<Query*>>> & GetSlots() const { return _slots; }

	inline const Configuration* GetConfig() const { return config; }

	inline const vector<list<ClusterNode*>> & GetSlots() const { return _slots; }
	// inline const map<int,list<Query*>> & GetTimeSlotQueries() const { return _time_slot_queries; }
	inline const map<int,vector<Query*>> & GetTimeSlotQueries() const { return _time_slot_queries; }
	inline const map<Query*,float> & GetQueriesEstimatedTime() const { return _queries_estimated_time; }
	inline const vector<int> & GetQueriesInitTimeSlot() const { return _queries_init_time_slot; }
	// inline vector<int> & GetQueriesInitTimeSlot() { return _queries_init_time_slot; }

	inline void SetNumQueriesPerSec(vector<int> num_queries_per_sec) { _num_queries_per_sec = num_queries_per_sec; }

	inline void SetDayTimeMins(vector<string> day_time_in_mins){ _day_time_in_mins = day_time_in_mins; }

	inline void SetOverallCost(string overall_cost){ _overall_cost = overall_cost; }

	inline void SetCostPerSec(vector<float> cost_per_sec){ _cost_per_sec = cost_per_sec; };

	inline void SetParentsIds(vector<int> parents_ids){ _parents_ids = parents_ids; }
	inline void SetQueriesEndTimeSlot(vector<int> queries_end_time_slot){ _queries_end_time_slot = queries_end_time_slot; }

	// parents_ids
	// _queries_end_time_slot

	inline const vector<int> GetNumQueriesPerSec() const { return _num_queries_per_sec; }

	inline const vector<string> GetDayTimeMins(){ return _day_time_in_mins; }

	inline const string GetOverallCost(){ return _overall_cost; }

	inline const vector<float> GetCostPerSec(){ return _cost_per_sec; };

	inline const vector<int> GetParentsIds(){ return _parents_ids; }
	inline const vector<int> GetQueriesEndTimeSlot(){ return _queries_end_time_slot; }

	// inline const vector<int> & GetQueriesPerSec() const { return _queries_per_time_slots; }
	// GetQueriesPerSec()
	// GetNodesPerSec()
	// GetMoneyPerSec()

};

// Genetic algorithm
class Algorithm
{

private:

	// Population of chromosomes
	vector<Schedule*> _chromosomes;

	// Inidicates wheahter chromosome belongs to best chromosome group
	vector<bool> _bestFlags;

	// Indices of best chromosomes
	vector<int> _bestChromosomes;

	// Number of best chromosomes currently saved in best chromosome group
	int _currentBestSize;

	// Number of chromosomes which are replaced in each generation by offspring
	int _replaceByGeneration;

	// Prototype of chromosomes in population
	Schedule* _prototype;

	// Current generation
	int _currentGeneration;

	// Pointer to global instance of algorithm
	 Algorithm* _instance;

	ChromosomeCreator** chromosome_creator_engines;

public:

	// Returns reference to global instance of algorithm
	// Algorithm& GetInstance(char* fileName);
	Algorithm& GetInstance(vector<string> queriesStrings, vector<string> queriesFrequncies, int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms, vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect);

	// Frees memory used by gloval instance
	 void FreeInstance();

	// Initializes genetic algorithm
	Algorithm(int numberOfChromosomes, int replaceByGeneration, int trackBest,
		Schedule* prototype);

	// Frees used resources
	~Algorithm();

	// Starts and executes algorithm
	void Start();

	// Returns pointer to best chromosomes in population
	Schedule* GetBestChromosome() const;

	// Returns current generation
	inline int GetCurrentGeneration() const { return _currentGeneration; }

private:

	// Tries to add chromosomes in best chromosome group
	void AddToBest(int chromosomeIndex);

	// Returns TRUE if chromosome belongs to best chromosome group
	bool IsInBest(int chromosomeIndex);

	// Clears best chromosome group
	void ClearBest();

};

class ChromosomeCreator
{
    private:
        std::thread * _th;
        Schedule* _prototype;
        Schedule* _it;
        int _phase;
        void IntialPopulation();
        void CrossingOver();
    public:
        // ChromosomeCreator(Schedule* prototype, Schedule* it);
		ChromosomeCreator(Schedule* prototype);
        void execute();
        static void start(ChromosomeCreator * me);
        void setThread(std::thread * p_th);
        void waitForRunToFinish();
		Schedule* GetIt();
        ~ChromosomeCreator();
};
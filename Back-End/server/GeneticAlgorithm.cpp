#include<iostream>
using namespace std;
#include <math.h>
#include<string.h>
#include "Schedule.h"
#include "GeneticAlgorithm.h"
#include <iomanip>
#include <sstream>


Schedule* GeneticAlgorithm(vector<string> queriesStrings, vector<string> queriesFrequncies, int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms, vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect){

	Algorithm *genetic_algorithm=&genetic_algorithm->Algorithm::GetInstance(queriesStrings, queriesFrequncies, mxServers, mxLambda, mxBudget, boundTime, Realtime, EnableLambda, VMtypesVect, NewVms, CPUsNew, MoneyNew, queriesCostsVect);

	// Here, we start the whole algorithm
	genetic_algorithm->Start();

    // Now, we have the best chromosome after several generations
	Schedule* best_chromosome = genetic_algorithm->GetBestChromosome();

    // That's how we get the nodes used to fulfill the workload
    // map<node_id,map<time_slot,queries scheduled in that time slot for this node_id>>
	map<int,map<int,list<Query*>>> final_schedule=genetic_algorithm->GetBestChromosome()->GetNodes();

	for(auto it = final_schedule.begin(); it!=final_schedule.end();it++){
	    cout<< "node type --> " <<it->first<<endl;
	    cout<< "Times:\t";
	    for(auto it2 = (it->second).begin(); it2!=(it->second).end();it2++){
	        cout<< it2->first << "\t";
	    }
	    cout<<"\n";
	}

	for(map<int,map<int,list<Query*>>>::iterator node = best_chromosome->GetNodes().begin(); node != best_chromosome->GetNodes().end(); node++ ){

		// for each time-space slot in node
		for( map<int,list<Query*>>::iterator time_slot_queries = node->second.begin(); time_slot_queries != node->second.end(); time_slot_queries++ ){
			time_slot_queries->second.sort();
			time_slot_queries->second.unique();
		}
	}

	std::vector<int> num_queries_per_sec(24*60, 0);

    for(int i=0; i< 24*60 ; i++){num_queries_per_sec[i] = best_chromosome->GetSlots().at(i).size();}

	std::vector<string> day_time_in_mins;
	
	for(int i=0; i<24; i++){
		for(int j=0; j<60; j++){
			string hour = std::to_string(i);
			string min = std::to_string(j);
			if(i<10)hour = "0"+std::to_string(i);
			if(j<10)min = "0"+std::to_string(j);

			string time = hour + ":" + min;

			day_time_in_mins.push_back(time);
		}
	}
	
	float overall_cost = 0;

	for(int i=0; i< best_chromosome->GetSlots().size();i++){
		for(auto it = best_chromosome->GetSlots().at(i).begin(); it != best_chromosome->GetSlots().at(i).end(); ++it){
			overall_cost += (*it)->get_cost_per_second();
		}
	}

	stringstream stream;
    // Set precision level to 3
    stream.precision(3);
    stream << fixed;
    
    // Convert float to string
    stream<<overall_cost;  
    string str  = stream.str();  
    cout<<str<<endl;

	std::vector<float> cost_per_sec(24*60, 0);

	for(int i=0; i< 24*60 ; i++){
		float cost = 0;
        for(auto it = best_chromosome->GetSlots().at(i).begin(); it != best_chromosome->GetSlots().at(i).end(); ++it){
            cost += (*it)->get_cost_per_second();
        }
		cost_per_sec[i] = cost;
	}

	best_chromosome->SetNumQueriesPerSec(num_queries_per_sec); // take it is the number of servers now
	best_chromosome->SetDayTimeMins(day_time_in_mins);
	best_chromosome->SetOverallCost(std::to_string(overall_cost));
	best_chromosome->SetCostPerSec(cost_per_sec);

	int num_of_queries = best_chromosome->GetConfig()->GetQueries_values().size();
	vector<int> _queries_end_time_slot(num_of_queries,0);

	for(auto it = best_chromosome->GetTimeSlotQueries().begin(); it != best_chromosome->GetTimeSlotQueries().end(); ++it){
		for(int i=0; i<it->second.size() ; i++){
			int query_index = (it->second.at(i)->get_query_id_original()) - 1;
			int end_time_slot = it->first;
			if ( _queries_end_time_slot[query_index] < end_time_slot) _queries_end_time_slot[query_index] = end_time_slot;
		}
	}
	vector<int> parents_ids;

	for(int i=0 ;i<best_chromosome->GetConfig()->GetQueries_values().size();i++){
		parents_ids.push_back(best_chromosome->GetConfig()->GetQueries_values().at(i)->get_parent_id());
	}


	best_chromosome->SetParentsIds(parents_ids);
	best_chromosome->SetQueriesEndTimeSlot(_queries_end_time_slot);


	cout<< "best chromosome fitness: " <<best_chromosome->GetFitness()<<endl;
    cout<< "best chromosome nodes size: " <<best_chromosome->GetNodes().size()<<endl;


	return best_chromosome;
}
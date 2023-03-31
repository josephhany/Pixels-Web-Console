#include <iostream>
#include <map>
#include <vector>
#include "Configuration.h"
#include "Schedule.h"
// #include "Room.h"
#include "Query.h"
#include <ctime>
#include <iomanip>
#include <math.h>


// Initializes chromosomes with configuration block (setup of chromosome)
Schedule::Schedule(int numberOfCrossoverPoints, int mutationSize,
				   int crossoverProbability, int mutationProbability,char* fileName,
				   vector<string> queriesStrings, vector<string> queriesFrequncies, 
				   int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, 
				   bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms,
				   vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect
				   ) : _mutationSize(mutationSize),
				   _numberOfCrossoverPoints(numberOfCrossoverPoints),
				   _crossoverProbability(crossoverProbability),
				   _mutationProbability(mutationProbability),
				   _fitness(0)
{

    verbose = false;

	//printf("bgining of Schedule::Schedule(int)ooooooooooooooooooooooo\n");
	config=new Configuration(queriesStrings, queriesFrequncies, mxServers, mxLambda, mxBudget, boundTime, Realtime, EnableLambda, VMtypesVect, NewVms, CPUsNew, MoneyNew, queriesCostsVect);
	// _cluster_nodes_threads = config->GetCluster_threads_nodes();

	// modify here ??? initialize the nodes
	

	

	//printf("after config=new Configuration();\n");
	//config->ParseFile(fileName); //modify hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee

	// reserve space for time-space slots in chromosomes code
	// _slots.resize( );//* Configuration::GetInstance().GetNumberOfRooms() );
//	_slots.resize(DAY_HOURS*60*60); //*12
    _slots.resize(DAY_HOURS*60); //*12
	// _slots_decision.resize(DAY_HOURS*60*60); //*12

	_queries_init_time_slot.resize(config->GetNumberOfUniqueQueries());

	//printf("after _slots.resize(DAY_HOURS*60*60*1000);\n");

	// for(int i=0;i<_slots.size();i++){
	// 	//printf("resizeing _slots[%queries]\n",i);
	// 	_slots[i].resize(10);
	// }

	// reserve space for flags of class requirements
	//_criteria.resize( config->GetNumberOfCourseClasses() * 5 );
	//printf("end of Schedule::Schedule(int)\n");
}

// Copy constructor
Schedule::Schedule(const Schedule& c, bool setupOnly)
{

	if( !setupOnly )
	{
		// copy code
		_slots = c._slots;
		_nodes = c._nodes;
		//cout<<"wsl\n";
		// copy flags of class requirements
		//_criteria = c._criteria;
		config=c.config;
		// _cluster_nodes_threads = c._cluster_nodes_threads;
		// copy fitness
		_fitness = c._fitness;

		_queries_init_time_slot=c._queries_init_time_slot;
	}
	else
	{
		// reserve space for time-space slots in chromosomes code
//		_slots.resize(DAY_HOURS*60*60); //*12
        _slots.resize(DAY_HOURS*60); //*12
		// _slots_decision.resize(DAY_HOURS*60*60); //*12

		
		
		config=c.config;

		

		_queries_init_time_slot.resize(config->GetNumberOfUniqueQueries());
		// _cluster_nodes_threads = c._cluster_nodes_threads;
		
		// for(int i=0;i<_slots.size();i++){
		// 	_slots[i].resize(10);
		// 	}

		// reserve space for flags of class requirements
		//_criteria.resize( config->GetNumberOfCourseClasses() * 5 );
		//cout<<"wsl2\n";
	}

	// copy parameters
	_numberOfCrossoverPoints = c._numberOfCrossoverPoints;
	_mutationSize = c._mutationSize;
	_crossoverProbability = c._crossoverProbability;
	_mutationProbability = c._mutationProbability;
}

// Makes copy ot chromosome
Schedule* Schedule::MakeCopy(bool setupOnly) const
{
	// make object by calling copy constructor and return smart pointer to new object
	//cout<<"gai mn makecopy\n";
	return new Schedule( *this, setupOnly );
}

// int Schedule::rand_from_available_days(CourseClass * course) const
// {
// 	//int size= DAYS_NUM;
// 	//int rand_day;
// 	//while(1){
// 	//	rand_day=rand()%size;
// 	//	if(course->available_days[rand_day]!=false){
// 	//		break;
// 	//	}
// 	//}
// 	//return rand_day;
// 	return 0;
// }

// double Schedule::rand_from_available_times(CourseClass * course,int day) const
// {
// 	//int number_of_avaialable_times=course->available_times[day].size();
// 	//return course->available_times[day][rand()%number_of_avaialable_times];
// 	return 0;
// }

//double Schedule::rand_from_available_sections(CourseClass * course,int day) const
//{
	//map<char*,list<CourseClass*>> _courseClasses;
	
	//int number_of_avaialable_times=course->available_times[day].size();
	//return course->available_times[day][rand()%number_of_avaialable_times];
//}

// Makes new chromosome with same setup but with randomly chosen code
Schedule* Schedule::MakeNewFromPrototype() const
{
	// number of time-space slots
	int size = (int)_slots.size();

	// //cout<<"before the mass\n";
	// make new chromosome, copy chromosome setup
//	cout<<"gy mn mn MakeNewFromPrototype"<<endl;
	
	Schedule* newChromosome = new Schedule( *this, true );

	// //cout<<"e7na hena\n";

	const vector<Query*> queries = config->GetQueries_values();

	// //cout<<"config->GetQueries_keys().at(0) = "<< config->GetQueries_keys().at(0)<<endl;

	// //cout<<"config->GetQueries_values().at(0) = "<< config->GetQueries_values().at(0)->get_query_string()<<endl;

	map<double,int> rand_time_count;

	//cout<<"hwa da5al bs ma3rafsh eh ely 7asal ??????????\n";
	
	// //cout<<"before the mass2\n";
	//cout<< "bos el queries size" << queries.size()<<endl;

	for(int i=0; i<queries.size();i++){

		// //cout<<"inside the mass\n";

		int bound_limit = 3; //at maximum the query can get assigned after 3 time slots
		
		int issuance_time = queries[i]->get_issuance_time();

		double rand_time;

		time_t start, end;
		time(&start);
		ios_base::sync_with_stdio(false);
		
		do { 
			rand_time = (rand()%(bound_limit))+issuance_time;
			//cout<<rand_time<<endl;
			// rand_time = rand()%(3)+issuance_time;
			// rand_time_count[rand_time]++;
		}
		while(rand_time >= DAY_HOURS*60);
		// while(rand_time >= DAY_HOURS || rand_time_count[rand_time]>=3);
//		while(rand_time >= DAY_HOURS*60*60);

//        cout<< "this query "<< queries[i]->get_query_string() << " was inssued here "<<issuance_time<<" and will be put here "<<rand_time<<endl;

		time(&end);
		double time_taken = double(end - start);
		//cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " sec " << endl;

		//cout<<"ana hena\n <><><><><><><><><><><><><><><><><><><><><><><><><><>";


		

		



		//cout<<"rand_time: "<<rand_time<<endl;

		newChromosome->_queries_init_time_slot[i] = rand_time;
		
		// //cout<<"after newChromosome->_queries_init_time_slot[i] = rand_time;\n";

		newChromosome->_time_slot_queries[rand_time].push_back(queries[i]);
//		uncomment again?
//		cout<< "queries[i]->get_query_id_original() : " <<queries[i]->get_query_id_original()<<endl;

		//cout<< "size of _time_slot_queries[rand_time]: "<<newChromosome->_time_slot_queries[rand_time].size()<<endl;

		// //cout<<"after newChromosome->_time_slot_queries[rand_time].push_back(queries[i]);\n";

		newChromosome->_queries_estimated_time[queries[i]] = queries[i]->get_estimated_execution_time();

		// //cout<<"after newChromosome->_queries_estimated_time[queries[i]] = queries[i]->get_estimated_execution_time();\n";

	}

	

/*	

	for( int i = 0; i<c.size(); i++ )
	{
		for( int j = 0; j< queries[i].size(); j++ )
		{
			//printf("iteration %queries %queries\n",i,j);

			// choose random node type
			// either lambda or trino
			int rand_node_type=rand()%2;

			int node_type_offset;

			if( rand_node_type == 0 ) node_type_offset = 0; //trino
			else node_type_offset = 5; //lambda


			int rand_node_index=rand()%(5)+node_type_offset;

			int issuance_time = queries[i][j]->get_issuance_time();
			//cout<<"issuance_time = "<<issuance_time<<endl;

			// get the duration of this random class
			int dur = queries[i][j]->get_estimated_execution_time(); //*12;

			// choose random time slot starting from the time of issuance of the query
			// double rand_time=rand()%(DAY_HOURS-issuance_time)+issuance_time;

			// max_time_slot is the last time slot that can be used to execute this query in
			int bound_limit = 3; //at maximum the query can get assigned after 3 time slots

			
			double rand_time;
			
			do { rand_time = rand()%(bound_limit)+issuance_time; } while(rand_time >= DAY_HOURS);

			newChromosome->_slots_decision[rand_time][rand_node_index].push_back(queries[i][j]);
			newChromosome->queries_left_time[queries[i][j]][queries[i][j]->get_estimated_execution_time()];
			
			for(int k=0;k<dur;k++)
			{

				queries_random_nodes[queries[i][j]].push_back(rand_node_index);

				// newChromosome->_slots_decision[rand_time+k].push_back(make_pair(queries[i][j],rand_node_index));



				// queries special structure that hold both the remaining time and the next node to execute the query
				// we will push in it the next random node


			}

			// newChromosome->Populate(*newChromosome,_slots_decision);

			// for(int k=0;k<dur;k++)
			// {
			// 	// set time-space slot to class
				
			// 	newChromosome->_slots[rand_time+k][rand_node_index].push_back(queries[i][j]);
			// 	newChromosome->_nodes[rand_node_index][rand_time+k].push_back(queries[i][j]);
			// }

		}
	}

*/

	newChromosome->Populate();

	newChromosome->CalculateFitness();
	// //cout<<_fitness<<endl;

	// return smart pointer
	return newChromosome;
}


// populate schedule
// void Schedule::Populate(Schedule& newChromosome,const vector<vector<pair<Query*,int>>> &slots_decision) const
// void Schedule::Populate()
// {
// 	for(int k=0; k < _slots_decision.size();k++){
// 		for(int l=0; l < _slots_decision[k].size();l++){
			
// 			int dur = _slots_decision[k][l].first->get_estimated_execution_time();

// 			_slots[k][_slots_decision[k][l].second].push_back(_slots_decision[k][l].first);
// 			_nodes[_slots_decision[k][l].second][k].push_back(_slots_decision[k][l].first);
// 			}
// 		}
// }

			// _cluster_nodes_count[it->second]--;
			// if(nodes_ordered.front().second() == 0) nodes_ordered.pop_front(); // if the count is zero, remove the node from the list
			// total_threads_count += nodes_ordered.front().first().number_of_threads();
			// total_estimated_execution_time -= nodes_ordered.front().first().number_of_threads() * time_slot_duration_sec;

// check if there are already any nodes or not


// if yes, let's see wether these are enough or not
// if there are enough, we will use them

// if not, let's add more nodes

// _queries_init_time_slot

// _time_slot_queries
// _slots
// _queries_estimated_time

void Schedule::Populate()
{



	int push_backs = 0;

	vector<int> cluster_nodes_threads = config->GetCluster_nodes_threads();
	
	map<ClusterNode*,int> cluster_nodes_count = config->GetCluster_nodes_count();

	vector<ClusterNode*> cluster_nodes_cross_threads = config->GetCluster_nodes_cross_threads();

	//cout<<"cluster_nodes_threads.size() = "<<cluster_nodes_threads.size()<<endl;
	//cout<<"cluster_nodes_count.size() = "<<cluster_nodes_count.size()<<endl;
	//cout<<"_slots.size() = "<<_slots.size()<<endl; //tmam
	//cout<<"_time_slot_queries.size() = "<< _time_slot_queries.size()<<endl;

//  uncomment again?
	for(auto tsq : _time_slot_queries){

		// if (tsq.second.size()!=1)
//		cout<< tsq.first << " ------ " << tsq.second.at(0)->get_query_id_original()<<endl;
	}

	int nodes_count_init = 0;

	for (auto it = cluster_nodes_count.begin() ; it !=cluster_nodes_count.end(); ++it ){
		nodes_count_init += it->second;
	}
//  uncomment again?
//	cout <<"nodes_count_init -=-=-= :" << nodes_count_init<<endl;

	for(int i=0; i<_slots.size();i++){
		
		if(_time_slot_queries.find(i) == _time_slot_queries.end()){
			// cout << "yes\n";
			continue;
			// cout << "after continue\n";
		}
		// else{
		// 	// cout<< "the i : "<< i<<endl;
		// 	// cout<<"see the queries: \n";
		// 	for(Query* q : _time_slot_queries[i]){
		// 		if(q->get_query_id_original() != 1) cout<<q->get_query_id_original()<<endl;
		// 	}
		// }

		//cout<<"hena eshta tmm\n";

		// some code to determine the best node types and their count
		// this will be done based on the number of queries in this specific time slot
		// there are some limits -- like the minimum number of nodes and the maximum number of nodes

		
		// get total estimated execution time
		float total_estimated_execution_time = 0;
		for(Query* q : _time_slot_queries[i]){
			// //cout<< "q->get_estimated_execution_time() +_+_+_+ : "<<q->get_estimated_execution_time()<<endl;
			// total_estimated_execution_time += q->get_estimated_execution_time();
			total_estimated_execution_time += _queries_estimated_time[q];
		}

		int queries_per_timeslot = _time_slot_queries[i].size();
		//cout<< "+++++++++++++++++++++++++++++++++++++ queries_per_timeslot: "<< queries_per_timeslot << " +++++++++++++++++++++++++++++++++++++"<<endl;
		
		float flt = total_estimated_execution_time;
		//cout<< flt<<endl;
		// int max_threads_count = ceil(total_estimated_execution_time / time_slot_duration_sec);
		int max_threads_count = ceil(total_estimated_execution_time);
		//cout<< "+++++++++++++++++++++++++++++++++++++ max_threads_count: "<< max_threads_count << " +++++++++++++++++++++++++++++++++++++"<<endl;

		// do your best

		int total_threads_count = 0;

		//cout<<"max_threads_count = "<<max_threads_count<<endl;
		// cout<<"total_estimated_execution_time = "<<total_estimated_execution_time<<endl;

		// while(total_estimated_execution_time > 0 && cluster_nodes_threads.size() > 0){
		
		// int nodes_count = cluster_nodes_count[cluster_nodes_cross_threads[0]];
		int nodes_count =  nodes_count_init;

		while(total_estimated_execution_time > 0 && nodes_count > 0){

			// std::vector<int>::iterator it = std::lower_bound (cluster_nodes_threads.begin(), cluster_nodes_threads.end(), max_threads_count);
			std::vector<int>::iterator it = std::upper_bound (cluster_nodes_threads.begin(), cluster_nodes_threads.end(), max_threads_count);

			int position;
			
			if(it == cluster_nodes_threads.end()){
				position = it - cluster_nodes_threads.begin() - 1;
				// cout<<"it == cluster_nodes_threads.end() --> "<< max_threads_count << " == " << position <<endl;
				// break;
			}
			else{
				position = it - cluster_nodes_threads.begin();
				// cout<<"it != cluster_nodes_threads.end() --> "<< max_threads_count << " == " << position <<endl;
			}

			// position = 0;

			//cout<< "3shan akon radet damery bs !!!!!!!!!!!!!!!!!!!!!!! : "<< position<<endl;


			
			// cluster_nodes_count[cluster_nodes_cross_threads[position]]--;

			// if(cluster_nodes_count[cluster_nodes_cross_threads[position]] < 0){
			// 	// cluster_nodes_threads.erase(it);
			// 	// continue;
			// 	break;
			// }

			

			// modify here???

			//cout<< "Check this >> " << cluster_nodes_cross_threads[position]->get_node_id() << endl;

			_nodes[cluster_nodes_cross_threads[position]->get_node_id()][i].insert(_nodes[cluster_nodes_cross_threads[position]->get_node_id()][i].end(), _time_slot_queries[i].begin(), _time_slot_queries[i].end());
			
			// for(int j=0;j<_time_slot_queries[i].size();j++){
			// 	//cout<< "push_backs ============================ " << push_backs++ <<endl;
			// 	_nodes[1][i].push_back(_time_slot_queries[i][j]);
			// }
		
			// //cout<< "And check this >> " << _nodes[cluster_nodes_cross_threads[position]->get_node_id()][i].front()->get_query_string() << endl;
			// //cout<< "And check this >> " << _nodes[cluster_nodes_cross_threads[position]->get_node_id()][i].back()->get_query_string() << endl;

			_slots[i].push_back(cluster_nodes_cross_threads[position]); // add to the current time slot a new node
			nodes_count--;

			total_threads_count += cluster_nodes_cross_threads[position]->get_max_runnable_threads();
			total_estimated_execution_time -= cluster_nodes_cross_threads[position]->get_max_runnable_threads();

			// total_estimated_execution_time -= cluster_nodes_cross_threads[position]->get_max_runnable_threads() * time_slot_duration_sec;
			
			
		}

		// cout << "total_estimated_execution_time : "<< total_estimated_execution_time<<endl;

		// if the queries esitmated time is not 0 yet, we will add them to the next time slot
		if(total_estimated_execution_time != 0){
			
			int threads_per_query = total_threads_count / _time_slot_queries[i].size();
			
			for(Query* q : _time_slot_queries[i]){
				// _queries_estimated_time[q] -= threads_per_query * time_slot_duration_sec;
				_queries_estimated_time[q] -= threads_per_query;
				
				if(_queries_estimated_time[q]>0){
					_time_slot_queries[i+1].push_back(q);
				}
			}
		}
	}

	//cout<< "_nodes[1].size() ----------------------->" << _nodes[1].size() <<endl;

	//cout<< "nodes size inside populate: " <<_nodes.size()<<endl;
	// nodes size inside populate: 0

}



// Performes crossover operation using to chromosomes and returns pointer to offspring
Schedule* Schedule::Crossover(const Schedule& parent2) const
{
//	cout<<"cross over tmmmmmmmmmm !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	// check probability of crossover operation
	if( rand() % 100 > _crossoverProbability )
		// no crossover, just copy first parent
		return new Schedule( *this, false );

	// new chromosome object, copy chromosome setup
	Schedule* n = new Schedule( *this, true );

	// number of classes
	int size = (int)_slots.size();

	vector<bool> cp( size );

	// determine crossover point (randomly)
	for( int i = _numberOfCrossoverPoints; i > 0; i-- )
	{
		while( 1 )
		{
			int p = rand() % size;
			if( !cp[ p ] )
			{
				cp[ p ] = true;
				break;
			}
		}
	}

	
	vector<int> it1 = _queries_init_time_slot;
	vector<int> it2 = parent2._queries_init_time_slot;

	// make new code by combining parent codes
	bool first = rand() % 2 == 0;
	for( int i = 0; i < _queries_init_time_slot.size(); i++ )
	{
		if( first )
		{
			// insert class from first parent into new chromosome's calss table
			n->_queries_init_time_slot[i] = it1[i];
			n->_time_slot_queries[_queries_init_time_slot[i]].push_back(config->GetQueries_values()[i]);
		}
		else
		{
			// insert class from second parent into new chromosome's calss table
			n->_queries_init_time_slot[i] = it2[i];	
			n->_time_slot_queries[_queries_init_time_slot[i]].push_back(config->GetQueries_values()[i]);
		}

		// crossover point
		if( cp[ i ] )
			// change soruce chromosome
			first = !first;
	}

	// _time_slot_queries

	n->Populate();
	//cout<< "after crossover see size of nodes : " << n->GetNodes().size() << endl;
	n->CalculateFitness();

	// return smart pointer to offspring
	return n;
	// return NULL;
}


// Performs mutation on chromosome
void Schedule::Mutation()
{
// 	// check probability of mutation operation
// 	if( rand() % 100 > _mutationProbability )
// 		return;

// 	// number of classes
// 	int numberOfClasses = (int)_nodes.size();
// 	// number of time-space slots
// 	int size = (int)_slots.size();

// 	// move selected number of classes at random position
// 	for( int i = _mutationSize; i > 0; i-- )
// 	{
// 		// select ranom chromosome for movement
// 		int mpos = rand() % numberOfClasses;
// 		int pos1 = 0;
// 		map<CourseClass*, int>::iterator it = _nodes.begin();
// 		for( ; mpos > 0; it++, mpos-- )
// 			;

// 		// current time-space slot used by class
// 		pos1 = ( *it ).second;

// 		CourseClass* cc1 = ( *it ).first;

// 		// determine position of class randomly
// //		int nr = config->GetNumberOfRooms();
// 		int dur = cc1->GetDuration();
// 		int day = rand() % DAYS_NUM;
// 		//int room = rand() % nr;
// 		int tim = rand() % ( DAY_HOURS + 1 - dur );
// 		int pos2 = day * DAY_HOURS +  DAY_HOURS + tim;

// 		// move all time-space slots
// 		for( int i = dur - 1; i >= 0; i-- )
// 		{
// 			// remove class hour from current time-space slot
// 			list<CourseClass*>& cl = _slots[ pos1 + i ];
// 			for( list<CourseClass*>::iterator it = cl.begin(); it != cl.end(); it++ )
// 			{
// 				if( *it == cc1 )
// 				{
// 					cl.erase( it );
// 					break;
// 				}
// 			}

// 			// move class hour to new time-space slot
// 			_slots.at( pos2 + i ).push_back( cc1 );
// 		}

// 		// change entry of class table to point to new time-space slots
// 		_nodes[ cc1 ] = pos2;
// 	}

// 	CalculateFitness();
}

// Calculates fitness value of chromosome
void Schedule::CalculateFitness()
{
	float score = 0;
	int issuance_assigment_difference_total = 0;

	for(map<int,vector<Query*>>::iterator time_slot_queries = _time_slot_queries.begin(); time_slot_queries != _time_slot_queries.end(); time_slot_queries++){
		
		int queries_count = (*time_slot_queries).second.size();

		if(queries_count > 2){
			_fitness = 0;
			break;
		}

	}

	for(int i=0; i<config->GetQueries_values().size();i++){
		issuance_assigment_difference_total += _queries_init_time_slot[i] - config->GetQueries_values().at(i)->get_issuance_time();
	}

	score = issuance_assigment_difference_total;

	
	// calculate fitess value based on score
	// _fitness = (float)(1/(float)score);
	
	_fitness = (float)(1/score);
	// _fitness = 2;
	
	//cout<<"_fitness : "<<_fitness<<endl;

	/*
	_fitness = (rand() % 100) / 100.0;

	float score = 0;

	_fitness = 1;

	//cout<<"test 1 passed\n"<<endl;

	// Schedule validity test:

	// 1) If queries scheduled on a node exceed the node's cpu capacity, the fitness of the chromosome is 0.


	// added code here +++
	std::set<pair<int,int>> query_list;

	
	// for each node
	for( map<int,map<int,list<Query*>>>::iterator node = _nodes.begin(); node != _nodes.end(); node++ ){

		//cout<<"inside node loop\n"<<endl;
		//cout<< (config->GetCluster_nodes()).size()<<endl;
		//cout<< "it worked!!"<<endl;

		for( ClusterNode* cn : config->GetCluster_nodes()){
			//cout<<"inside cluster node loop\n"<<endl;
			//cout<<"node id = "<<cn->get_node_id()<<endl;
		}

		
		//cout<<"hheerr: "<<node->first<<endl;

		int node_id = config->GetCluster_nodes().at(node->first)->get_node_id();
		int node_max_cpu_usage =  config->GetCluster_nodes().at(node->first)->get_node_max_cpu_usage();

		//cout<<"node_id: "<<node_id<<endl;
		//cout<<"node_max_cpu_usage: "<<node_max_cpu_usage<<endl;

		double total_queries_cpu_usage = 0;


		// for each time-space slot in node
		for( map<int,list<Query*>>::iterator time_slot_queries = node->second.begin(); time_slot_queries != node->second.end(); time_slot_queries++ ){

			//cout<<"inside time_slot_queries loop\n"<<endl;

			// if(node->second.at(time_slot_queries->first).size() > 11){
			// 	_fitness = 0;
			// 	return;	
			// }

			// if( time_slot_queries->second.size() > 2){
			// 	//cout<<"time_slot_queries->seccond.size() > 3\n"<<endl;
			// 	_fitness = 0;
			// 	return;
			// }

			int number_of_queries_per_time_slot = time_slot_queries->second.size();
			int max_runnable_threads = config->GetCluster_nodes().at(node->first)->get_max_runnable_threads();
			int number_of_threads_for_query_in_time_slot = max_runnable_threads / number_of_queries_per_time_slot;
			
			// for each query scheduled in this time-space slot on this node
			for( list<Query*>::iterator query = time_slot_queries->second.begin(); query != time_slot_queries->second.end(); query++ ){
				
				//cout<<"inside query loop\n"<<endl;

				total_queries_cpu_usage += (*query)->get_estimated_cpu_usage();

				// now each schedule is aware aware of the number of threads available for each query in each time slot
				// uncomment to continue working on this
				// queries_time_slot_threads_count[query][time_slot_queries->first] = number_of_threads_for_query_in_time_slot;
				
				// added code here +++

				// get query unique id
				int query_id = (*query)->get_query_id_original();
				int frag_id = (*query)->get_query_fragment_id();
				int issuance_time = (*query)->get_issuance_time();
				
				
				// query_list.insert({query_id,{frag_id,issuance_time}});
				query_list.insert(make_pair(query_id,frag_id));
			}

			if( total_queries_cpu_usage > node_max_cpu_usage ){
				//cout<<"test 2 failed\n"<<endl;
				_fitness = 0;
				return;
			}
		}
	}
	
	
	// // now calculate the total performance of the schedule
	// float total_latency = 0;
	// // for each query
	// for( map<Query*,map<int,int>>::iterator query_time_slot_threads_count = queries_time_slot_threads_count.begin(); query != queries_time_slot_threads_count.end(); query++ ){
	// 	query_time_slot_threads_count
	// }


	// i don;t know why this is never entered!!
	// added code here +++
	if(config->GetQueries_unique_ids() != query_list){

		for(auto it = config->GetQueries_unique_ids().begin(); it != config->GetQueries_unique_ids().end(); it++){
			//cout<<"query_id: "<<it->first<<" ";
			//cout<<"frag_id: "<<it->second<<"\n";
		}

		//cout<<"+++++++++++++++++++++++++++++++++++++++++++\n";

		for(auto it = query_list.begin(); it != query_list.end(); it++){
			//cout<<"query_id: "<<it->first<<" ";
			//cout<<"frag_id: "<<it->second<<"\n";
		}

		//cout<<"+++++++++++++++++++++++++++++++++++++++++++\n";
		

		//cout<<"config->GetQueries_unique_ids() != query_list\n"<<endl;
		_fitness = 0;
		return;
	}


	//cout<<"test 2 passed\n"<<endl;

	// Schedule scoring:

	// 1) count total time * cost per hour that each node will be up and running.

	float total_queries_cost = 0;

	// for each node
	for( map<int,map<int,list<Query*>>>::iterator node = _nodes.begin(); node != _nodes.end(); node++ ){

		float cost_per_hour;

		if( config->GetCluster_nodes().at(node->first)->get_node_type() == 0 ){
			cost_per_hour = 0.051; // for 4 GB
		}
		else{
			cost_per_hour = 0.24012; // for 4 GB
		}

		// for each time-space slot in node
		for( map<int,list<Query*>>::iterator time_slot_queries = node->second.begin(); time_slot_queries != node->second.end(); time_slot_queries++ ){
			
			// time_slot_queries->first

			total_queries_cost += cost_per_hour;

		}
	}

	score = total_queries_cost;

	score += _nodes.size() * 0.1;

	// calculate fitess value based on score
	_fitness = (float)(1/(float)score);// / (10);
	
	//cout<<"_fitness : "<<_fitness<<endl;

	// for( map<int,map<int,list<Query*>>>::iterator node = _nodes.begin(); node != _nodes.end(); node++ ){

	// 	//cout<< config->GetCluster_nodes().at(node->first)->get_node_type()<<endl;
	// 	//cout<< config->GetCluster_nodes().at(node->first)->get_node_id()<<endl;

	// 	// for each time-space slot in node
	// 	for( map<int,list<Query*>>::iterator time_slot_queries = node->second.begin(); time_slot_queries != node->second.end(); time_slot_queries++ ){
	// 		for( list<Query*>::iterator query = time_slot_queries->second.begin(); query != time_slot_queries->second.end(); query++ ){	
	// 			//cout<<(*query)->get_estimated_cpu_usage()<<" ";
	// 			//cout<<(*query)->get_query_string()<<" ";
	// 			//cout<<(*query)->get_issuance_time()<<" ";
	// 			//cout<<(*query)->get_estimated_execution_time()<<" ";
	// 			//cout<<(*query)->get_query_id_original()<<"\n";

	// 		}
	// 	}
	// }

	//cout<<"my fitness is 1\n";
	*/

}

// Returns reference to global instance of algorithm
// Algorithm& Algorithm::GetInstance(char* fileName)
Algorithm& Algorithm::GetInstance(vector<string> queriesStrings, vector<string> queriesFrequncies, int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms, vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect)
{
		
		// set seed for random generator
		srand(time(0));

		// make prototype of chromosomes

		//printf("before Schedule* prototype = new Schedule( 2, 2, 80, 3, fileName);\n");

		Schedule* prototype = new Schedule( 2, 2, 80, 3, "fileName", queriesStrings, queriesFrequncies, mxServers, mxLambda, mxBudget, boundTime, Realtime, EnableLambda, VMtypesVect, NewVms, CPUsNew, MoneyNew, queriesCostsVect);
		////printf("Algorithm::GetInstance(char* fileName) 1111111111\n");
		// make new global instance of algorithm using chromosome prototype

		// //cout<<"that's the protoype config: "<<prototype->config->GetQueries_keys().at(0)<<endl;

		//printf("before Algorithm* instance = new Algorithm( 100, 8, 5, prototype);\n");

		Algorithm* instance = new Algorithm( 100, 8, 5, prototype);
	
		//printf("Algorithm::GetInstance(char* fileName)\n");
	return *instance;
}

// Frees memory used by gloval instance
void Algorithm::FreeInstance()
{

	// free memory used by global instance if it exists
	if( _instance != NULL )
	{
		delete _instance->_prototype;
		delete _instance;
		_instance = NULL;
	}
}

// Initializes genetic algorithm
Algorithm::Algorithm(int numberOfChromosomes, int replaceByGeneration, int trackBest,
					 Schedule* prototype) : _replaceByGeneration(replaceByGeneration),
					 _currentBestSize(0),
					 _prototype(prototype),
					 _currentGeneration(0)
{
	// there should be at least 2 chromosomes in population
	if( numberOfChromosomes < 2 )
		numberOfChromosomes = 2;

	// and algorithm should track at least on of best chromosomes
	if( trackBest < 1 )
		trackBest = 1;

	if( _replaceByGeneration < 1 )
		_replaceByGeneration = 1;
	else if( _replaceByGeneration > numberOfChromosomes - trackBest )
		_replaceByGeneration = numberOfChromosomes - trackBest;

	// reserve space for population
	_chromosomes.resize( numberOfChromosomes );
	_bestFlags.resize( numberOfChromosomes );

	// reserve space for best chromosome group
	_bestChromosomes.resize( trackBest );

	// clear population
	for( int i = (int)_chromosomes.size() - 1; i >= 0; --i )
	{
		_chromosomes[ i ] = NULL;
		_bestFlags[ i ] = false;
	}


	// rakez ya bro
	// intialize an array of chromosome engines each one is responsible for creating one random chromosome in the initial population
	chromosome_creator_engines = new ChromosomeCreator*[numberOfChromosomes];

	int i = 0;
	for( vector<Schedule*>::iterator it = _chromosomes.begin(); it != _chromosomes.end(); ++it, ++i )
	{
		// chromosome_creator_engines[i] = new ChromosomeCreator(_prototype,*it);
		chromosome_creator_engines[i] = new ChromosomeCreator(_prototype);
	}
	
	////printf("end of Algorithm constructor\n");
}

// Frees used resources
Algorithm::~Algorithm()
{
	// clear population by deleting chromosomes 
	for( vector<Schedule*>::iterator it = _chromosomes.begin(); it != _chromosomes.end(); ++it )
	{
		if( *it )
			delete *it;
	}
}

void Algorithm::Start()
{
	//printf("begining of algorithm start()\n");
	if( !_prototype )
		return;

	ClearBest();

	
	// initialize new population with chromosomes randomly built using prototype


	for( vector<Schedule*>::iterator it = _chromosomes.begin(); it != _chromosomes.end(); ++it)
	{
		//printf("\ninside algorithm start for loop\n");
		// remove chromosome from previous execution
		if( *it ) delete *it;
		//printf("after delete *it\n");
	}

	// numberofchromosomes
	// replacebygeneration
	// rakez ya bro

	int init_pop_size = _chromosomes.size();
	// int init_pop_size = 1;
	// _chromosomes.resize(1);

	for ( int i = 0 ; i  < init_pop_size ; i++)
	{
		//cout<<"bos b2a <----- " << i <<"\n";
		std::thread * th = new std::thread(&ChromosomeCreator::start, chromosome_creator_engines[i]);
		chromosome_creator_engines[i]->setThread(th);
	}

	for(int i=0; i< init_pop_size; i++)
	{
		chromosome_creator_engines[i]->waitForRunToFinish();
	}

	// //cout<<"chromosome_creator_engines[0]->GetIt()->GetFitness() = "<<chromosome_creator_engines[0]->GetIt()->GetFitness()<<endl;

	//cout<<"chromosome_creator_engines[0]->GetIt()->GetFitness() = "<<chromosome_creator_engines[1]->GetIt()->GetFitness()<<endl;
	//cout<<"chromosome_creator_engines[0]->GetIt()->GetFitness() = "<<chromosome_creator_engines[2]->GetIt()->GetFitness()<<endl;
	//cout<<"chromosome_creator_engines[0]->GetIt()->GetFitness() = "<<chromosome_creator_engines[3]->GetIt()->GetFitness()<<endl;
	//cout<<"chromosome_creator_engines[0]->GetIt()->GetFitness() = "<<chromosome_creator_engines[4]->GetIt()->GetFitness()<<endl;
	//cout<<"chromosome_creator_engines[0]->GetIt()->GetFitness() = "<<chromosome_creator_engines[5]->GetIt()->GetFitness()<<endl;
	//cout<<"chromosome_creator_engines[0]->GetIt()->GetFitness() = "<<chromosome_creator_engines[6]->GetIt()->GetFitness()<<endl;

	int i = 0;
	for( vector<Schedule*>::iterator it = _chromosomes.begin(); it != _chromosomes.end(); ++it, ++i )
	{
		// //cout<< "mn gwa : " << *it GetFitness()<<endl;
		_chromosomes[i] = chromosome_creator_engines[i]->GetIt();
		//cout<<"bos keda ma3lesh = " <<_chromosomes[i]->GetNodes().size()<<endl;
		//cout<< "_chromosomes[i]->GetFitness() = " << _chromosomes[i]->GetFitness() <<endl;
		//printf("before add to best\n");
		AddToBest(i);
	}


	//cout<<"wow2\n";

	_currentGeneration = 0;



	// The process of getting the best chromosome is repeated until the best chromosome is found
	// or the number of generations is exceeded.
	// The best chromosome is stored in _bestChromosomes vector.

	float PreviousBestFitness;

	float _fitnessThreshold = 0.01;
	// float _fitnessThreshold = 0.0003;
	// float _fitnessThreshold = 0.00001;

	int repeated = 0;



	while( 1 )
	{
		Schedule* best = GetBestChromosome();

		// algorithm has reached criteria?
		if(abs(best->GetFitness() - PreviousBestFitness)  < _fitnessThreshold || _currentGeneration > 10)
		// if(_currentGeneration > 10)
		{
			if(repeated >= -1){
				//printf("\nalgorithm has reached criteria\n");
				break;
			}
			repeated++;

			// break;
		}
		PreviousBestFitness = best->GetFitness();

		// produce offepsing
		
		vector<Schedule*> offspring;
		offspring.resize(_replaceByGeneration);
		for( int j = 0; j < _replaceByGeneration; j++ )
		{
			// selects parent randomly
			Schedule* p1 = _chromosomes[ rand() % _chromosomes.size() ];
			Schedule* p2 = _chromosomes[ rand() % _chromosomes.size() ];

			offspring[ j ] = p1->Crossover( *p2 );
			// offspring[ j ]->Mutation();
		}

		// replace chromosomes of current operation with offspring
		for( int j = 0; j < _replaceByGeneration; j++ )
		{
			int ci;
			do
			{
				// select chromosome for replacement randomly
				ci = rand() % (int)_chromosomes.size();

				// protect best chromosomes from replacement
			} while( IsInBest( ci ) );

			// replace chromosomes
			delete _chromosomes[ ci ];
			_chromosomes[ ci ] = offspring[ j ];

			// try to add new chromosomes in best chromosome group
			AddToBest( ci );
		}
		_currentGeneration++;
		//cout<<"wooooooooooooooooooooowjhjhgjhgjhgjgj\n";
		//cout<<_currentGeneration<<" generation\n";
	}



}

// Returns pointer to best chromosomes in population
Schedule* Algorithm::GetBestChromosome() const
{
	return _chromosomes[ _bestChromosomes[ 0 ] ];
}

// Tries to add chromosomes in best chromosome group
void Algorithm::AddToBest(int chromosomeIndex)
{
	// don't add if new chromosome hasn't fitness big enough for best chromosome group
	// or it is already in the group?
	if( ( _currentBestSize == (int)_bestChromosomes.size() && 
		_chromosomes[ _bestChromosomes[ _currentBestSize - 1 ] ]->GetFitness() >= 
		_chromosomes[ chromosomeIndex ]->GetFitness() ) || _bestFlags[ chromosomeIndex ] )
		return;

	//cout<<"add to best no.1\n";

	// find place for new chromosome
	int i = _currentBestSize;
	for( ; i > 0; i-- )
	{
		// group is not full?
		if( i < (int)_bestChromosomes.size() )
		{
			// //cout<<"add to best no.1.1\n";
			// //cout<< _bestChromosomes[ i - 1 ]<<endl;
			// //cout<<"add to best no.1.1.1\n";
			// _chromosomes[ chromosomeIndex ]->GetFitness();
			// //cout<<"add to best no.1.1.2\n";
			// _chromosomes[ _bestChromosomes[ i - 1 ] ]->GetFitness();
			// //cout<<"add to best no.1.1.3\n";

			// position of new chromosomes is found?
			
			if( _chromosomes[ _bestChromosomes[ i - 1 ] ]->GetFitness() > 
				_chromosomes[ chromosomeIndex ]->GetFitness() ){
					//cout<<"add to best no.1.1.4\n";
					break;
				}

			//cout<<"add to best no.1.2\n";
			// move chromosomes to make room for new
			_bestChromosomes[ i ] = _bestChromosomes[ i - 1 ];

			//cout<<"add to best no.1.3\n";
		}
		else
			// group is full remove worst chromosomes in the group
			_bestFlags[ _bestChromosomes[ i - 1 ] ] = false;
	
		//cout<<"add to best no.2\n";
	
	}

	//cout<<"add to best no.3\n";

	// store chromosome in best chromosome group
	_bestChromosomes[ i ] = chromosomeIndex;
	_bestFlags[ chromosomeIndex ] = true;

	//cout<<"add to best no.4\n";

	// increase current size if it has not reached the limit yet
	if( _currentBestSize < (int)_bestChromosomes.size() )
		_currentBestSize++;
	
	//cout<<"add to best no.5\n";
}

// Returns TRUE if chromosome belongs to best chromosome group
bool Algorithm::IsInBest(int chromosomeIndex)
{
	return _bestFlags[ chromosomeIndex ];
}

// Clears best chromosome group
void Algorithm::ClearBest()
{
	for( int i = (int)_bestFlags.size() - 1; i >= 0; --i )
		_bestFlags[ i ] = false;

	_currentBestSize = 0;
}






void ChromosomeCreator::IntialPopulation()
{
    _it = _prototype->MakeNewFromPrototype();


	//cout<<"_it->GetFitness() = "<<_it->GetFitness()<<endl;
}


void ChromosomeCreator::CrossingOver()
{
}

void ChromosomeCreator::execute ()
{
    if ( _phase == intialPopulation) 
    {
        IntialPopulation();
        _phase = crossingOver;
    }
    else if(_phase == crossingOver) CrossingOver();
}

void ChromosomeCreator::start (ChromosomeCreator * me)
{
    me->execute();
}

void ChromosomeCreator::setThread(std::thread * p_th)
{
    _th = p_th;
}

void ChromosomeCreator::waitForRunToFinish()
{
    _th->join();
}


ChromosomeCreator::~ChromosomeCreator()
{
    delete(_th);
}

// ChromosomeCreator::ChromosomeCreator(Schedule* prototype, Schedule* it)
// {
//     this->_prototype = prototype;
//     this->_it = it;
//     _phase = intialPopulation;
// }

ChromosomeCreator::ChromosomeCreator(Schedule* prototype)
{
    this->_prototype = prototype;
    // this->_it = it;
    _phase = intialPopulation;
}

Schedule* ChromosomeCreator::GetIt()
{
	return _it;
}
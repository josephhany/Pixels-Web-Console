#include "Configuration.h"
#include "Query.h"
#include "ClusterNode.h"

void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

Configuration::Configuration(vector<string> queriesStrings, vector<string> queriesFrequncies, int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms, vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect){


	//cout<<"queriesCostsVect : ++++++++++++++++ll+++++++++00+++++++ll++++++++++++++++++++\n";
	for(int i=0; i<queriesCostsVect.size();i++){
		//cout<< queriesCostsVect[i]<<endl;
	}

	printf("inside Configuration::Configuration()\n");

	int id = 1;
	int parent_id = 1;


	for(int i=0;i<queriesStrings.size();i++){
		std::string s = queriesFrequncies[i];
		const char delim = ',';
		std::vector<std::string> out;
		tokenize(s, delim, out);
	
		for (auto &s: out) {
			//std::cout << s << std::endl;

			std::string ss = s;
			const char delim2 = ':';
			std::vector<std::string> out2;
			tokenize(ss, delim2, out2);

			int issuance_time = -1;
			int place = 1;

			for (auto &ss: out2) {
				//std::cout << ss << std::endl;

//				if(place==1) issuance_time += stoi(ss) * 60 * 60;
//				else if(place==2) issuance_time += stoi(ss) * 60;
//				else if(place==3) issuance_time += stoi(ss);

				if(place==1) issuance_time += stoi(ss) * 60;
                else if(place==2) issuance_time += stoi(ss);

				place++;
			}

			_queries_keys.push_back(id);
//			float execution_time = queriesCostsVect[i]/35000000;
            float execution_time = queriesCostsVect[i]/(35000000*60);
			_queries_values.push_back(new Query(execution_time, queriesStrings[i], id, issuance_time,parent_id));
			id++;

		}

		parent_id++;
	}

	
	/*
	for(int i=0;i<queriesStrings.size();i++){

		//cout<< "queriesFrequncies[i] :" <<queriesFrequncies[i]<<endl;
		std::string s = queriesFrequncies[i];
		std::string delimiter_char = ",";
		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter_char)) != std::string::npos) {
			token = s.substr(0, pos);
			std:://cout << "token : " << token << std::endl;

			int issuance_time = 0;

			
			std::string delimiter_char2 = ":";
			std::string token2;
			size_t pos2 = 0;
			int place = 1;
			while ((pos2 = token.find(delimiter_char2)) != std::string::npos) {
			
				token2 = token.substr(0, pos2);

				//cout<<"place: "<<place<<endl;
				//cout<<"token2: "<<token2<<endl;

				if(place==1) issuance_time += stoi(token2) * 60 * 60;
				else if(place==2) issuance_time += stoi(token2) * 60;
				else if(place==3) issuance_time += stoi(token2);
				place++;

				
				// //cout<<"token: "<<token<<endl;

				//cout<<"----------------> bos kam issuance time <---------------- "<< issuance_time<<endl;

				token.erase(0, pos2 + delimiter_char2.length());
			}

			_queries_keys.push_back(id);
			float execution_time = queriesCostsVect[i]/35000000;
			//cout<<"execution_time : "<<execution_time<<endl;
			_queries_values.push_back(new Query(execution_time, queriesStrings[i], id, issuance_time));
			
			id++;

			s.erase(0, pos + delimiter_char.length());
		}
		std:://cout << s << std::endl;
	}
	*/

	//cout << "dy el nahya ya m3alm: " << _queries_values.size() <<endl;


/*
	_queries_values.push_back(new Query(10, "SELECT * FROM nations2;", 2, 0));

	_queries_values.push_back(new Query(1, "SELECT * FROM nations3;", 3, 1));
	_queries_values.push_back(new Query(1, "SELECT * FROM nations4;", 4, 1));

	_queries_values.push_back(new Query(2, "SELECT * FROM nations5;", 5, 2));
	_queries_values.push_back(new Query(2, "SELECT * FROM nations6;", 6, 2));

	_queries_keys.push_back(1);
	_queries_keys.push_back(2);
	_queries_keys.push_back(3);
	_queries_keys.push_back(4);
	_queries_keys.push_back(5);
	_queries_keys.push_back(6);
*/

// Query(double execution_time, double storage_space, double cpu_usage, double network_time, string query_string, int query_id_original, double issuance_time, int query_fragment_id);
// Query(double execution_time, string query_string, int query_id_original, double issuance_time)

	// _queries_values.push_back(new Query(10, 1.0, 30, 1.0, "SELECT * FROM nations1;", 1, 0, 0));
	// _queries_values.push_back(new Query(10, 1.0, 30, 1.0, "SELECT * FROM nations2;", 2, 0, 0));
	
	// _queries_values.push_back(new Query(1, 1.0, 20, 1.0, "SELECT * FROM nations3;", 3, 1, 0));
	// _queries_values.push_back(new Query(1, 1.0, 20, 1.0, "SELECT * FROM nations4;", 4, 1, 0));

	// _queries_values.push_back(new Query(2, 1.0, 30, 1.0, "SELECT * FROM nations5;", 5, 2, 0));
	// _queries_values.push_back(new Query(2, 1.0, 50, 1.0, "SELECT * FROM nations6;", 6, 2, 0));

/*
	_queries_values.push_back(new Query(10, "SELECT * FROM nations1;", 1, 0));
	_queries_values.push_back(new Query(10, "SELECT * FROM nations2;", 2, 0));

	_queries_values.push_back(new Query(1, "SELECT * FROM nations3;", 3, 1));
	_queries_values.push_back(new Query(1, "SELECT * FROM nations4;", 4, 1));

	_queries_values.push_back(new Query(2, "SELECT * FROM nations5;", 5, 2));
	_queries_values.push_back(new Query(2, "SELECT * FROM nations6;", 6, 2));
*/

	printf("After push backs");

	// sort it with threads <----------------------

	int types_num = VMtypesVect.size();

	cout << "bos wenaby keda ::::::::::::::::::::::::::::::: "<< mxServers / types_num <<endl;
	
	for(int i=0; i<VMtypesVect.size();i++){
		cout<< "===================>" << VMtypesVect[i] << endl;
	}




  map<string, pair<int, float>> specs_map;
  specs_map["t2.nano"] = make_pair(1, 0.0058 / 60);
  specs_map["t2.small"] = make_pair(1, 0.023 / 60 );
  specs_map["t2.medium"] = make_pair(2, 0.0464 / 60 );
  specs_map["t2.large"] = make_pair(2, 0.055 / 60 );
  specs_map["t2.xlarge"] = make_pair(4, 0.1856 / 60 );
  specs_map["t2.2xlarge"] = make_pair(8, 0.3712 / 60 );
  specs_map["a1.2xlarge"] = make_pair(8, 0.204 / 60 );
  specs_map["a1.4xlarge"] = make_pair(16, 0.408 / 60 );
  specs_map["a1.metal"] = make_pair(16, 0.408 / 60 );
  specs_map["c4.2xlarge"] = make_pair(8, 0.398 / 60 );
  specs_map["c4.4xlarge"] = make_pair(16, 0.796 / 60 );
  specs_map["c5.2xlarge"] = make_pair(8, 0.34 / 60 );
  specs_map["c5.4xlarge"] = make_pair(16, 0.68 / 60 );

  map<string, pair<int, float>> specs_map_new;

  for(int i=0; i<NewVms.size();i++){
    specs_map_new[NewVms[i]] = make_pair(CPUsNew[i], MoneyNew[i] / 3600 );
  }
  
  for(int i=0; i<VMtypesVect.size();i++){

	int threads;
    float cost_per_sec;

	if (specs_map.count(VMtypesVect[i])){
	    threads = specs_map[VMtypesVect[i]].first;
        cost_per_sec = specs_map[VMtypesVect[i]].second;
	}
	else if(specs_map_new.count(VMtypesVect[i])){
	    threads = specs_map_new[VMtypesVect[i]].first;
        cost_per_sec = specs_map_new[VMtypesVect[i]].second;
	}

	_cluster_nodes.push_back(new ClusterNode(0, i, 100, threads,cost_per_sec));
	_cluster_nodes_threads.push_back(threads);
	_cluster_nodes_cross_threads.push_back(_cluster_nodes.at(i));
	_cluster_nodes_count[_cluster_nodes.at(i)] = mxServers / types_num;
  }



	/*
	// for(int i=0;i<300;i++){
		int i = 0;
		int threads = 20;
		float cost_per_sec = 7.08333333e-6;
		// int threads = 96;
		_cluster_nodes.push_back(new ClusterNode(0, i, 100, threads,cost_per_sec));
		_cluster_nodes_threads.push_back(threads);
		_cluster_nodes_cross_threads.push_back(_cluster_nodes.at(i));
		_cluster_nodes_count[_cluster_nodes.at(i)] = mxServers / types_num;
		// _cluster_nodes_count[_cluster_nodes.at(i)] = 300;
		// _cluster_nodes_count[_cluster_nodes.at(i)] = 1;
	// }

	int threads2 = 30;
	_cluster_nodes.push_back(new ClusterNode(0, 9, 100, threads2,7.08333333e-6));
	_cluster_nodes_threads.push_back(threads2);
	_cluster_nodes_cross_threads.push_back(_cluster_nodes.at(i+1));
	_cluster_nodes_count[_cluster_nodes.at(i+1)] =  mxServers / types_num;
	*/

	// _cluster_nodes.push_back(new ClusterNode(0, 1, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 2, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 3, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 4, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 5, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 6, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 7, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 8, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 9, 100, 96));
	// _cluster_nodes.push_back(new ClusterNode(0, 10, 100, 96));

	// // number of threads    nodes count     node itslef

	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(0));

	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(1));

	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(2));

	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(3));
	
	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(4));

	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(5));

	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(6));
	
	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(7));
	
	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(8));

	// _cluster_nodes_threads.push_back(96);
	// _cluster_nodes_cross_threads.push_back(_cluster_nodes.at(9));


	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(0)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(1)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(2)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(3)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(4)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(5)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(6)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(7)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(8)));
	// // _cluster_nodes_threads.insert(make_pair(2,_cluster_nodes.at(9)));


	// _cluster_nodes_count[_cluster_nodes.at(0)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(1)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(2)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(3)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(4)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(5)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(6)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(7)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(8)] = 96;
	// _cluster_nodes_count[_cluster_nodes.at(9)] = 96;


/*
	_cluster_nodes_count[_cluster_nodes.at(0)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(1)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(2)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(3)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(4)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(5)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(6)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(7)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(8)] = 1;
	_cluster_nodes_count[_cluster_nodes.at(9)] = 1;
*/


	// _queries_unique_ids.insert(make_pair(1,1));
	// _queries_unique_ids.insert(make_pair(1,2));
	// _queries_unique_ids.insert(make_pair(2,1));
	// _queries_unique_ids.insert(make_pair(2,2));
	// _queries_unique_ids.insert(make_pair(3,1));
	// _queries_unique_ids.insert(make_pair(3,2));


	// //cout<< "inside Configuration::Configuration() loop over _queries_unique_ids: " << endl;
	
	// for(auto it = _queries_unique_ids.begin(); it != _queries_unique_ids.end(); it++){
	// 		//cout<<"query_id: "<<it->first<<" ";
	// 		//cout<<"frag_id: "<<it->second<<"\n";
	// 	}

}
void Configuration::ParseFile(char* fileName)
{
	// //cout<<"hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii ma man\n";
	// fstream input( fileName );
	// string line;
	// string _class="#class";
	// while( input.is_open() && !input.eof() )
	// {
	// 	//getline( input, line );
	// 		input>>line;
	// 	//	//cout<<"inside the looooop\n";
	// 	//	//cout<<line<<endl;
	// 		//cout<<line<<endl;//<<":"<<"#class\n";
	// 	if( line==_class)
	// 	{
	// 		//cout<<"hooho entered\n";

	// 		string prof;
	// 		string cors;
	// 		string days;
	// 		double dur;
	// 		double times;
	// 		int count=0;
	// 		while(line!="#end")
	// 		{
	// 			//getline( input, line );
	// 			input>>line;
	// 			if( count == 0 ){
	// 				prof=line;
	// 				count++;
	// 			}
	// 			else if(count == 1){
	// 				cors = line;
	// 				count++;
	// 			}
	// 			else if( count == 2){
	// 				dur = atof( line.c_str() );
	// 				count++;
	// 			}
	// 			else if( count == 3){
	// 				days=line;
	// 				count++;
	// 			}
	// 			else if( count == 4){
	// 				times= atof(line.c_str());
	// 				count++;
	// 			}
	// 		}

	// 		CourseClass* c = new CourseClass( prof.c_str(), cors.c_str(), days.c_str(), dur, times);
	// 		if( c ){
	// 			printf("checking course name : %s\n",(char*)c->getCourseName());
	// 			bool found=false;
	// 			int index=0;
	// 			auto itr=_queries_keys.begin();
	// 			for(;itr!=_queries_keys.end();itr++){
	// 				if((char*)c->getCourseName()==*itr){
	// 					found=true;
	// 					break;
	// 				}
	// 				index++;
	// 			}
	// 			if(!found){
	// 				printf("checkingggggggggggggggggggggg\n");
	// 				_queries_keys.push_back((char*)c->getCourseName());
	// 				printf("size %d\n",(int)_queries_keys.size()-1);
	// 				_queries_values.resize(_queries_keys.size()+1);
	// 				_queries_values[_queries_keys.size()-1].push_back(c);
	// 			}
	// 			else{
	// 				printf("index: %d\n", index);
	// 				_queries_values[index].push_back(c);
	// 				//cout<<"mr bslam\n";
	// 			}
	// 		}
	// 	}

	// }

	// for(int i=0;i<_queries_keys.size();i++){
	// 	printf("%s : \n",_queries_keys[i]);
	// 	for(int j=0;i<_queries_values[i].size();j++){
	// 		printf("prof: %s\n",_queries_values[i][j]->GetProfessor());
	// 	}
	// }
	// input.close();
}
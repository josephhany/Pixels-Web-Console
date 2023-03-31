#include "Query.h"


// Query::Query(double execution_time, double storage_space, double cpu_usage, double network_time, string query_string, int query_id_original, double issuance_time, int query_fragment_id):
//                                                                         _estimated_execution_time(execution_time),
//                                                                         _estimated_storage_space(storage_space),
//                                                                         _estimated_cpu_usage(cpu_usage),
//                                                                         _estimated_network_time(network_time),
//                                                                         _query_string(query_string),
//                                                                         _query_fragment_id(query_fragment_id),
//                                                                         _query_id_original(query_id_original),
//                                                                         _issuance_time(issuance_time),
//                                                                         _assignment_time(-1)
// {

// }

Query::Query(float execution_time, string query_string, int query_id_original, double issuance_time, int parent_id):
                                                                        _estimated_execution_time(execution_time),
                                                                        _query_string(query_string),
                                                                        _query_id_original(query_id_original),
                                                                        _issuance_time(issuance_time),
                                                                        _parent_id(parent_id)
{

}

// Frees used memory
Query::~Query() { }
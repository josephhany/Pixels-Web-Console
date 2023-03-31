// #include <string>
#include <iostream>
#include "Configuration.h"
#include "Schedule.h"

// std::string helloUser( std::string name );
// Configuration helloUser( std::string name, int *A, int size);
// Configuration helloUser( std::string name, vector<int32_t> vect, int size);
// Configuration helloUser( std::string name, vector<string> vect1, vector<string> vect2);
// Schedule* helloUser( std::string name, vector<string> vect1, vector<string> vect2);
// Schedule* helloUser(vector<string> vect1, vector<string> vect2);
// Schedule* helloUser(vector<string> vect1, vector<string> vect2, int mxServers, int mxLambda, int boundTime, bool Realtime, bool EnableLambda);
Schedule* helloUser(vector<string> queriesStrings, vector<string> queriesFrequncies, int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms, vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect);
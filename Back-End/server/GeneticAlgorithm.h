#include<string>
#include <iostream>
#include "Schedule.h"

// std::string GeneticAlgorithm();
// int* GeneticAlgorithm();
// Schedule* GeneticAlgorithm();
Schedule* GeneticAlgorithm(vector<string> queriesStrings, vector<string> queriesFrequncies, int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms, vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect);
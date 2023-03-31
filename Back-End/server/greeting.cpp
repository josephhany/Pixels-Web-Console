#include <iostream>
#include <string>
#include "greeting.h"
#include "GeneticAlgorithm.h"
#include "Configuration.h"
#include "Schedule.h"

// std::string helloUser( std::string name ) {
// Configuration helloUser( std::string name, int *A, int size) {
// Configuration helloUser( std::string name, vector<int32_t> vect, int size) {
// Configuration helloUser( std::string name, vector<string> vect1, vector<string> vect2) {
// Schedule* helloUser( std::string name, vector<string> vect1, vector<string> vect2) {
Schedule* helloUser(vector<string> queriesStrings, vector<string> queriesFrequncies, int mxServers, int mxLambda, int mxBudget, int boundTime, bool Realtime, bool EnableLambda, vector<string> VMtypesVect, vector<string> NewVms, vector<int> CPUsNew, vector<float> MoneyNew, vector<double> queriesCostsVect) {

//   return "Hello " + name + "!";
//   GeneticAlgorithm();

    //cout<<"from helloUser\n";

    //cout<<"dol el strings\n";
    for (int i = 0; i < queriesStrings.size(); ++i) {
      // //cout<<A[i] <<endl;
      //cout<<queriesStrings[i] <<endl;
    }

    //cout<<"dol el frequencies\n";
    for (int i = 0; i < queriesFrequncies.size(); ++i) {
      // //cout<<A[i] <<endl;
      //cout<<queriesFrequncies[i] <<endl;
    }

    //cout<<"------------------> dol el queriesCostsVect <--------------\n";
    for (int i = 0; i < queriesCostsVect.size(); ++i) {
      // //cout<<A[i] <<endl;
      //cout<<queriesCostsVect[i] <<endl;
    }
    
    //cout<<"a7la bound time: "<< boundTime<< endl;

    // Configuration config = Configuration();

    // return config;

//   return "tmam";
    return GeneticAlgorithm(queriesStrings,queriesFrequncies,mxServers,mxLambda,mxBudget,boundTime,Realtime,EnableLambda,VMtypesVect,NewVms,CPUsNew,MoneyNew,queriesCostsVect);
    // return GeneticAlgorithm();
    // return new Schedule( 2, 2, 80, 3, "fileName");
}
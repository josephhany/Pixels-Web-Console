#include <napi.h>
#include <string>
#include "greeting.h"
#include <iostream>
// #include "Configuration.h"
#include "Schedule.h"
#include <vector>

// native C++ function that is assigned to `greetHello` property on `exports` object
Napi::Object greetHello(const Napi::CallbackInfo& info) {

    cout<<"--> I am inside greetHello <--"<<endl;
    
    Napi::Env env = info.Env();

    Napi::Array queriesStrings = static_cast<Napi::Value>(info[0]).As<Napi::Array>();
    Napi::Array queriesFrequncies = static_cast<Napi::Value>(info[1]).As<Napi::Array>();
    int mxServers = info[2].ToNumber().Int32Value();
    int mxLambda = info[3].ToNumber().Int32Value();
    int mxBudget = info[4].ToNumber().Int32Value();
    int boundTime = info[5].ToNumber().Int32Value();
    bool Realtime = info[6].ToBoolean();
    bool EnableLambda = info[7].ToBoolean();
    Napi::Array VMtypes = static_cast<Napi::Value>(info[8]).As<Napi::Array>();

    Napi::Array NewVms = static_cast<Napi::Value>(info[9]).As<Napi::Array>();
    Napi::Array CPUsNew = static_cast<Napi::Value>(info[10]).As<Napi::Array>();
    Napi::Array MoneyNew = static_cast<Napi::Value>(info[11]).As<Napi::Array>();

    Napi::Array queriesCosts = static_cast<Napi::Value>(info[12]).As<Napi::Array>();

    int length = queriesStrings.Length();
    int length2 = queriesFrequncies.Length();
    int length3 = VMtypes.Length();
    int length4 = NewVms.Length();
    int length5 = CPUsNew.Length();
    int length6 = MoneyNew.Length();
    int length7 = queriesCosts.Length();

    vector<std::string> queriesStringsVect;
    vector<std::string> queriesFrequnciesVect;
    vector<std::string> VMtypesVect;
    vector<std::string> NewVmsVect;
    vector<int> CPUsNewVect;
    vector<float> MoneyNewVect;
    vector<double> queriesCostsVect;

    unsigned int i;

    for (i = 0; i < length; i++) queriesStringsVect.push_back( static_cast<Napi::Value>(queriesStrings[i]).As<Napi::String>().ToString() );
    for (i = 0; i < length2; i++) queriesFrequnciesVect.push_back( static_cast<Napi::Value>(queriesFrequncies[i]).As<Napi::String>().ToString() );
    for (i = 0; i < length2; i++) queriesFrequnciesVect.push_back( static_cast<Napi::Value>(queriesFrequncies[i]).As<Napi::String>().ToString() );
    for (i = 0; i < length3; i++) VMtypesVect.push_back( static_cast<Napi::Value>(VMtypes[i]).As<Napi::String>().ToString() );

    for (i = 0; i < length4; i++) NewVmsVect.push_back( static_cast<Napi::Value>(NewVms[i]).As<Napi::String>().ToString() );
    for (i = 0; i < length5; i++) CPUsNewVect.push_back( static_cast<Napi::Value>(CPUsNew[i]).As<Napi::Number>().ToNumber().Int32Value());
    for (i = 0; i < length6; i++) MoneyNewVect.push_back( static_cast<Napi::Value>(MoneyNew[i]).As<Napi::Number>().ToNumber().FloatValue());


    for (i = 0; i < length7; i++) queriesCostsVect.push_back( static_cast<Napi::Value>(queriesCosts[i]).As<Napi::Number>().Int64Value());

    Schedule* result = helloUser(
        queriesStringsVect,
        queriesFrequnciesVect,
        mxServers,
        mxLambda,
        mxBudget,
        boundTime,
        Realtime,
        EnableLambda,
        VMtypesVect,
        NewVmsVect,
        CPUsNewVect,
        MoneyNewVect,
        queriesCostsVect
        );

    cout<<"result->GetFitness() = "<<result->GetFitness()<<endl;

    Napi::Object ret = Napi::Object::New(env);

    // ret.Set("my_number", Napi::Number::New(env, result.GetQueries_keys().size())); // ezay hena momkn ab3at object feh arrays of arrays

    // int fooo [5] = { 16, 2, 77, 40, 12071 };
    // ret.Set("queries_per_sec", Napi::Array::New(env, fooo));


// last commented working just fine
/*
    std::vector<int64_t> dims;
    dims.push_back(5);
    dims.push_back(9);
    dims.push_back(1);
    size_t dimsCount = 3;
    auto dimsArray = Napi::Array::New(env, dimsCount);
    for (uint32_t i = 0; i < dimsCount; i++) {
        dimsArray[i] = dims[i];
    }

    ret.Set("queries_per_sec", dimsArray);
*/



    std::vector<int> dims = result->GetNumQueriesPerSec();
    size_t dimsCount = dims.size();

    auto dimsArray = Napi::Array::New(env, dimsCount);
    for (uint32_t i = 0; i < dimsCount; i++) {
        dimsArray[i] = dims[i];
    }

    ret.Set("queries_per_sec", dimsArray);



    std::vector<string> daytim = result->GetDayTimeMins();
    size_t daytimsize = daytim.size();

    auto daytimArray = Napi::Array::New(env, daytimsize);
    for (uint32_t i = 0; i < daytimsize; i++) {
        daytimArray[i] = daytim[i];
    }

    ret.Set("daytim", daytimArray);


    ret.Set("OverallCost", result->GetOverallCost());


    std::vector<int> QueriesInitTimeSlot = result->GetQueriesInitTimeSlot();
    size_t QueriesInitTimeSlotsize = QueriesInitTimeSlot.size();

    auto QueriesInitTimeSlotArray = Napi::Array::New(env, QueriesInitTimeSlotsize);
    for (uint32_t i = 0; i < QueriesInitTimeSlotsize; i++) {
        QueriesInitTimeSlotArray[i] = QueriesInitTimeSlot[i];
    }


    std::vector<int> QueriesEndTimeSlot = result->GetQueriesEndTimeSlot();
    size_t QueriesEndTimeSlotsize = QueriesEndTimeSlot.size();

    auto QueriesEndTimeSlotArray = Napi::Array::New(env, QueriesEndTimeSlotsize);
    for (uint32_t i = 0; i < QueriesEndTimeSlotsize; i++) {
        QueriesEndTimeSlotArray[i] = QueriesEndTimeSlot[i];
    }



    std::vector<int> ParentsIds = result->GetParentsIds();
    size_t ParentsIdssize = ParentsIds.size();

    auto ParentsIdsArray = Napi::Array::New(env, ParentsIdssize);
    for (uint32_t i = 0; i < ParentsIdssize; i++) {
        ParentsIdsArray[i] = ParentsIds[i];
    }


    ret.Set("InitTimeSlot", QueriesInitTimeSlotArray);
    ret.Set("QueriesEndTimeSlot", QueriesEndTimeSlotArray);
    ret.Set("ParentsIds", ParentsIdsArray);


    std::vector<float> CostPerSec = result->GetCostPerSec();
    size_t CostPerSecCount = CostPerSec.size();

    auto CostPerSecArray = Napi::Array::New(env, CostPerSecCount);
    for (uint32_t i = 0; i < CostPerSecCount; i++) {
        CostPerSecArray[i] = CostPerSec[i];
    }

    ret.Set("CostPerSec", CostPerSecArray);





    // ret.Set("queries_per_sec", Napi::Array::New(env, result.GetQueriesPerSec()));
    // ret.Set("nodes_per_sec", Napi::Array::New(env, result.GetNodesPerSec()));
    // ret.Set("money_per_sec", Napi::Array::New(env, result.GetMoneyPerSec()));

    // return new `Napi::String` value
    return ret;
}

// callback method when module is registered with Node.js
Napi::Object Init(Napi::Env env, Napi::Object exports) {

    // set a key on `exports` object
    exports.Set(
        Napi::String::New(env, "greetHello"), // property name => "greetHello"
        Napi::Function::New(env, greetHello) // property value => `greetHello` function
    );

    // return `exports` object (always)
    return exports;
}

// register `greet` module which calls `Init` method
NODE_API_MODULE(greet, Init)
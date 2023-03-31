const express = require("express");
const cors = require('cors');

const PORT = process.env.PORT || 3001;

const app = express();

const corsOptions ={
   origin:'*',
   credentials:true,            //access-control-allow-credentials:true
   optionSuccessStatus:200,
}

let queriesStrings;

// const QueryFactory = (execution_time, storage_space, cpu_usage, network_time, query_string, query_id_original, issuance_time, query_fragment_id) => {
//     return {
//         execution_time: execution_time,
//         storage_space: storage_space,
//         cpu_usage: cpu_usage,
//         network_time: network_time,
//         query_string: query_string,
//         query_id_original: query_id_original,
//         issuance_time: issuance_time,
//         query_fragment_id: query_fragment_id,
//     };
// };

// const fs = require('fs');
// const util = require('util');
// const pipeline = util.promisify(require('stream').pipeline);

/*
// Global variables
// that is okay
var map_for_cols_sizes = {};

// https://stackoverflow.com/questions/25905465/how-to-create-map-with-key-and-a-list-of-values-in-javascript

// map_for_cols_sizes
var tbl1 = {};
var tbl2 = {};

tbl1["col1"] = ["val"];
tbl1["col2"] = ["val"];

tbl2["col1"] = ["val"];
tbl2["col2"] = ["val"];

map_for_cols_sizes["tbl1"] = tbl1;
map_for_cols_sizes["tbl2"] = tbl2;
*/



// console.log(map_for_cols_sizes);
// map_for_cols_sizes["country2"] = ["state1", "state2"];

const columns_sizes = new Map([
  ["l_quantity", "5.03GB"],
  ["l_extendedprice", "5.03GB"],
  ["l_discount", "5.03GB"],
  ["l_tax", "5.03GB"],
  ["l_returnflag", "3.08GB"],
  ["l_linestatus", "2.98GB"],
  ["l_shipdate", "2.79GB"],
  ["n_nationkey", "225B"],
  ["n_name", "361B"],
  ["n_regionkey", "225B"],
  ["r_regionkey", "45B"],
  ["r_name", "85B"],
  ["ps_partkey", "686.65MB"],
  ["ps_suppkey" , "686.65MB"],
  ["ps_supplycost" , "686.65MB"],
  ["s_suppkey" , "8.58MB"],
  ["s_name" , "21.97MB"],
  ["s_address" , "32.45MB"],
  ["s_nationkey" , "8.58MB"],
  ["s_phone" , "21.96MB"],
  ["s_acctbal" , "8.58MB"],
  ["s_comment" , "68.95MB"],
  ["p_partkey" , "171.66MB"],
  ["p_mfgr" , "106.40MB"],
  ["p_type" , "114.60MB"],
  ["p_size" , "95.37MB"],
  ["o_orderkey" , "1.26GB"],
  ["o_custkey" , "1.26GB"],
  ["o_orderdate" , "715.26MB"],
  ["o_shippriority" , "715.26MB"],
  ["l_orderkey" , "5.03GB"],
  ["c_custkey" , "128.75MB"],
  ["c_mktsegment" , "79.80MB"],
  ["o_orderpriority" , "798.02MB"],
  ["l_commitdate" , "2.79GB"],
  ["l_receiptdate" , "2.79GB"],
  ["l_suppkey" , "5.03GB"],
  ["c_nationkey" , "128.75MB"],
  ["l_partkey" , "5.03GB"],
  ["p_name" , "797.64MB"],
  ["c_name" , "329.5MB"],
  ["c_address" , "486.70MB"],
  ["c_phone" , "329.50MB"],
  ["c_acctbal" , "128.75MB"],
  ["c_comment" , "1.15GB"],
  ["ps_availqty" , "381.47MB"],
  ["l_shipmode" , "3.10GB"],
  ["o_comment" , "8.36GB"],
  ["p_brand" , "114.53MB"],
  ["p_container" , "114.53MB"],
  ["o_totalprice" , "1.26GB"],
  ["l_shipinstruct" , "3.02GB"],
  ["o_orderstatus" , "796.07MB"]
  ]);

var presto = require('@dalongrong/trino-client');
// var presto = require('trino-client');
// var presto = require('presto-client');
// DriverManager
var client = new presto.Client({user: 'Joseph'});

client.host = '3.129.204.126';
client.port = '8080';
client.catalog = 'pixels';
client.schema = 'tpch';
client.source = 'nodejs-client';


/*
var java = require('java');
var javaLangSystem = java.import('java.lang.System');
var Properties = java.import('java.util.Properties');
var Connection = java.import('java.sql.Connection');
var Statement = java.import('java.sql.Statement');
var ResultSet = java.import('java.sql.ResultSet');
var DriverManager = java.import('java.sql.DriverManager');

// var mySumTest = java.import('SumOfNumbers');
// var result= java.callStaticMethodSync("SumOfNumbers", "sum", 2, 5)
// console.log(result)

// java.import("java.util.ArrayList"); // see NOTE below


javaLangSystem.out.printlnSync('I love gfg!');

// let java= require('java');
// java.classpath.push('./server/test.jar');
// java.classpath.push('D:\EPFL Summer Research\react-node-app-backend\server\test.jar');
// java.classpath.push( ".");
// java.classpath.push(path.resolve('D:/EPFL Summer Research/react-node-app-backend/server/test.jar'));
// path.resolve('../');
const path = require('node:path');
// java.classpath.push(path.resolve('D:/EPFL Summer Research/react-node-app-backend/server/test.jar'));
// java.classpath.push(path.basename('D:\\EPFL Summer Research\\react-node-app-backend\\server\\test.jar'));
console.log( path.resolve("./server/trino-jdbc-352.jar"));
// java.classpath.push(path.resolve("./server/Test.class"));
java.classpath.push(path.resolve("./server/trino-jdbc-352.jar"));



// var javaLangSystem = java.import('java.lang.System');
// javaLangSystem.out.printlnSync('Hello World');
java.import("Test");
// let test = java.import("Test");

// test.main(null);


// // new stuff
// var properties = java.newInstanceSync('java.util.Properties');
// properties.setProperty("user", "test");

// var conn = java.newInstanceSync('java.sql.Connection');
// conn = DriverManager.getConnection("jdbc:trino://3.129.204.126:8080/pixels/tpch", properties);
// // const stmt = new Statement();
// const stmt = Statement.conn.createStatement();
// // const rs = new ResultSet();
// const rs = ResultSet.stmt.executeQuery("select * from nation");

const properties = Object.create(Properties,{user: { value: 'test' }});

console.log(properties);

const rs = DriverManager.getConnection("jdbc:trino://3.129.204.126:8080/pixels/tpch",properties);



// .createStatement().executeQuery("select * from nation");
console.log(rs);
// // .createStatement().executeQuery("select * from nation");



// while (rs.next()) {
//   console.log(rs.getString(1));
// }
// java.classpath.push("trino-jdbc-393.jar");


// var db = require('node-any-jdbc');
*/

/*
var JDBC = require('jdbc');
var jinst = require('jdbc/lib/jinst');
// var jinst = require('../lib/jinst');
var asyncjs = require('async');

if (!jinst.isJvmCreated()) {
  console.log("hwa msh ma3mol");
    jinst.addOption("-Xrs");
    jinst.setupClasspath(['./trino-jdbc-393.jar']);
    // jinst.setupClasspath(['D:/EPFL Summer Research/react-node-app-backend/trino-jdbc-393.jar']);
    // jinst.setupClasspath(['./trino-jdbc-393.jar']);
    // jinst.setupClasspath(['../drivers/trino-jdbc-352.jar']);
    // jinst.setupClasspath(['./C:/Users/Joseph/.m2/repository/io/trino/trino-jdbc/352']);
    
    // jinst.setupClasspath(['./D:/EPFL Summer Research/react-node-app-backend/server/trino-jdbc-393.jar']);
    // jinst.setupClasspath(['/react-node-app-backend/server/trino-jdbc-393.jar']);
    // jinst.setupClasspath(['./C:/Users/Joseph/.m2/repository/io/trino/trino-jdbc/352']);
    console.log("lesa msh ma3mol");
  }

  
  var config = {
    
    // SparkSQL configuration to your server
    // url: 'jdbc:trino://3.129.204.126:8080/pixels/tpch',
    // url: 'jdbc:trino://3.129.204.126:8080',
    url: 'jdbc:trino://3.129.204.126:8080/pixels/tpch',
    // drivername: 'io.trino.jdbc.TrinoDriver',

    // drivername: 'com.ddtek.jdbc.sforce.SForceDriver',
    // drivername: 'com.facebook.presto.jdbc.PrestoDriver',
    // drivername: 'io.trino.jdbc.TrinoDriver',
    // drivername: 'io.trino.jdbc',
    // drivername: 'trino-jdbc-352',
    setupClasspath: './D:/EPFL Summer Research/react-node-app-backend/server/trino-jdbc-393.jar' ,
    user: 'test',
    password: 'password',
    properties: {}
  };

  var trino = new JDBC(config);

  //initialize
  trino.initialize(function(err) {
    if (err) {
      console.log("error", err);
    }
  });

  // trino.execute("select * from nation");

  // trino.execute(config, "select * from nation", function(results){
  //   console.log(results);
  // });
*/



// const delay = time => new Promise(res=>setTimeout(res,time));

// Trial #-1
/*
var Connection = require('tedious').Connection;  
    var config = {  
        server: 'jdbc:trino://3.129.204.126:8080/pixels/tpch',  //update me
        authentication: {
            type: 'default',
            options: {
                userName: 'your_username', //update me
                password: 'your_password'  //update me
            }
        },
        // options: {
        //     // If you are on Microsoft Azure, you need encryption:
        //     encrypt: true,
        //     database: 'your_database'  //update me
        // }
    };  
    var connection = new Connection(config);  
    connection.on('connect', function(err) {  
        // If no error, then good to proceed.
        console.log("Connected");  
        
    });
    
    connection.connect();

    var Request = require('tedious').Request;  
    var TYPES = require('tedious').TYPES;  
  

    let request = new Request("SELECT * From nation;", function(err) {  
    if (err) {  
        console.log(err);}  
    });  
    var result = "";


    request.on('row', function(columns) {
        columns.forEach(function(column) {
          if (column.value === null) {  
            console.log('NULL');  
          } else {  
            result+= column.value + " ";  
          }  
        });  
        console.log(result);  
        result ="";
    });  

    request.on('done', function(rowCount, more) {  
    console.log(rowCount + ' rows returned');  
    });  
    
    // Close the connection after the final event emitted by the request, after the callback passes
    request.on("requestCompleted", function (rowCount, more) {
        connection.close();
    });
    connection.execSql(request);
*/

// Trial #0

// const { spawn } = require('node:child_process');
// const ls = spawn('java', ['SumOfNumbers.class', '2 3 4']);

// // console.log(ls);

// ls.stdout.on('data', (data) => {
//   console.log(`stdout: ${data}`);
// });

// Trial #1

// const child_process = require('child_process');  

// var workerProcess = child_process.spawn(
//   'java', ['SumOfNumbers.class', '2 3 4']
// );

// workerProcess.stdout.on('data', function (data) {  
//   console.log('stdout: ' + data);  
// });  


// trial #2
// var child = require('child_process').exec(
//   'java', ['SumOfNumbers', '2 3 4']
// );

// child.stdout.on('data', function(data) {
//   console.log(data.toString());
// });


// child.on("error", function (error) {
//   console.log("The error is " + error);
// });

// child.on("close", function (code, signal) {
//   console.log(signal);
//   console.log("Our Java Snippet has finished with an exit code of " + code);
// });

// Trial #3
// child.stderr.on("data", function (data) {
//   console.log(data.toString());
// });


// const { spawn } = require('child_process');
// const spawn = require("child_process").spawn('java');
// const spawnn = spawn('java');
// const spawn = require("child_process").exec("SumOfNumbers.java");

/*
const spawn = require("child_process").spawn;


function sumOfNumbers(numbers) {
  let args = [];
  args.push("SumOfNumbers"); // Making our Java filename as the first argument to be picked by the java command

  // Push the numbers as the other arguments
  numbers.forEach((element) => {
    args.push(element);
  });

  // Starting our worker
  console.log("Starting our worker to execute our Java Snippet");


  let worker = spawn("java", args);


  worker.stdout.on("data", function (data) {
    console.log("The sum as processed by our Java Snippet is : " + data);
  });

  worker.on("error", function (error) {
    console.log("The error is " + error);
  });

  // worker.on("close", function (code, signal) {
  //   console.log("Our Java Snippet has finished with an exit code of " + code);
  // });
}

sumOfNumbers([1, 2, 9]); // Driver

*/

function estimateExecutionTime(query_string){
  console.log("kosom 7yaty");
  console.log(query_string);
}

function recurssion(){

  
  
}

async function estimateExecutionTime2(query_string) {

  console.log(query_string);
  
  // try {

    
    // const statement = await client.execute({
    //   query:query_string,
    //   success: function(error, stats){console.log({message:"success", stats:stats});}}
    //   );

    const statement = await client.execute({
                                      query: query_string,
                                      state:   function(error, query_id, stats){ 
                                        console.log({message:"status changed", id:query_id, stats:stats}); 
                                      },
                                      columns: function(error, data){ 
                                        console.log({resultColumns: data}); 
                                        datum = "tmam";
                                      },
                                      success: function(error, stats){
                                        console.log({message:"success", stats:stats});
                                      },
                                      error:   function(error){
                                        console.log({message:"error", error:error});
                                      },
                                      data:   function(error, data, columns, stats){ 
                                        datum = data;
                                        console.log(data); 
                                        return data;
                                      },
                                    });

    // statement.on('state_change',(currentState,stats)=>{
    //     console.log(`state changed to ${currentState} for query ${statement.query_id}`);
    //     console.log(stats);
    // });

    // return await pipeline(statement);

    // return statement.then(data=>{
    //   console.log(data);
    //   return data;
    // }).catch(err=>{
    //   console.log(err);
    //   return err;
    // });
    

    // let datum;
    

    
    // var response = await client.execute({
    //                                 query: query_string,
    //                                 state:   function(error, query_id, stats){
    //                                   console.log({message:"status changed", id:query_id, stats:stats});
    //                                 },
    //                                 columns: function(error, data){
    //                                   console.log({resultColumns: data});
    //                                   datum = await data;
    //                                 },
    //                                 success: function(error, stats){
    //                                   console.log({message:"success", stats:stats});
    //                                 },
    //                                 error:   function(error){
    //                                   console.log({message:"error", error:error});
    //                                 },
    //                                 data:    function(error, data, columns, stats){
    //                                   datum = data;
    //                                   console.log(data); 
    //                                   return data;
    //                                 },
    //                               });

    // console.log(datum);
    // return datam;

    // const writeStream = fs.createWriteStream('/path/to/file.csv');
    // statement.on('state_change',(currentState,stats)=>{
    //     console.log(`state changed to ${currentState} for query ${statement.query_id}`);
    //     console.log(stats);
    // });
    // await pipeline(statement,writeStream);
    // return statement;
    // console.log("datum: ",statement.columns.data);
    // return datum;
    
  // } catch(err) {
  //   // catches errors both in fetch and response.json
  //   console.log(err);
  //   console.log("error");
  //   // alert(err);
  // }

  // execute the query in the client and then return the column data

  // const statement = await client.execute({query: query_string});
  // console.log(statement.response);

  // return statement.response;



  // let datam;
  // var res = await client.execute({
  //   // query:   'EXPLAIN SELECT l_extendedprice FROM lineitem',
  //   query: query_string,
  //   state:   function(error, query_id, stats){ 
  //     // console.log({message:"status changed", id:query_id, stats:stats}); 
  //   },
  //   columns: function(error, data){ 
  //     // console.log({resultColumns: data}); 
  //     datam = data;
  //     // return data;
  //   },
  //   data:    function(error, data, columns, stats){ 
  //     // console.log(data); 
  //   },
  //   success: function(error, stats){
  //     // console.log({message:"success", stats:stats});
  //     // return "tmm";
  //   },
  //   error:   function(error){
  //     // console.log({message:"error", error:error});
  //   }
  // });

  // // await delay(10000);

  // // return datam;

  // return new Promise((resolve) => {
  //   setTimeout(() => resolve(res), 8000)
  //   });

}

app.use(cors(corsOptions)) // Use this after the variable declaration

app.use(express.json());


// import native addon
const addonGreet = require('bindings')('greet');

// expose module API
// exports.hello = addonGreet.greetHello;

// console.log( addonGreet.hello( 'World' ) );
// console.log( "addonGreet.greetHello : " , addonGreet.greetHello( 'World','3ady') );


// I want to send to c++
// 1) array of queries
// 2) array of estimated execution time
// 3) array of arrays of frequencies

/*
console.log("change is applied don't worry");
let arr = [1,2,3,4,5,9,8];

console.log( "addonGreet.greetHello : " , addonGreet.greetHello( 'World','3ady', arr) );
*/



app.get("/api", cors(), (req, res) => {

    // var newMap = new Map(existingMap)


    // //  vector<list<ClusterNode*>> _slots;
    // vector<int> _queries_init_time_slot; // when each query will be eventually assigned
    // map<int,vector<Query*>> _time_slot_queries; // the queries that are being processed at each time slot
    // map<Query*,int> _queries_estimated_time; // the estimated time of completion for each query
    // map<int,map<int,list<Query*>>> _nodes; // node id mapped to the its time slots and the queries being processed
    // float total_cost; // the total cost of this schedule
    // float cost_per_hour; // the average cost of the schedule per hour

    let total_cost = 2130.8;
    let max_budget = 4000;
    let percentage = (total_cost / max_budget) * 100;
    let budget_percentage = "-".concat(percentage,"%");
    let average_cost_per_hour = (total_cost / 24).toFixed(2);
    let costs_array = [12,15,2,7,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,0];
    let average_queries_per_hour = 7;
    let max_number_of_queries_per_hour = 15;
    let avg_vms_per_hour = 36
    let max_number_of_vms_per_hour = 72;
    let avg_λs_per_hour = 0;
    let max_number_of_λs_per_hour = 0;

    console.log(budget_percentage);
    // res.write(total_cost);
    // res.end();

    res.send(JSON.stringify({
      "status": 200, 
      "error": null, 
      "total_cost": total_cost, 
      "budget_percentage": budget_percentage, 
      "average_cost_per_hour": average_cost_per_hour, 
      "costs_array": costs_array,
      "average_queries_per_hour": average_queries_per_hour,
      "max_number_of_queries_per_hour": max_number_of_queries_per_hour,
      "avg_vms_per_hour": avg_vms_per_hour,
      "max_number_of_vms_per_hour": max_number_of_vms_per_hour,
      "avg_λs_per_hour": avg_λs_per_hour,
      "max_number_of_λs_per_hour": max_number_of_λs_per_hour,
    }));

    // res.json({ message: "ana baba3bas fel server" });

});


function recurse(filtered_data_array, filtered_data_map, time_array, index) {
  
  if(index === filtered_data_array.length) {
    console.log(time_array);

    // 1000000
    // for(var i=0; i<queriesStrings.length;i++){
    //   for(var j=0; j<queriesStrings.length;j++){

    //   }
    // }



    return;
  }
  else {
    // now perform the time calculations

    return;

    let query = "explain select "+ filtered_data_array[index] + " from " + filtered_data_map[filtered_data_array[index]];

    client.execute({
    
      query: query,
      success: function(error, stats){},
      data:    function(error, data, columns, stats){
        
        let estimate = data[0][0].split("[SOURCE]")[1].split("Estimates: {rows:")[1].split("(")[1].split(")")[0];
        console.log("estimate: ", estimate);
        time_array.push(estimate);
        index++;

        recurse(filtered_data_array, filtered_data_map, time_array, index);
      }
    });
  }
}

//add new user
app.post('/store-data', async (req, res) => {

  // let data = req.body;
  // console.log('test');
  let save = req.body.data;
  console.log(req.body.data);

  console.log("mx servers from the backend : ", req.body.data.mxServers);

  let mxServers = req.body.data.mxServers;
  let mxLambda = req.body.data.mxLambda;
  let mxBudget = req.body.data.mxBudget;
  let boundTime = req.body.data.boundTime;
  let Realtime = req.body.data.Realtime;
  let EnableLambda = req.body.data.EnableLambda;
  let VMtypes = req.body.data.VMtypes;
  let NewVms = req.body.data.NewVms;
  let CPUsNew = req.body.data.CPUsNew;
  let MoneyNew = req.body.data.MoneyNew;
  let queriesCosts = [];

  console.log("mx servers from the backend : ", mxServers);
  console.log(mxLambda);
  console.log(mxBudget);
  console.log(boundTime);
  console.log(Realtime);
  console.log(EnableLambda);
  console.log(VMtypes);
  

  // here we need to parse the data to be in the follwing format
  // ------------------------------------------ data structure for all queries = q1_string, q2_string, ..., qn_string
  queriesStrings = req.body.data.Queries.split("\n");
  console.log(queriesStrings); // one done
    // ------------------------------------------

  queriesFrequncies = req.body.data.Frequencies.split("\n");
  console.log("Frequencies of queries: ", queriesFrequncies);

  
  // console.log( "addonGreet.greetHello : " , addonGreet.greetHello( 'World','3ady', queriesStrings, queriesFrequncies) );

  console.log(">-----> VMtypes <-----< : ", VMtypes);

  

  queriesStrings.forEach(function (item, index) {
    let query_cost = 0;
    columns_sizes.forEach((value, key) => {
      if( item.includes(key) ){
        if(value.includes('GB')){
          let val = parseFloat(value.split('GB')[0]) * 1000000000;
          query_cost = query_cost + val;
        } else if (value.includes('MB')) {
          let val = parseFloat(value.split('MB')[0]) * 1000;
          query_cost = query_cost + val;
        }
        else{
          let val = parseFloat(value.split('B')[0]);
          query_cost = query_cost + val;
        }
      }
    });
    queriesCosts.push(query_cost);
  });

  console.log("this is the queries estimates: ", queriesCosts);
  
  

  // --> this one working
  // console.log(
  //   "addonGreet.greetHello : ===================================================" , 
  //   addonGreet.greetHello( 
  //     queriesStrings, 
  //     queriesFrequncies, 
  //     mxServers,
  //     mxLambda,
  //     mxBudget,
  //     boundTime,
  //     Realtime,
  //     EnableLambda,
  //     VMtypes,
  //     queriesCosts
  //     )
  //   );


  // ------------------------------------------ data structure for all queries time estimation = q1_time, q2_time, ..., qn_time

  // algorithm reciepe 

  // to get the time estimation for each query we will:
  // 1- gather all the table names that were called in each query
  // 2- gather all column names that were called in each query
  // 3- relate the column names with the table names i.e. tbl1 --> col1, col2, .. , tbl2 --> col1, col2, ..
  // 4- reference this 2d-array (not really global bec. col names will be get only inside request) to the recursive function that will
  //   a) take a column by column and calculate its size while saving it on the stack
  //   b) have a base case that will have the main logic of time estimation
  //  in which we will have the following logic:
  //      1) iterate over all the queries (global array) and see its read columns and sum their values
  //      2) assign this value to the query's time estimation in a local array
  //      3) send this whole array along with the queries array to --> addonGreet.greetHello(queries, time_estimation)
  //      4) get the result from the addonGreet.greetHello function and send it as a return for the res for the frontend

  // ------------------------------------------


  // get all the tables of all the queries
  let tbls = [];

  for(var i=0; i<queriesStrings.length; i++){
    let tbls_in_query = queriesStrings[i].split(" where ")[0].split(" from ")[1].replace('/n', '').replace(/ /g,'').split(",");
    tbls = [...tbls, ...tbls_in_query];
  }

  // get all the columns of all the tables

  const tbls_datesWrappedInQuotes = tbls.map(tbl => `'${tbl}'`);
  const tbls_withCommasInBetween = tbls_datesWrappedInQuotes.join(',');
  
  let query = "select column_name, table_name from INFORMATION_SCHEMA.COLUMNS where TABLE_NAME IN ("  + tbls_withCommasInBetween + ")";

  console.log(query);

  client.execute({
    
    query: query,
    success: function(error, stats){},
    data:    function(error, data, columns, stats){

      console.log(data);

      // now filter this data to get only the columns found in the queries
      let filtered_data = new Set();
      let filtered_data_map = {};

      queriesStrings.forEach(queryString => {
        data.forEach(row => {
          if( queryString.includes(row[0]) ){
            filtered_data.add(row[0]);
            filtered_data_map[row[0]]=row[1];
          }
        });
      });

      console.log(filtered_data);
      console.log(filtered_data_map);

      let filtered_data_array = Array.from(filtered_data);

      console.log("filtered data: ", filtered_data_array);

      let time_array = [];

      recurse(filtered_data_array, filtered_data_map , time_array, 0);

      /*
      // var estimate = estimateExecutionTime(data);

      let selectedCols = [];

      // console.log("query --> ",query);

      // console.log(query.includes('p_partkey'));

      data.forEach(colm => {
        // console.log("col =", colm[0]);
        if( queriesStrings[0].includes(colm[0]) ){
          selectedCols.push(colm[0]);
        }
      });

      const selCols_withCommasInBetween = selectedCols.join(', ');
      const tbls_withCommasInBetween2 = tbls.join(', ');

      // console.log("tbls_withCommasInBetween2 = ",tbls_withCommasInBetween2);

      let q3 = "explain select " +  selCols_withCommasInBetween + " from " + tbls_withCommasInBetween2 ;

      

      console.log(q3);
      // console.log("selected cols ---> ",selectedCols);

      client.execute({
        query: q3,
        success: function(error, stats){},
        data:    function(error, data, columns, stats){
          // var estimate = estimateExecutionTime(data);;
          console.log("result : ", data[0][0]);
          const lastWord = data[0].split(' ').pop();
          console.log("last word = ", lastWord);
        },
      });

      */

    },
  });



  
  /*

  // --------------------- data structure for all queries issaunce time slots = q1_issuance_time {1,2,3,...}, q2_issuance_time {1,2,3,...}, ..., qn_issuance_time {1,2,3,...}
  const queriesFrequencies = req.body.data.Frequencies.split("\n");
  // iterate over the queriesStrings and queriesFrequencies and create a new object for each query
  let queriesFrequencies2 = [];

  // "select column_name from INFORMATION_SCHEMA.COLUMNS where TABLE_NAME=\'lineitem\'"
  // select column_name from INFORMATION_SCHEMA.COLUMNS where TABLE_NAME='lineitem'

  queriesFrequencies.forEach(frequency => {
    queriesFrequencies2.push(frequency.split(","));
  } );

  console.log(queriesFrequencies2);

  */

  var obj  = addonGreet.greetHello(
    queriesStrings,
    queriesFrequncies,
    mxServers,
    mxLambda,
    mxBudget,
    boundTime,
    Realtime,
    EnableLambda,
    VMtypes,
    NewVms,
    CPUsNew,
    MoneyNew,
    queriesCosts
    );

  console.log("obj.queries_per_sec : ",obj.queries_per_sec);
  


  res.send(JSON.stringify(
    {
      "status": 200, 
      "error": null, 
      "response": obj.queries_per_sec, 
      "daytim": obj.daytim,
      "OverallCost": obj.OverallCost,
      "InitTimeSlot": obj.InitTimeSlot,
      "QueriesEndTimeSlot": obj.QueriesEndTimeSlot,
      "ParentsIds": obj.ParentsIds,
      "CostPerSec" : obj.CostPerSec
    }));
  

  // res.send(JSON.stringify({
  //   "status": 200, 
  //   "error": null, 
  //   "costs_array": costs_array
  // }));
  
});

app.listen(PORT, () => {
  console.log(`Server listening on ${PORT}`);
});
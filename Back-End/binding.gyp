{
  "targets": [
    {
      "target_name": "greet",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./server/greeting.cpp",
        "./server/ClusterNode.cpp",
        "./server/Configuration.cpp",
        "./server/GeneticAlgorithm.cpp",
        "./server/Query.cpp",
        "./server/Schedule.cpp",
        "./server/index.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
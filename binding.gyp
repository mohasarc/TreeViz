{
    "targets": [{
        "target_name": "logic",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "logicSrc/main.cpp",
            "logicSrc/logic-classes/2_3_Search_Tree/Implementation_Files/Tree23.cpp",
            "logicSrc/logic-classes/2_3_Search_Tree/Implementation_Files/Tree23Wrapper.cpp",
            "logicSrc/logic-classes/2_3_Search_Tree/Implementation_Files/TriNode.cpp",
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}
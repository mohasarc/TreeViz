{
    "targets": [{
        "target_name": "AVLTree",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "logicSrc/logic-classes/AVL_Tree/Implementation_Files/AVLTree.cpp",
            "logicSrc/logic-classes/AVL_Tree/Implementation_Files/AVLTreeWrapper.cpp",
            "logicSrc/logic-classes/AVL_Tree/Implementation_Files/TreeNode.cpp",
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },
    {
        "target_name": "Tree23",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "logicSrc/logic-classes/2_3_Search_Tree/Implementation_Files/Tree23.cpp",
            "logicSrc/logic-classes/2_3_Search_Tree/Implementation_Files/Tree23Wrapper.cpp",
            "logicSrc/logic-classes/2_3_Search_Tree/Implementation_Files/TriNode.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },{
        "target_name": "BSTree",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "logicSrc/logic-classes/Binary_Search_Tree/Implementation_Files/BSTree.cpp",
            "logicSrc/logic-classes/Binary_Search_Tree/Implementation_Files/BSTWrapper.cpp",
            "logicSrc/logic-classes/Binary_Search_Tree/Implementation_Files/TreeNode.cpp",
            "logicSrc/3rd-Party/deelx.h"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },
    {
        "target_name": "BTree",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "logicSrc/logic-classes/B_Tree/Implementation_Files/BNode.cpp",
            "logicSrc/logic-classes/B_Tree/Implementation_Files/BTree.cpp",
            "logicSrc/logic-classes/B_Tree/Implementation_Files/BTreeWrapper.cpp",
            "logicSrc/3rd-Party/deelx.h"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },{
        "target_name": "Deelx",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "logicSrc/3rd-Party/deelx.h",
            "logicSrc/3rd-Party/deelxWrapper.cpp",
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
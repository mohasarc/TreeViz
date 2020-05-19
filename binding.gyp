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
            "logicSrc/logic-classes/Binary_Search_Tree/Implementation_Files/TreeNode.cpp"
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
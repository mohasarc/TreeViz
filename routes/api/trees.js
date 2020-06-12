// const logic = require('../../build/Release/logic.node');
const {AVLTree} = require('../../build/Release/AVLTree.node');
const {Tree23} = require('../../build/Release/Tree23.node');
const {BSTree} = require('../../build/Release/BSTree.node');
const {BTree} = require('../../build/Release/BTree.node');
const session = require('express-session');
const express = require('express');
const router = express.Router();

router.use(session({
    secret : 'Key773_-+3Vvx||d121dddvsCZXW@$%^&$#fsghdsb',
    resave : false,
    saveUninitialized : false,
}));

router.post('/performOperation', (req, res) => {
    var operationType = req.operation.type;
    var value = req.operation.value;
    var treeContent = req.treeContent;
    var targetTreeInfo = req.targetTreeInfo;

    // Create the tree
    switch (targetTreeInfo.type) {
        case 'binary-tree':
            req.session.theTree = new BSTree();
        break;
        
        case 'B-tree':
            req.session.theTree = new BTree(targetTreeInfo.preferences.order);
        break;
    
        default:
        break;
    }

    // Perform the operation
    switch (operationType) {
        case 'insert':
            if (treeContent.treeSequence != '')
                req.session.theTree.insertSequence(treeContent.treeSequence);
            else{
                req.session.theTree.constructFromTreeString(treeContent.treeString);
                res.session.theTree.setSequence(req.session.theTree.generateInorderSequence());
            }

            req.session.theTree.insert(value);
        break;

        case 'remove':
        
        break;

        case 'build':
        
        break;

        case 'buildRandom':
    
        break;

        default:
            break;
    }

    // Send back the final product
    var responseObj = {
        type : targetTreeInfo.type,
        treeString : req.session.theTree.toTreeString(),
        treeSequence : req.session.theTree.getSequence(),
        preferences : targetTreeInfo.preferences,
    }

    res.send(responseObj);
});

// @route  GET api/trees/getTree
// @desc   get the current tree
// @access public
router.get('/getTree', (req, res) => {
    res.send({'tree-string': '{5}({4}{6})', 'id': 5});
});

// @route  POST api/trees/sendTree
// @desc   send a tree
// @access public
router.post('/sendTree', (req, res) => {
    // Creating a new tree object & initializing it from tree string recieved
    req.session.treeBinary = new BSTree();
    req.session.tree23 = new Tree23();

    // construct the tree
    console.log('not crashed yet');
    console.log(req.body);
    if (req.body.treeString){
        req.session.treeBinary.constructFromTreeString(req.body.treeString);
        // req.session.tree23.constructFromTreeString(req.body.treeString);
    } else {
        req.session.treeBinary.constructFromTreeString('');
        req.session.tree23.constructFromTreeString('');
    }

    // Send back the tree just recieved after adding it to json formatted object
    treeObj = {'id': 0, 'treeStrings': {}};
    treeObj.id = 0; // will be fixed later
    // treeObj.treeStrings['23'] = req.session.tree23.toTreeString();
    treeObj.treeStrings['binary'] = req.session.treeBinary.toTreeString();

    res.send(treeObj);
});

// @route  POST api/trees/addValue
// @desc   sends one value to be added to tree
// @access public
router.post('/addValue', (req, res) => {
    // Creating a new tree object & initializing it from tree string recieved
    req.session.treeBinary = new BSTree();
    req.session.tree23 = new Tree23();

    // construct the tree
    console.log('not crashed yet');
    console.log(req.body);
    if (req.body.treeStrings){
        req.session.treeBinary.constructFromTreeString(req.body.treeStrings['binary']);
        req.session.tree23.constructFromTreeString(req.body.treeStrings['23']);
    } else {
        req.session.treeBinary.constructFromTreeString('');
        req.session.tree23.constructFromTreeString('');
    }

    // insert the value into the tree
    req.session.treeBinary.insert(parseInt( req.body.value ));
    req.session.tree23.insert(parseInt( req.body.value ));

    // Send back the tree just recieved after adding it to json formatted object
    treeObj = {'id': 0, 'treeStrings': {}};
    treeObj.id = 0; // will be fixed later
    treeObj.treeStrings['23'] = req.session.tree23.toTreeString();
    treeObj.treeStrings['binary'] = req.session.treeBinary.toTreeString();

    res.send(treeObj);
});

// @route  POST api/trees/buildRandomTree
// @desc   Creates a random tree
// @access public
router.post('/buildRandomTree', (req, res) => {
    // get values from request
    var minRange = parseInt(req.body.range.min);
    var maxRange = parseInt(req.body.range.max);
    var numNodes = parseInt(req.body.numNodes);

    // Creating a new tree object & initializing it from tree string recieved
    req.session.treeBinary = new BSTree();
    req.session.tree23 = new Tree23();
    req.session.bTree = new BTree(3);

    // construct the tree
    req.session.treeBinary.constructFromTreeString('');
    req.session.tree23.constructFromTreeString('');
    req.session.bTree.constructFromTreeString('');
    // Generate ranfom numbers list
    var numbers = [];
    for (var i = minRange; i <= maxRange; i++){
        numbers.push(i);
    }

    function shuffle(o) {
        for(var j, x, i = o.length; i; j = parseInt(Math.random() * i), x = o[--i], o[i] = o[j], o[j] = x);
        return o;
    };
    
    var random = shuffle(numbers);

    // insert random values into the trees
    for (let i = 0; i < numNodes && i < random.length; i++){
        // let randomValue = Math.random() * (maxRange - minRange) + minRange;
        req.session.treeBinary.insert(parseInt( random[i]));
        req.session.tree23.insert(parseInt( random[i] ));
        req.session.bTree.insert(parseInt(random[i]));
    }


    // Send back the tree just recieved after adding it to json formatted object
    treeObj = { 'id': 0, 
                'treeStrings': {},
                'treeSequence': '',
                };
    treeObj.id = 0; // will be fixed later
    // treeObj.treeStrings['23'] = req.session.tree23.toTreeString();
    treeObj.treeStrings['23'] = req.session.bTree.toTreeString();
    treeObj.treeStrings['binary'] = req.session.treeBinary.toTreeString();

    res.send(treeObj);
});

// Exporting router
module.exports = router;
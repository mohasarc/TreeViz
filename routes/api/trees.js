// const logic = require('../../build/Release/logic.node');
const {AVLTree} = require('../../build/Release/AVLTree.node');
const {Tree23} = require('../../build/Release/Tree23.node');
const {BSTree} = require('../../build/Release/BSTree.node');
const session = require('express-session');
const express = require('express');
const router = express.Router();

router.use(session({
    secret : 'Key773_-+3Vvx||d121dddvsCZXW@$%^&$#fsghdsb',
    resave : false,
    saveUninitialized : false,
}));

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
    switch (req.body.treeChoice) {
        case 'binary':
            req.session.tree = new BSTree();
            req.session.tree.constructFromTreeString(req.body.treeString);
            console.log('in binary tree');
        break;

        case '23':
            req.session.tree = new Tree23();
            req.session.tree.constructFromTreeString(req.body.treeString);
            console.log("23 tree");
        break;
        case '234':
        break;
        case 'avl':
            req.session.tree = new AVLTree();
            req.session.tree.constructFromTreeString(req.body.treeString);
            console.log("avl tree");
        break;
        case 'redblack':
        break;

        default:
        break;
    }

    // Send back the tree just recieved after adding it to json formatted object
    treeObj = {'id': 0, 'treeString': ''};
    treeObj.id = 0; // will be fixed later
    treeObj.treeString = req.session.tree.toTreeString();
    res.send(treeObj);
});

// @route  POST api/trees/addValue
// @desc   sends one value to be added to tree
// @access public
router.post('/addValue', (req, res) => {
    // Creating a new tree object & initializing it from tree string recieved
    switch (req.body.treeChoice) {
        case 'binary':
            req.session.tree = new BSTree();
            console.log('in binary tree');
        break;

        case '23':
            req.session.tree = new Tree23();
            console.log("23 tree");
        break;
        case '234':
        break;
        case 'avl':
            req.session.tree = new AVLTree();
            console.log("avl tree");
        break;
        case 'redblack':
        break;

        default:
        break;
    }

    console.log('not crashed yet');
    req.session.tree.constructFromTreeString(req.body.treeString);
    console.log('crashed');
    console.log('was converted');
    // insert the value into the tree
    req.session.tree.insert(parseInt( req.body.value ));

    // Send back the tree just recieved after adding it to json formatted object
    treeObj = {'id': 0, 'treeString': ''};
    treeObj.id = 0; // will be fixed later
    treeObj.treeString = req.session.tree.toTreeString();
    console.log('ther tree string', treeObj.treeString);
    res.send(treeObj);
});

// Exporting router
module.exports = router;
const logic = require('../../build/Release/logic.node');
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
    req.session.tree = new logic.Tree23();
    req.session.tree.constructFromTreeString(req.body.treeString);

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
    req.session.tree = new logic.Tree23();
    req.session.tree.constructFromTreeString(req.body.treeString);
    // insert the value into the tree
    req.session.tree.insert(parseInt( req.body.value ));

    // Send back the tree just recieved after adding it to json formatted object
    treeObj = {'id': 0, 'treeString': ''};
    treeObj.id = 0; // will be fixed later
    treeObj.treeString = req.session.tree.toTreeString();
    res.send(treeObj);
});


// Exporting logic
module.exports = logic;
module.exports = router;
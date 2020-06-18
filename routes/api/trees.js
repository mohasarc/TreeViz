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
    var operationType = req.body.operation.type;
    var operationPreferences = req.body.operation.preferences;
    var value = req.body.operation.value;
    var treeContent = req.body.treeContent;
    var targetTreeInfo = req.body.targetTreeInfo;
    console.log(req.body);

    // Create the tree
    switch (targetTreeInfo.type.value) {
        case 'BST':
            req.session.theTree = new BSTree();
            console.log(targetTreeInfo.preferences.replaceWithPredecessor);
            req.session.theTree.setPrioritizePredecessor(targetTreeInfo.preferences.replaceWithPredecessor);
        break;
        
        case '234':
        case 'B-T':
        case '23T':
            req.session.theTree = new BTree(targetTreeInfo.preferences.order);
            req.session.theTree.setPropagateS(targetTreeInfo.preferences.propagateSmallerValue);
            req.session.theTree.setPrioritizeInorderPredecessor(targetTreeInfo.preferences.prioritizeInorderPredecessor);
            req.session.theTree.setPrioritizeRotateLeft(targetTreeInfo.preferences.prioritizeRotateLeft);
        break;

        case 'AVL':
        break;

        case 'RBT':
        break;
        
        default:
        break;
    }

    // Populate tree
    if (treeContent.treeSequence != ''){
        req.session.theTree.insertSequence(treeContent.treeSequence);
        req.session.useSequence = true;
    }
    else{
        // If tree string has only one node with one value create tree + generate tree sequence

        // If tree string has more than one node or a node with more than one value, DO NOT
        // generate tree sequence and do not send back any tree sequence
        var re = new RegExp("^{\\d+}$");
        console.log('the test', re.test(treeContent.treeString));
        if (re.test(treeContent.treeString)){
            req.session.theTree.constructFromTreeString(treeContent.treeString);
            var treeSequence = req.session.theTree.generateInorderSequence();
            req.session.theTree.setSequence(treeSequence);
            req.session.useSequence = true;
        } else {
            req.session.theTree.constructFromTreeString(treeContent.treeString);
            req.session.useSequence = false;
        }
    }

    // Perform the operation
    switch (operationType) {
        case 'insert':
            req.session.theTree.clearSteps();
            req.session.theTree.insert(parseInt(value));
        break;

        case 'remove':
            req.session.theTree.clearSteps();
            req.session.theTree.remove(parseInt(value), 's');
        break;

        // case 'build':

        // break;

        case 'buildRandom':
            req.session.useSequence = true;

            // utility function
            function shuffle(o) {
                for(var j, x, i = o.length; i; j = parseInt(Math.random() * i), x = o[--i], o[i] = o[j], o[j] = x);
                return o;
            };

            // get values from request
            var minRange = parseInt(operationPreferences.range.min);
            var maxRange = parseInt(operationPreferences.range.max);
            var numNodes = parseInt(operationPreferences.numNodes);

            // Generate random numbers list
            var numbers = [];
            for (var i = minRange; i <= maxRange; i++){
                numbers.push(i);
            }
            
            // shuffle the list
            var random = shuffle(numbers);

            // insert random values into the tree
            for (let i = 0; i < numNodes && i < random.length; i++)
                req.session.theTree.insert(parseInt( random[i]));
        break;

        default:
            break;
    }

    // Send back the final product
    // Special naming for B-trees
    var treeName = targetTreeInfo.type.name;
    if (targetTreeInfo.type.value == 'B-T'){
        if (targetTreeInfo.preferences.order > 4)
            treeName = targetTreeInfo.preferences.order + targetTreeInfo.type.name.substr(1);
        else{
            if (targetTreeInfo.preferences.order == 3)
                treeName = '2-3 tree'
            if (targetTreeInfo.preferences.order == 4)
                treeName = '2-3-4 tree'
        }
    }

    steps = [];
    // Retrieving steps
    for (var i = 0; i < req.session.theTree.getStepsNo(); i++){
        steps.push({
            'text' : req.session.theTree.getStepText(i),
            'treeStr' : req.session.theTree.getStepTreeStr(i),
            'note' : req.session.theTree.getStepNote(i),
        });
    }

    // Add final result as a last step
    steps.push({
        'text' : '',
        'treeStr' : req.session.theTree.toTreeString(),
        'note' : '',
    });

    var responseObj = {
        'type' : treeName,
        'treeString' : req.session.theTree.toTreeString(),
        'treeSequence' : req.session.useSequence ? req.session.theTree.getSequence() : '',
        'preferences' : targetTreeInfo.preferences,
        'steps' : steps
    }

    res.send(responseObj);
});

// Exporting router
module.exports = router;
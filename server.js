const express = require('express');
const logic = require('./build/Release/logic.node');
// const mongoose = require('mongoose');
// const bodyParser = require('body-parser');

const trees = require('./routes/api/trees');
const app = express();

// body-parser middleware
// app.use(bodyParser.json);

// TEST
var tree = new logic.Tree23();
tree.insert(5);
tree.insert(2);
tree.insert(7);
app.get('/', (req, res) => {
    res.send(tree.toTreeString());
})

// redirecting api requests to items
app.use('/api/trees', trees);


// Exporting logic
module.exports = logic;

// Port configurations
const port = process.env.PORT || 2000;
app.listen(port, () => {
    console.log(`server started at ${port}`);
});
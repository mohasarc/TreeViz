const express = require('express');
// const mongoose = require('mongoose');
// const bodyParser = require('body-parser');

const trees = require('./routes/api/trees');
const app = express();

// body-parser middleware
// app.use(bodyParser.json);

// redirecting api requests to items
app.use('/api/trees', trees);

// Port configurations
const port = process.env.PORT || 2000;
app.listen(port, () => {
    console.log(`server started at ${port}`);
});
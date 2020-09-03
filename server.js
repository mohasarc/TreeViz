const express = require('express');
// const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const path = require('path');
const trees = require('./routes/api/trees');
const robots = require("express-robots-txt");
const sitemap = require("./sitemap");
const app = express();
// body-parser middleware
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// redirecting api requests to items
app.use('/api/trees', trees);

app.use(sitemap);

// Adding robots.txt
app.use(
    robots({
      UserAgent: "*",
      Disallow: "",
      Sitemap: "http://www.treeviz.xyz/sitemap.xml"
    })
);

// serve static assets if in production
if (process.env.NODE_ENV === 'production'){
    // Set static folder
    app.use(express.static('client/build'));

    app.get('*', (req, res) => {
        res.sendFile(path.resolve(__dirname, 'client', 'build', 'index.html'));
    });
}

// Port configurations
const port = process.env.PORT || 2000;
app.listen(port, () => {
    console.log(`server started at ${port}`);
});
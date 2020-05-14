const express = require('express');
const router = express.Router();


// @route  GET api/items
// @desc   get the current tree
// @access public
router.get('/getTree', (req, res) => {
    res.send({'tree-string': '{5}({4}{6})', 'id': 5});
});

module.exports = router;
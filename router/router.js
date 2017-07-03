var express = require('express');
var router = express.Router();
var lights = require('./lights');
var setColor = require('./setColor');


router.get('/', lights);
router.post('/setcolor', setColor);

module.exports = router;

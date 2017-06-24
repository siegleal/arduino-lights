var express = require('express')
var router = require('./router/router.js')
var path = require('path')

var app = express();

app.use('/', router);

app.use(express.static(path.join(__dirname, 'public')));
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'html');

app.listen(3000, function (){
    console.log('listening on port 3000')
})


var express = require('express')
var router = require('./router/router.js')
var path = require('path')
var bodyParser = require('body-parser');

var app = express();
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

app.use('/', router);

app.use(express.static(path.join(__dirname, 'public')));
console.log(path.join(__dirname, 'python_scripts'))
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'html');

app.listen(3030, function (){
    console.log('listening on port 3030')
})


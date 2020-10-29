var express = require('express')
  , http = require('http')
  , path = require('path')
  , mitsobox = require('mitsobox')
  , RFIDService = require("./services/exports")
  , app = express()
  , cors = require('cors');

app.set('port', process.env.PORT || 8888);
app.use(express.logger('dev'));
app.use(express.bodyParser());
app.use(express.methodOverride());
app.use(app.router);
app.use(express.static(path.join(__dirname, 'public')));
app.use(cors());

app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

app.get('/api/rfid/inventorys', RFIDService.inventorys);
app.get('/api/rfid/connect', RFIDService.connect);
app.get('/api/rfid/load', RFIDService.load);
app.get('/api/rfid/beep', RFIDService.beep);


http.createServer(app).listen(app.get('port'), function(){
  console.log('Express server listening on port ' + app.get('port'));
});


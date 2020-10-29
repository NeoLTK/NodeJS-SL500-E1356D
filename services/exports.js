var RFID = require('../src/rfidLib');

exports.inventorys = function(req, res) {
	res.send(RFID.RFIDReader.inventorys());
};

exports.connect = function(req, res) {
	res.send(RFID.RFIDReader.connect());
}

exports.load = function(req, res) {
	res.send(RFID.RFIDReader.load());
}

exports.beep = function(req, res) {
	res.send(RFID.RFIDReader.beep(5, 1));
}
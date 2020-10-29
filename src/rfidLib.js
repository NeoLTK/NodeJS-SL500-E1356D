
/*******************************************************

Nom ......... : rfidLib.js
Role ........ : Prise en charge, RFID reader SL500-E1356D 
Language .... : NodeJS
Auteur ...... : NeoLTK
Licence ..... : GPL

********************************************************/

var ffi = require('ffi');
var ref = require("ref");

var output = {
	old: [],

	parseContent: function(data, len) {
		var offset;
		var index;
		var uid = [];
		var tmp = [];

		for(var i = 0; i < len.deref() / 9; i++ ){
			offset =  ( 9 * i ) + 1;
			index = uid.length;

			uid[index] = this.getUid(data, offset);
		}	

		tmp = JSON.parse(JSON.stringify(uid)); 

		for (var i in tmp) 
			for(var a in this.old) 
				if (typeof  tmp[i] != 'undefined' && tmp[i].hex == this.old[a].hex)
					tmp.splice(i, 1);
		
		this.old = uid;

		return tmp;
	},
	getUid: function(data, offset){
		var tmp;
		var uid = {
			hex: [],
			dec: []
		};

		for (var a = offset; a != (offset + 8); a++){
			tmp = (data[a].toString(16).length == "1" ? "0" + data[a].toString(16) : data[a].toString(16));

			uid.hex[a - offset] = tmp;
			uid.dec[a - offset] = tmp;
		}

		uid.hex = uid.hex.join('');
		uid.dec = uid.dec.reverse().join('');
		uid.dec = this.hexToDec(uid.dec);

		return uid;
	}, 
	hexToDec: function(s) {
	    function add(x, y) {
	        var c = 0;
	        var r = [];
	        var x = x.split('').map(Number);
	        var y = y.split('').map(Number);

	        while (x.length || y.length) {
	            var s = (x.pop() || 0) + (y.pop() || 0) + c;
	            r.unshift(s < 10 ? s : (s - 10)); 
	            c = (s < 10 ? 0 : 1);
	        }

	        if (c) r.unshift(c);

	        return r.join('');
	    }

	    var dec = '0';
	    
	    s.split('').forEach(function(chr) {
	        var n = parseInt(chr, 16);

	        for (var t = 8; t; t >>= 1) {
	            dec = add(dec, dec);
	            if(n & t) dec = add(dec, '1');
	        }
	    });

	    return dec;
	},
	decToHex: function(decStr) {
	  var hex = convertBase(decStr, 10, 16);
	  return (hex ? ('0x' + hex) : null);
	}
}

exports.RFIDReader = {
	MasterRD: null,
	MAX_BUFFER: 4096,
	COM: null,
	CurCOM: 0x0000,
	BaudRate: 19200,
	Type: 0x31,
	liberat: true,
	DEV: true,

	load: function(){
		try {
			this.MasterRD = ffi.Library(__dirname + '/../dll/MasterRD', {
			  'rf_init_com': 			['int', ['int', 'long' ]],
			  'rf_init_type':  			['int', ['int', 'char']],
			  'rf_ClosePort':			['int', []],
			  'rf_beep':  				['void', ['int', 'int']],
			  'rf_light':  				['void', ['int', 'int']],
			  'ISO15693_Inventorys':  	['int', ['int', 'pointer', 'pointer']],
			  'ISO15693_Inventory':  	['int', ['int', 'pointer', 'pointer']],
			});
			return {
				statut: "success",
				code: 1
			};

		} catch (e) {
			if (this.DEV) console.log("Loading MasterRD failled : " + __dirname + " /../dll/MasterRD.dll");

			return {
				statut: "Loading MasterRD failled",
				code: 0 
			}
		}
	},

	connect: function(com){
		if (!com) com = JSON.parse(JSON.stringify(this.CurCOM));
		if (this.COM) com = this.COM;

		try {
			if (com == 0x0020) {
				this.COM = null;
				com = this.CurCOM;

				if (this.DEV) console.log("Valide port not detected");
				throw "RFIDReader COM port not detected";
			}


			if (this.MasterRD.rf_init_com(com, this.BaudRate))
				return this.connect(com + 1)

			if (this.DEV) console.log("Port detected : " + com);
			if(this.MasterRD.rf_init_type(this.CurCOM, this.Type))
				return this.connect(com + 1)

			if (this.DEV) console.log("RFID Init Success Port : " + com);

			this.COM = com;
			this.light("green", 0.3);
			this.light("yellow");

			return {
				statut: "success",
				code: 1
			};
		} catch (e) {
			return {
				statut: e.toString(),
				code: 0 
			}
		}	
	}, 

	inventorys: function(){
		var buffer = new Buffer(this.MAX_BUFFER);
		var len = ref.alloc('char');
		var json = {
			length: 0,
			uid: [],
		};

		try {
			if(this.MasterRD.ISO15693_Inventorys(this.CurCOM, buffer, len)) {
				output.old = [];
				return json;
			}
			
			var uid = output.parseContent(buffer, len);

			if (uid.length > 0) {
				this.beep(5, uid.length);

				this.light("green", uid.length / 10, true);
				this.light("yellow");

				json.length = uid.length;
				json.uid = uid;

				if (this.DEV) console.log("Reading : " + uid);
			}

			return json;
		} catch (e) {
			return {
				statut: e.toString(),
				code: 0
			}
		}
	},

	light: function(color, sec, flag) {
		if (!sec) var sec = 0.1;
		if (flag == null) var flag = false;

		switch (color) {
			case 'yellow':
				color = 3
				break;
			case 'green':
				color = 2;
				break;
			case 'red':
				color = 1
				break;
			case'disable':
				color = 0;
				break;
		}

		for (var i = 0; i != sec * 10; i++) {
			this.MasterRD.rf_light(this.CurCOM, color);
			if (flag) this.MasterRD.rf_light(this.CurCOM, 0);
		}
	},

	beep: function(sec, nb) {
		var bool = false;

		if (sec < 0) sec = 5;
		if (nb < 0) nb = 1;

		for (var i = 0; i != nb * 2; i++) {
			if (!bool) {
				this.MasterRD.rf_beep(this.CurCOM, sec);
				bool = true;
			} else bool = false;
		}		
	}
}

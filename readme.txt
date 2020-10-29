Support for the SL500-E1356D RFID reader on NodeJS applications coupled with expressjs for its implementation on the network

- The driver of the reader available in the dll folder
- The Lib Node JS alone is available in the SRC folder

Start-up procedure :

1. Expressjs starting 
- node app.js

1. Loading RFID Reader DLLs
- http://127.0.0.1:8888/load 

2. Attempting to connect to a valid COM port
- http://127.0.0.1:8888/connect

Uses :

Attempting to scan an RFID
- http://127.0.0.1:8888/inventorys

Test without scanned
- http://127.0.0.1:8888/beep


Windows installation : npm install

Requirement : nodejs x64/x86 de v6 à V10 max
Requirement : python 2.7 x86
Requirement : npm install --global --production windows-build-tools
Requirement : https://go.microsoft.com/fwlink/?LinkId=691126
Requirement : https://support.microsoft.com/fr-fr/help/2977003/the-latest-supported-visual-c-downloads

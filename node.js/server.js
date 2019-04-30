// include the library
var net = require('net');
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;
var pet = false;
var first_pet = false;

var portName = "/dev/ttyACM0";  // serial port to connect
// create  a serial port
var mySerialPort = new serialport(portName, {
    baudRate:9600,
    parser:serialport.parsers.raw
});

mySerialPort.on("open",()=>{
    console.log(portName + " opened");
});
// on receive data
mySerialPort.on("data", (data)=>{
    //console.log("data: "+data);
});



// Configuration parameters
var HOST = 'localhost'; // hots
var PORT = 3000;    // host port
 
// Create Server instance 
var server = net.createServer(onClientConnected);  
 
server.listen(PORT, HOST, function() {  
  console.log('server listening on %j', server.address());
});
 
function onClientConnected(sock) {  
  var remoteAddress = sock.remoteAddress + ':' + sock.remotePort;
  //console.log('new client connected: %s', remoteAddress);
 
  sock.on('data', function(data) {
    console.log('%s Says: %s', remoteAddress, data);
    if(data == "pet") {
        first_pet = true;
        pet = true;
    } else if(mySerialPort.isOpen) {  // if port is open
        mySerialPort.flush();
        mySerialPort.write(data, (err, result) => {
            // code
        });
    }


  });
  sock.on('close',  function () {
    console.log('connection from %s closed', remoteAddress);    
  });
  sock.on('error', function (err) {
    console.log('Connection %s error: %s', remoteAddress, err.message);
  });
};

// watch dog
var inyterval = setInterval(function() {

    if (!pet && first_pet) {
        if(mySerialPort.isOpen)
            mySerialPort.close();   // close serial port
        server.close();     // close server
        clearInterval(inyterval); // clear the interval
    }
    pet = false;
}, 2500);   // interval 2000 ms
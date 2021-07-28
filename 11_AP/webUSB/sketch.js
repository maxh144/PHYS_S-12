let color;
let lastVal = 0;
let currentVal = 0;

function setup() {
  createCanvas(710, 400);
  colorMode(HSB);

}

function draw() {
  background(50);
  drawCircle(); 
}


function drawCircle() {

  let color = int(Math.abs(lastVal - currentVal) / 200.0 * 100.0);
    let test = (currentVal / 1024.0 * 1.8 * Math.PI) + 1.9;
    
  stroke(0);
  strokeWeight(6);
  
    fill(180, color, 50);

  ellipse(355, 200, 300);
  
  line(355, 200, 355 + 150*Math.cos(test), 200 + 150*Math.sin(test));


}

function drawGradient(){

    fill(0, 100, 100);
  arc(355, 200, 300, 300, 1.9, test);
    


}


(function() {
  'use strict';

  document.addEventListener('DOMContentLoaded', event => {
    let connectButton = document.querySelector("#connect");
    let statusDisplay = document.querySelector('#status');
    let port;

    function isNumeric(value) {
      return /^\d+$/.test(value);
  }

    function connect() {
      port.connect().then(() => {
        statusDisplay.textContent = '';
        connectButton.textContent = 'Disconnect';

        console.log("connected");

        port.onReceive = data => {
          let textDecoder = new TextDecoder();
          let decodedData = parseInt(textDecoder.decode(data), 10);
          if (isNumeric(decodedData)){
        

              lastVal = currentVal;
              currentVal = decodedData;

          }
        };
      
        port.onReceiveError = error => {
          console.error(error);
        };
      }, error => {
        statusDisplay.textContent = error;
      });
    }

    connectButton.addEventListener('click', function() {
      if (port) {
        port.disconnect();
        connectButton.textContent = 'Connect';
        statusDisplay.textContent = '';
        port = null;
      } else {
        serial.requestPort().then(selectedPort => {
          port = selectedPort;
          connect();
        }).catch(error => {
          statusDisplay.textContent = error;
        });
      }
    });

    serial.getPorts().then(ports => {
      if (ports.length === 0) {
        statusDisplay.textContent = 'No device found.';
      } else {
        statusDisplay.textContent = 'Connecting...';
        port = ports[0];
        connect();
      }
    });

  });
})();
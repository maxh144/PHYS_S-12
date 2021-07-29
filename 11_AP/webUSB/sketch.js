let color;
let lastVal = 0;
let currentVal = 0;
let angle;
let radius;
let width = 1000;
let height = 600;

function setup() {
  createCanvas(width, height);
  colorMode(HSB);

}

function draw() {
  background(50);

  angle = (currentVal / 1024.0 * 1.8 * Math.PI) + 1.9;
  radius = Math.abs(currentVal - lastVal)/2 + 75;
  console.log(radius);

  drawGradient();
  drawCircle(); 

}


function drawCircle() {
   
    
  stroke(0);
  strokeWeight(8);
  
  noFill();

  ellipse(width/2, height/2, 2*radius);
  
  line(width/2, height/2, width/2 + radius*Math.cos(angle), height/2 + radius*Math.sin(angle));


}

function drawGradient(){

    let color = 0.0;
    let addVal = 0.3;

    for(let i = 1.96; i <= angle; i += 0.005){

        stroke(color % 360, 100,  Math.abs(currentVal - lastVal) + 10);
        line(width/2, height/2, width/2 + radius*Math.cos(i), height/2 + radius*Math.sin(i));

        color += addVal;

    }

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
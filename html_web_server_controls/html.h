R"rawText(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta http-equiv="X-UA-Compatible" content="ie=edge" />
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"></script>
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
  
  
    <title>Daniel's Robot Controls</title>

    <script type="text/javascript">
      var ws;

    //This is where the html sends info to arduino via JSON --------------------------------------------
    function buttonUp() {
      ws.send('{"button" : 0}');
      }
    function forwardDown() {
      ws.send('{"button" : 1}');
      }
    function leftDown() {
      ws.send('{"button" : 2}');
      }
    function rightDown() {
      ws.send('{"button" : 3}');
      }
    function reverseDown() {
      ws.send('{"button" : 4}');
      }

      function WebSocketBegin() {
        if ("WebSocket" in window) {
          // Let us open a web socket
      ws = new WebSocket(
        location.hostname.match(/\.husarnetusers\.com$/) ? "wss://" + location.hostname + "/__port_8001/" : "ws://" + location.hostname + ":8001/"
            );
          //ws = new WebSocket(
          //  "wss://fc94f91f5992989f83474cc8abf7329b-8001.husarnetusers.com"
          //);

          ws.onopen = function() {
            // Web Socket is connected
          };

          ws.onmessage = function(evt) {
            //create a JSON object
            //This is where we read the JSON file passed from the arduino to HTML    -----------------------------------------
            var jsonObject = JSON.parse(evt.data);
            var temp = jsonObject.temp;
            var humidity = jsonObject.humidity;

            document.getElementById("temp").innerText = temp;
            document.getElementById("humidity").innerText = humidity;
  
          };

          ws.onclose = function() {
            // websocket is closed.
            alert("Connection is closed...");
          };
        } else {
          // The browser doesn't support WebSocket
          alert("WebSocket NOT supported by your Browser!");
        }
      }
    </script>
  </head>

  <body onLoad="javascript:WebSocketBegin()">
  <div class = "row">
  <div class = "col-12 text-center" style ="background-color:lightgray;">
  <h3> Daniel's Robot Controls </h1>
  </div>
  </div>
  
  <div class="row">
        <div id="Rxdata"class="col-3" style="background-color:lavender;">
          <br><br>
          <p> 
          Temp:
          <p id ="temp" class ="font-weight-bold">
          </p>
          <p> 
          Humidity:
          <p id ="humidity" class ="font-weight-bold">
          </p>
        </div>
    
        <div id = "controls" class="col-9 text-center">
          <br><br><br>
          <p><button type="button" class="btn btn-primary"          
          onmousedown = "forwardDown()"
          onmouseup = "buttonUp()"
          ontouchstart = "forwardDown()"
          ontouchend = "buttonUp()"
      style="font-size:96px"
      >
      <i class = "fa fa-caret-square-o-up"></i>
          </button></p>
      
          <p><button type="button" class="btn btn-primary mr-5"
          onmousedown = "leftDown()"
          onmouseup = "buttonUp()"
          ontouchstart = "leftDown()"
          ontouchend = "buttonUp()"
      style="font-size:96px"
      >
      <i class = "fa fa-caret-square-o-left"></i>
      </button>
      
          <button type="button" class="btn btn-primary"
          onmousedown = "rightDown()"
          onmouseup = "buttonUp()"
          ontouchstart = "rightDown()"
          ontouchend = "buttonUp()"
      style="font-size:96px"
      >
      <i class = "fa fa-caret-square-o-right"></i>
      </button></p>
      
          <p><button type="button" class="btn btn-primary"
          onmousedown = "reverseDown()"
          onmouseup = "buttonUp()"
          ontouchstart = "reverseDown()"
          ontouchend = "buttonUp()"
      style="font-size:96px"
      >
      <i class = "fa fa-caret-square-o-down"></i>
      </button></p>
      
        </div>  
    </div>    
  </body>
</html>

)rawText"



const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <title>Web Lichtkrant</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {
      font-family: Arial, Helvetica, sans-serif;
      text-align: center;
    }
    h1 {
      font-size: 1.8rem;
      color: white;
      margin: 0;
      padding: 0;
    }
    .topnav {
      overflow: hidden;
      background-color: #143642;
      height: 120px;
      position: relative;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
    }
    .topnav h1 {
      margin: 5px 0;
    }
    .topnav .refresh-button {
      position: absolute;
      right: 20px;
      top: 25px;
    }
    body {
      margin: 0;
      padding: 0;
      background-color: blue;
    }
    .content {
      padding: 0px;
      margin: 0 auto;
      text-align: left;
    }
    .brightness {
      position: absolute;
      left: 10px;
      top: 10px;
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    .brightness-buttons {
      display: flex;
      gap: 10px;
      margin-top: 10px;
    }
    .button-brightness {
      margin: 2px;
      width: 100px;
      padding: 15px;
      font-size: 20px;
      text-align: center;
      outline: none;
      color: #fff;
      background-color: #ff0000;
      border: none;
      border-radius: 5px;
      -webkit-touch-callout: none;
      -webkit-user-select: none;
      -khtml-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
      -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
    }
    .button-brightness:active {
      background-color: #ff0000;
      box-shadow: 2px 2px #CDCDCD;
      transform: translateY(2px);
    }
    .brightness-text {
      font-size: 1.5rem;
      color: #8c8c8c;
      font-weight: bold;
      margin-top: 5px;
    }
    .button {
      margin: 2px;
      margin-right: 0px;
      margin-left: 5px;
      width: 150px;
      padding: 15px;
      font-size: 24px;
      text-align: center;
      outline: none;
      color: #fff;
      background-color: #ff0000;
      border: none;
      border-radius: 5px;
      -webkit-touch-callout: none;
      -webkit-user-select: none;
      -khtml-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
      -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
      white-space: normal;
      word-wrap: break-word;
      height: auto;
    }
    .button:active {
      background-color: #ff0000;
      box-shadow: 2px 2px #CDCDCD;
      transform: translateY(2px);
    }
    .button-row {
      display: flex;
      justify-content: flex-start;
      margin-top: 20px;
    }
    .button-row .button {
      margin: 0 5px;
    }
  </style>
</head>
<body>
  <div class="topnav">
    <h1>STROBOCOPS</h1>
    <h1>LICHTKRANT</h1>
    <button id="button35" class="button refresh-button" onclick="location.reload()">Refresh</button>
  </div>
  <div class="content">
    <div class="brightness">
      <div class="brightness-buttons">
        <button class="button-brightness" onclick="adjustBrightness('-')">-</button>
        <button class="button-brightness" onclick="adjustBrightness('+')">+</button>
      </div>
      <p class="brightness-text">Brightness: <span id="brightnessValue">50</span>%</p>
    </div>
    <div class="button-row">
      <p><button id="button1" class="button" onclick="toggleEffect('effect_1')">Cops 1</button></p>
      <p><button id="button2" class="button" onclick="toggleEffect('effect_2')">Cops 2</button></p>
      <p><button id="button3" class="button" onclick="toggleEffect('effect_3')">Cops 3</button></p>
      <p><button id="button4" class="button" onclick="toggleEffect('effect_4')">Cops 4</button></p>
      <p><button id="button5" class="button" onclick="toggleEffect('effect_5')">Cops 5</button></p>
    </div>
    <div class="button-row">
      <p><button id="button20" class="button" onclick="toggleEffect('effect_20')">Cops 6</button></p>
      <p><button id="button32" class="button" onclick="toggleEffect('effect_32')">COPS 7</button></p>
      <p><button id="button15" class="button" onclick="toggleEffect('effect_15')">Website</button></p>
      <p><button id="button21" class="button" onclick="toggleEffect('effect_21')">Monkeys</button></p>
      <p><button id="button25" class="button" onclick="toggleEffect('effect_25')">POETIN</button></p>
    </div>  
    <div class="button-row"> 
      <p><button id="button6" class="button" onclick="toggleEffect('effect_6')">Strobe Full</button></p>
      <p><button id="button7" class="button" onclick="toggleEffect('effect_7')">Strobe 1/2</button></p>
      <p><button id="button8" class="button" onclick="toggleEffect('effect_8')">Strobe <[]></button></p>
      <p><button id="button9" class="button" onclick="toggleEffect('effect_9')">Strobe U/D</button></p>
      <p><button id="button10" class="button" onclick="toggleEffect('effect_10')">Sparkle</button></p>
    </div>
    <div class="button-row"> 
      <p><button id="button11" class="button" onclick="toggleEffect('effect_11')">Rainbows</button></p>  
      <p><button id="button12" class="button" onclick="toggleEffect('effect_12')">Fire</button></p>
      <p><button id="button13" class="button" onclick="toggleEffect('effect_13')">Data</button></p>
      <p><button id="button14" class="button" onclick="toggleEffect('effect_14')">Carnaval</button></p>
      <p><button id="button17" class="button" onclick="toggleEffect('effect_17')">Hearts</button></p>
    </div>
    <div class="button-row"> 
      <p><button id="button19" class="button" onclick="toggleEffect('effect_19')">Red</button></p> 
      <p><button id="button22" class="button" onclick="toggleEffect('effect_22')">Green</button></p>
      <p><button id="button23" class="button" onclick="toggleEffect('effect_23')">Blue</button></p>
      <p><button id="button18" class="button" onclick="toggleEffect('effect_18')">Pink</button></p>
      <p><button id="button16" class="button" onclick="toggleEffect('effect_16')">Red | Blue</button></p>
    </div>
    <div class="button-row"> 
      <p><button id="button26" class="button" onclick="toggleEffect('effect_26')">CABRIO</button></p> 
      <p><button id="button27" class="button" onclick="toggleEffect('effect_27')">C.A.B.R.I.O</button></p>
      <p><button id="button28" class="button" onclick="toggleEffect('effect_28')">POWER</button></p>
      <p><button id="button29" class="button" onclick="toggleEffect('effect_29')">LSD</button></p>
      <p><button id="button30" class="button" onclick="toggleEffect('effect_30')">NEUKEN</button></p>
    </div>
    <div class="button-row"> 
      <p><button id="button31" class="button" onclick="toggleEffect('effect_31')">LOADING</button></p> 
      <p><button id="button24" class="button" onclick="toggleEffect('effect_24')">HARDER</button></p>
      <p><button id="button33" class="button" onclick="toggleEffect('effect_33')">ADEM</button></p>
      <p><button id="button34" class="button" onclick="toggleEffect('effect_34')">VOEL NIKS</button></p>
      <p><button id="button35" class="button" onclick="toggleEffect('effect_35')">35 N/A</button></p>
    </div>
    <p>&nbsp;</p>
    <p>&nbsp;</p>
  </div>
  <script>
    var gateway = `ws://${window.location.hostname}/ws`;
    var websocket;
    window.addEventListener('load', onLoad);
    function initWebSocket() {
      console.log('Trying to open a WebSocket connection...');
      websocket = new WebSocket(gateway);
      websocket.onopen = onOpen;
      websocket.onclose = onClose;
      websocket.onmessage = onMessage;
    }
    function onOpen(event) {
      console.log('Connection opened');
      websocket.send('Connect ');
    }
    function onClose(event) {
      console.log('Connection closed');
      setTimeout(initWebSocket, 2000);
    }
    function onMessage(event) {
      console.log('Message from server:', event.data);
      var effects = event.data.split(",");
      document.getElementById('button1').style.backgroundColor = effects[0] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button2').style.backgroundColor = effects[1] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button3').style.backgroundColor = effects[2] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button4').style.backgroundColor = effects[3] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button5').style.backgroundColor = effects[4] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button6').style.backgroundColor = effects[5] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button7').style.backgroundColor = effects[6] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button8').style.backgroundColor = effects[7] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button9').style.backgroundColor = effects[8] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button10').style.backgroundColor = effects[9] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button11').style.backgroundColor = effects[10] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button12').style.backgroundColor = effects[11] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button13').style.backgroundColor = effects[12] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button14').style.backgroundColor = effects[13] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button15').style.backgroundColor = effects[14] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button16').style.backgroundColor = effects[15] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button17').style.backgroundColor = effects[16] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button18').style.backgroundColor = effects[17] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button19').style.backgroundColor = effects[18] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button20').style.backgroundColor = effects[19] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button21').style.backgroundColor = effects[20] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button22').style.backgroundColor = effects[21] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button23').style.backgroundColor = effects[22] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button24').style.backgroundColor = effects[23] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button25').style.backgroundColor = effects[24] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button26').style.backgroundColor = effects[25] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button27').style.backgroundColor = effects[26] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button28').style.backgroundColor = effects[27] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button29').style.backgroundColor = effects[28] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button30').style.backgroundColor = effects[29] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button31').style.backgroundColor = effects[30] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button32').style.backgroundColor = effects[31] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button33').style.backgroundColor = effects[32] === '1' ? '#4CAF50' : '#ff0000';
      document.getElementById('button34').style.backgroundColor = effects[33] === '1' ? '#4CAF50' : '#ff0000';
      var brightnessValue = document.getElementById('brightnessValue');
      brightnessValue.textContent = effects[34];    
    }
    function adjustBrightness(direction) {
      websocket.send('adjustBrightness' + direction);
    }
    function onLoad(event) {
      initWebSocket();
    }
    function toggleEffect(effect) {
      websocket.send('toggle' + effect.charAt(0).toUpperCase() + effect.slice(1));
    }
  </script>
</body>
</html>
)rawliteral";

var Clay = require('pebble-clay');
var clayConfig = require('./config');
var clay = new Clay(clayConfig);

//TagDev: Include on clay and make it customizable;


// TagDev: Set this up on Clay
var units="c";



var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};
function locationSuccess(pos) {
  // Construct URL
 
    //Get JSON from Yahoo Weather
   var urlyahoo = 'https://query.yahooapis.com/v1/public/yql?q=select item.condition, ' +
      'item.forecast from weather.forecast(1) where woeid in ' +
      '(select woeid from geo.places(1) where ' +
      'text=\'(' + pos.coords.latitude + ',' + pos.coords.longitude + ')\') and ' +
      'u=\'' + units + '\'&format=json'; 
  
      console.log("Url is " + urlyahoo);
  
  
  // Send request to OpenWeatherMap
  xhrRequest(encodeURI(urlyahoo), 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      console.log("units are " + units );
      
      var temperature = Math.round(json.query.results.channel.item.condition.temp) + units;
      console.log("Temperature is " + temperature);
   
      // Conditions item.condition.code
      var conditions = Math.round(json.query.results.channel.item.condition.code);      
      console.log("Conditions are " + conditions);
    
    
      // Assemble dictionary using our keys
      var dictionary = {
        "WeatherTemp": temperature,
        "WeatherCond": conditions};
      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log("Weather info sent to Pebble successfully!");
        },
        function(e) {
          console.log("Error sending weather info to Pebble!");
        }
      );
    }      
  );
}

function locationError(err) {
  console.log("Error requesting location!");
}

function getWeather() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log("PebbleKit JS ready!");

    // Get the initial weather
    getWeather();
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log("AppMessage received!");
    getWeather();
  }                     
);



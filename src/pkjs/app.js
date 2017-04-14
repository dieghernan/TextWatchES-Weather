var Clay = require('pebble-clay');
var clayConfig = require('./config');
var clay = new Clay(clayConfig);






var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};
function locationSuccess(pos) {
  
  var settings = JSON.parse(localStorage.getItem('clay-settings')) || {};
   var units = unitsToString(settings.WeatherUnit);

  // Construct URL
 
    //Get JSON from Yahoo Weather
   var urlyahoo = 'https://query.yahooapis.com/v1/public/yql?q=select astronomy,item.condition ' +
      'from weather.forecast(1) where woeid in ' +
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
      
      var temperature = Math.round(json.query.results.channel.item.condition.temp) +"°" + units;
      console.log("Temperature is " + temperature);
   
      // Conditions item.condition.code
      var conditions = Math.round(json.query.results.channel.item.condition.code);      
      console.log("Conditions are " + conditions);
      
      var condparsed=parseyahoo(conditions);
      
      var conday=parseday(condparsed);
      var condnight=parsenight(condparsed);
      
      console.log("Parsed day"+conday+" parsed night "+condnight)    ;
      
        // Sunrise
      var risebase=json.query.results.channel.astronomy.sunrise;
      var sunrisehhmm=gettime(risebase);
   
    //Sunset
      var setbase=json.query.results.channel.astronomy.sunset;
      var sunsethhmm=gettime(setbase);
      
      
      
      // Assemble dictionary using our keys
      var dictionary = {
        "WeatherTemp": temperature,
        "WeatherCondDay": conday,
        "WeatherCondNight":condnight,
        "HourSunset": sunsethhmm,
        "HourSunrise":sunrisehhmm
      };
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

Pebble.addEventListener('webviewclosed',
  function(e) {
    console.log("Updating config!");
    getWeather();
  }                     
);                   
              
                        
function unitsToString(unit) {
  if (unit) {
    return 'f';
  }
  return 'c';
}

function gettime(timetoparse){
  var arrayrise = timetoparse.split(" ");
  var aamm=arrayrise[1];
  var array1m=arrayrise[0];
  var arrayhhmm=array1m.split(":");
  var hh=parseInt(arrayhhmm[0]);
  var mm=parseInt(arrayhhmm[1]);
  if (aamm=='am'){
    if (hh==12){
      return mm;      
    }
    else {
      return (hh*100)+mm;
    }     
  }
  else {
    if (hh==12){
      return (hh*100)+mm;
    }
    else {
      return ((hh+12)*100)+mm;
    }    
  }
}  

// Function to translate Yahoo
function parseyahoo(condcode){
  if (condcode===0) return 0; //Condcode is tornado - icon is tornado
else if (condcode==1) return 1; //Condcode is tropical storm - icon is day-storm-showers
else if (condcode==2) return 2; //Condcode is hurricane - icon is hurricane
else if (condcode==3) return 3; //Condcode is severe thunderstorms - icon is thunderstorm
else if (condcode==4) return 3; //Condcode is thunderstorms - icon is thunderstorm
else if (condcode==5) return 4; //Condcode is mixed rain and snow - icon is rain-mix
else if (condcode==6) return 4; //Condcode is mixed rain and sleet - icon is rain-mix
else if (condcode==7) return 4; //Condcode is mixed snow and sleet - icon is rain-mix
else if (condcode==8) return 5; //Condcode is freezing drizzle - icon is hail
else if (condcode==9) return 6; //Condcode is drizzle - icon is showers
else if (condcode==10) return 5; //Condcode is freezing rain - icon is hail
else if (condcode==11) return 6; //Condcode is showers - icon is showers
else if (condcode==12) return 23; //Condcode is showers - icon is day-rain-mix
else if (condcode==13) return 7; //Condcode is snow flurries - icon is snowflake-cold
else if (condcode==14) return 7; //Condcode is light snow showers - icon is snowflake-cold
else if (condcode==15) return 7; //Condcode is blowing snow - icon is snowflake-cold
else if (condcode==16) return 7; //Condcode is snow - icon is snowflake-cold
else if (condcode==17) return 5; //Condcode is hail - icon is hail
else if (condcode==18) return 4; //Condcode is sleet - icon is rain-mix
else if (condcode==19) return 8; //Condcode is dust - icon is dust
else if (condcode==20) return 9; //Condcode is foggy - icon is fog
else if (condcode==21) return 8; //Condcode is haze - icon is dust
else if (condcode==22) return 12; //Condcode is smoky - icon is smoke
else if (condcode==23) return 11; //Condcode is blustery - icon is strong-wind
else if (condcode==24) return 10; //Condcode is windy - icon is windy
else if (condcode==25) return 7; //Condcode is cold - icon is snowflake-cold
else if (condcode==26) return 13; //Condcode is cloudy - icon is cloudy
else if (condcode==27) return 15; //Condcode is mostly cloudy (night) - icon is night-alt-cloudy
else if (condcode==28) return 14; //Condcode is mostly cloudy (day) - icon is day-cloudy
else if (condcode==29) return 15; //Condcode is partly cloudy (night) - icon is night-alt-cloudy
else if (condcode==30) return 14; //Condcode is partly cloudy (day) - icon is day-cloudy
else if (condcode==31) return 16; //Condcode is clear (night) - icon is night-clear
else if (condcode==32) return 17; //Condcode is sunny - icon is sunny
else if (condcode==33) return 18; //Condcode is fair (night) - icon is night-alt-partly-cloudy
else if (condcode==34) return 19; //Condcode is fair (day) - icon is sunny-overcast
else if (condcode==35) return 4; //Condcode is mixed rain and hail - icon is rain-mix
else if (condcode==36) return 25; //Condcode is hot - icon is thermometer
else if (condcode==37) return 1; //Condcode is isolated thunderstorms - icon is day-storm-showers
else if (condcode==38) return 1; //Condcode is scattered thunderstorms - icon is day-storm-showers
else if (condcode==39) return 1; //Condcode is scattered thunderstorms - icon is day-storm-showers
else if (condcode==40) return 6; //Condcode is scattered showers - icon is showers
else if (condcode==41) return 7; //Condcode is heavy snow - icon is snowflake-cold
else if (condcode==42) return 7; //Condcode is scattered snow showers - icon is snowflake-cold
else if (condcode==43) return 7; //Condcode is heavy snow - icon is snowflake-cold
else if (condcode==44) return 19; //Condcode is partly cloudy - icon is sunny-overcast
else if (condcode==45) return 1; //Condcode is thundershowers - icon is day-storm-showers
else if (condcode==46) return 7; //Condcode is snow showers - icon is snowflake-cold
else if (condcode==47) return 1; //Condcode is isolated thundershowers - icon is day-storm-showers
else return 26;   
}

function parseday(condnum){
  if (condnum===0) return "a";  //tornado
  else if (condnum===1) return "b";  //day-storm-showers
  else if (condnum===2) return "c";  //hurricane
  else if (condnum===3) return "d";  //thunderstorm
  else if (condnum===4) return "e";  //rain-mix
  else if (condnum===5) return "f";  //hail
  else if (condnum===6) return "g";  //showers
  else if (condnum===7) return "h";  //snowflake-cold
  else if (condnum===8) return "i";  //dust
  else if (condnum===9) return "j";  //fog
  else if (condnum===10) return "k";  //windy
  else if (condnum===11) return "l";  //strong-wind
  else if (condnum===12) return "m";  //smoke
  else if (condnum===13) return "n";  //cloudy
  else if (condnum===14) return "o";  //day-cloudy
  else if (condnum===15) return "o";  //day-cloudy
  else if (condnum===16) return "r";  //sunny
  else if (condnum===17) return "r";  //sunny
  else if (condnum===18) return "t";  //sunny-overcast
  else if (condnum===19) return "t";  //sunny-overcast
  else if (condnum===20) return "u";  //hot
  else if (condnum===21) return "v";  //stars
  else if (condnum===22) return "b";  //day-storm-showers
  else if (condnum===23) return "x";  //day-rain-mix
  else if (condnum===24) return "x";  //day-rain-mix
  else if (condnum===25) return "z";  //thermometer
  else if (condnum===26) return "0";  //na
}

function parsenight(condnum){
  if (condnum===0) return "a";  //tornado
  else if (condnum===1) return "w";  //night-alt-storm-showers
  else if (condnum===2) return "c";  //hurricane
  else if (condnum===3) return "d";  //thunderstorm
  else if (condnum===4) return "e";  //rain-mix
  else if (condnum===5) return "f";  //hail
  else if (condnum===6) return "g";  //showers
  else if (condnum===7) return "h";  //snowflake-cold
  else if (condnum===8) return "i";  //dust
  else if (condnum===9) return "j";  //fog
  else if (condnum===10) return "k";  //windy
  else if (condnum===11) return "l";  //strong-wind
  else if (condnum===12) return "m";  //smoke
  else if (condnum===13) return "n";  //cloudy
  else if (condnum===14) return "p";  //night-alt-cloudy
  else if (condnum===15) return "p";  //night-alt-cloudy
  else if (condnum===16) return "q";  //night-clear
  else if (condnum===17) return "q";  //night-clear
  else if (condnum===18) return "s";  //night-alt-partly-cloudy
  else if (condnum===19) return "s";  //night-alt-partly-cloudy
  else if (condnum===20) return "u";  //hot
  else if (condnum===21) return "v";  //stars
  else if (condnum===22) return "w";  //night-alt-storm-showers
  else if (condnum===23) return "y";  //night-alt-rain-mix
  else if (condnum===24) return "y";  //night-alt-rain-mix
  else if (condnum===25) return "z";  //thermometer
  else if (condnum===26) return "0";  //na                    
}
                

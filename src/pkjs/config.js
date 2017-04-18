// Clay Config: see https://github.com/pebble/clay


module.exports = [
  {
    "type": "heading",
    "defaultValue": "Settings"
  },

  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "General settings"
      },
         {
          "type": "select",
          "messageKey": "Lang",
          "defaultValue": "1",
          "label": "Language",
          "options": [
                        { 
              "label": "Spanish - Español",
              "value": "1" 
            },
            { 
              "label": "English",
              "value": "2" 
            },
            { 
              "label": "German - Deutsch",
              "value": "3" 
            },
            { 
              "label": "French - Français",
              "value": "4" 
            },
            {"label":"Portuguese (Brazil) - Português",
             "value": "5"              
            }
          ]
        },
      {
          "type": "select",
          "messageKey": "DateFormat",
          "defaultValue": "1",
          "label": "Date Format",
          "options": [
                        { 
              "label": "dd mm",
              "value": "1" 
            },
            { 
              "label": "mm dd",
              "value": "2" 
            }
          ]
        },
      {
        "type": "color",
        "messageKey": "BackgroundColor",
        "defaultValue": "0x000055",
        "label": "Background"
      },
      {
        "type": "color",
        "messageKey": "ForegroundColor",
        "defaultValue": "0xFFFFFF",
        "label": "Text"
      },
       {"type": "section",
      "items": [
      {
        "type": "heading",
        "defaultValue": "Night Theme",
        "size":4
      }  ,
      {
        "type": "toggle",
        "messageKey": "NightTheme",
        "label": "Activate Night Theme",
        "defaultValue": false,
        "description": "When activate requires GPS. Theme applied between sunset and sunrise."
      },
      {
        "type": "color",
        "messageKey": "BackgroundColorNight",
        "defaultValue": "0xFFFFFF",
        "label": "Background"
      },
      {
        "type": "color",
        "messageKey": "ForegroundColorNight",
        "defaultValue": "0x000055",
        "label": "Text"
      }
        ]
       }      
    ]
  },
  
 {
    "type": "section",
    "items": [ 
      {
        "type": "heading",
        "defaultValue": "Weather Settings"
      },
      {
        "type": "toggle",
        "messageKey": "DisplayTemp",
        "label": "Weather",
        "defaultValue": false      
      },
      {
        "type": "toggle",
        "messageKey": "WeatherUnit",
        "label": "Temperature in Fahrenheit",
        "defaultValue": false      
      },
       {
        "type": "select",
        "messageKey": "WeatherProv",
        "defaultValue": "yahoo",
        "label": "Weather Provider",
        "description": "WU and OWM requires authentification. See next section",
        "options": [
          { 
            "label": "Yahoo", 
            "value": "yahoo" 
          },
          { 
            "label": "OpenWeatherMap",
            "value": "owm"
          },
          {
            "label": "WeatherUnderground",
            "value": "wu"
          }
        ]        
      },
      {
        "type": "input",
        "messageKey": "EmailPMKEY",
        "defaultValue": "",
        "label": "pmkey.xyz User",
        "description": "pmkey.xyz is a free service for Pebble users that allows you to store safely all your API keys in a single place. Check <a href=https://www.pmkey.xyz/>pmkey.xyz</a> ",
        "attributes": {
          "placeholder": "eg: john.doe@pmkey.xyz",
          "type": "email"
        }
      },
      {
        "type": "input",
        "messageKey": "PINPMKEY",
        "defaultValue": "",
        "label": "pmkey.xyz PIN",
        "attributes": {
          "placeholder": "eg: 12345"
        }
      },      
      {
        "type": "slider",
        "messageKey": "UpSlider",
        "defaultValue": 30,
        "label": "Update frequency (minutes)",
        "description": "More frequent requests will drain your phone battery faster",
        "min": 15,
        "max": 120,
        "step": 15}
    ]
 },
 {
    "type": "submit",
    "defaultValue":"Ok"
  },
  {
      "type": "heading",
      "defaultValue": "Made in Madrid, Spain",
      "size":6
  }    
];

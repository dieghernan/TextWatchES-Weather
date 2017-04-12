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
        "defaultValue": "Color settings"
      },
      {
        "type": "color",
        "messageKey": "BackgroundColor",
        "defaultValue": "0x000000",
        "label": "Background"
      },
      {
        "type": "color",
        "messageKey": "ForegroundColor",
        "defaultValue": "0xFFFFFF",
        "label": "Text"
      }
      
    ]
  },
  
 {
    "type": "section",
    "items": [ 
      {
        "type": "heading",
        "defaultValue": "Local Settings"
      },
              
           {
          "type": "select",
          "messageKey": "Lang",
          "defaultValue": "1",
          "label": "Language",
          "options": [
                        { 
              "label": "es - Español",
              "value": "1" 
            },
            { 
              "label": "en - English",
              "value": "2" 
            },
            { 
              "label": "de - German",
              "value": "3" 
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
              "label": "DD MM",
              "value": "1" 
            },
            { 
              "label": "MM DD",
              "value": "2" 
            }
          ]
        },
      
        {
        "type": "toggle",
        "messageKey": "WeatherUnit",
        "label": "Temperature in Fahrenheit",
        "defaultValue": false      
      },
    ]
 },

  //Yahoo disclaimer
  {
      "type": "heading",
      "defaultValue": "Weather info provided by <a href=https://www.yahoo.com/?ilc=401>Yahoo.com </a>",
      "size":6
  },
      
 {
    "type": "submit",
    "defaultValue": "OK"
  }
];

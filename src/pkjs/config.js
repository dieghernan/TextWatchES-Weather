// Clay Config: see https://github.com/pebble/clay


module.exports = [
  {
    "type": "heading",
    "defaultValue": "Configuración"
  },

  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Opciones de Color"
      },
      {
        "type": "color",
        "messageKey": "BackgroundColor",
        "defaultValue": "0x000000",
        "label": "Esfera"
      },
      {
        "type": "color",
        "messageKey": "ForegroundColor",
        "defaultValue": "0xFFFFFF",
        "label": "Texto"
      }
      
    ]
  },
  
 {
    "type": "section",
    "items": [ 
      {
        "type": "heading",
        "defaultValue": "Opciones de Tiempo"
      },
        {
        "type": "toggle",
        "messageKey": "WeatherUnit",
        "label": "Temperatura en Fahrenheit",
        "defaultValue": false,
          
          //TagDev: Need to update on save settings, not on restart watchface;
          "description": "Los cambios se aplicarán al reiniciar la esfera"
          //EndTagDev
      },

  //Yahoo disclaimer
  {
      "type": "text",
      "defaultValue": "Condiciones meteorológicas proporcionadas por <a href=https://www.yahoo.com/?ilc=401>Yahoo.com </a>"
  }
     
      
    
    
    ]
 },

 {
    "type": "submit",
    "defaultValue": "Guardar"
  }
];
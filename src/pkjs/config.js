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
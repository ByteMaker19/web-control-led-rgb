#include <WiFi.h> 
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>

// Configura tu red WiFi
const char* ssid = "SSID";
const char* password = "PASSWORD";

// Configura el aro LED
#define LED_PIN    25
#define LED_COUNT  48
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

WebServer server(80);

// Variables de color
int red = 0, green = 0, blue = 0;


String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <title>Control RGB</title>
  <style>
    body {
      margin: 0;
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      /* Fondo con la imagen que pediste */
      background: url('https://i.postimg.cc/7YtrVgQQ/web.jpg') no-repeat center center fixed;
      background-size: cover;
      color: #333;
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      position: relative;
    }

    h2 {
      color: #333;
      margin-bottom: 30px;
    }

    .slider-container {
      background: white;
      padding: 20px;
      margin: 10px;
      border-radius: 12px;
      box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);
      width: 90%%;
      max-width: 400px;
    }

    label {
      font-size: 1.1em;
      display: block;
      margin-bottom: 10px;
    }

    input[type=range] {
      width: 100%%;
      height: 8px;
      -webkit-appearance: none;
      background: #ddd;
      border-radius: 5px;
      outline: none;
      transition: background 0.3s;
    }

    input[type=range]::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 18px;
      height: 18px;
      background: #007bff;
      border-radius: 50%%;
      cursor: pointer;
      box-shadow: 0 2px 6px rgba(0,0,0,0.3);
    }

    span {
      font-weight: bold;
    }

    .logo {
      position: fixed;
      bottom: 10px;
      left: 10px;
      width: 100px;
      opacity: 0.85;
    }
  </style>
</head>
<body>
  <h2>Control de Aro LED RGB</h2>

  <div class="slider-container">
    <label>Rojo: <span id="rval">0</span></label>
    <input type="range" min="0" max="255" value="0" id="r">
  </div>

  <div class="slider-container">
    <label>Verde: <span id="gval">0</span></label>
    <input type="range" min="0" max="255" value="0" id="g">
  </div>

  <div class="slider-container">
    <label>Azul: <span id="bval">0</span></label>
    <input type="range" min="0" max="255" value="0" id="b">
  </div>

  <!-- Logo de empresa -->
  <img src="https://i.postimg.cc/C1TMSjGx/Byte-Maker.png" alt="Logo Empresa" class="logo">

  <script>
    window.onload = function() {
      const r = document.getElementById('r');
      const g = document.getElementById('g');
      const b = document.getElementById('b');

      function updateColor() {
        document.getElementById('rval').innerText = r.value;
        document.getElementById('gval').innerText = g.value;
        document.getElementById('bval').innerText = b.value;

        fetch(`/setColor?r=${r.value}&g=${g.value}&b=${b.value}`)
          .then(response => {
            if (!response.ok) {
              console.error('Error al enviar colores');
            }
          })
          .catch(err => console.error('Fetch error:', err));
      }

      r.addEventListener('input', updateColor);
      g.addEventListener('input', updateColor);
      b.addEventListener('input', updateColor);
    };
  </script>
</body>
</html>
)rawliteral";

void setColorAll(int r, int g, int b);

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Inicializa los LEDs apagados

  // Conexión WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Rutas del servidor web
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/setColor", []() {
    if (server.hasArg("r")) red = server.arg("r").toInt();
    if (server.hasArg("g")) green = server.arg("g").toInt();
    if (server.hasArg("b")) blue = server.arg("b").toInt();
    setColorAll(red, green, blue);
    server.send(200, "text/plain", "OK");
  });

  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  server.handleClient();
}

void setColorAll(int r, int g, int b) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}
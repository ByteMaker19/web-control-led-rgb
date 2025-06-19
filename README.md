# 🎛️ Controlador RGB para Aro LED con ESP32

Este proyecto permite controlar un aro LED RGB (basado en WS2812 o similar) mediante una interfaz web desde cualquier dispositivo conectado a la misma red WiFi. Utiliza un ESP32 y una interfaz HTML sencilla con sliders para ajustar los colores rojo, verde y azul en tiempo real.

![Interfaz Web](https://i.postimg.cc/7YtrVgQQ/web.jpg)

---

## 🧰 Requisitos

- ESP32 (cualquier modelo con WiFi)
- Aro LED WS2812 (o tira LED compatible)
- Fuente de alimentación adecuada para los LEDs
- Arduino IDE
- Librerías necesarias:
  - [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
  - WiFi.h (incluida por defecto en el ESP32)

---

## ⚙️ Conexiones

| Componente           | ESP32     |
|----------------------|-----------|
| DIN del aro LED      | GPIO 25   |
| GND                  | GND       |
| 5V (o 3.3V si aplica)| VIN / 5V  |

🔧 Se recomienda:
- Resistencia de 330Ω entre GPIO 25 y DIN.
- Condensador de 1000µF entre 5V y GND.

---

## 🚀 Cómo usar

1. **Clona el repositorio o descarga el archivo `.ino`.**

2. **Abre el archivo en el Arduino IDE.**

3. **Configura tus credenciales WiFi:**
   ```cpp
   const char* ssid = "TU_SSID";
   const char* password = "TU_PASSWORD";

4. **Sube el código al ESP32.:**
   

5. **Abre el Monitor Serial (baud 115200) para ver la dirección IP**
   

6. **Desde un navegador, entra a esa IP y usa los sliders para controlar el color.**


**Diseñado por ByteMaker**
  
   ![Interfaz Web](https://i.postimg.cc/C1TMSjGx/Byte-Maker.png)

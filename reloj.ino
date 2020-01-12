// librerías necesarias:

// ADAFRUIT GFX LIBRARY https://github.com/adafruit/Adafruit-GFX-Library
// MAX72XXPANEL   https://github.com/markruys/arduino-Max72xxPanel/archive/master.zip
// DHT SENSOR LIBRARY https://github.com/adafruit/DHT-sensor-library
// ADAFRUIT SENSOR https://github.com/adafruit/Adafruit_Sensor
// DS1302 http://www.rinkydinkelectronics.com/download.php?f=DS1302.zip

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <DHT.h>
#include <DS1302.h>

#include <EEPROM.h>

// Conexión de pines DS1302
// DS1302:  CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 4

DS1302 rtc(2, 3, 4);  //puede modificar los pines para utilizar el ds1302

// Conexión de pines matiz led

//Vcc - Vcc
//Gnd - Gnd
//Din - Mosi (Pin 11)
//Cs  - SS (Pin 10)
//Clk - Sck (Pin 13)

// Definimos el pin digital donde se conecta el sensor DHT11
#define DHTPIN 7
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

const int pinCS = 10; // pin cs para matiz led
const int numberOfHorizontalDisplays = 4; // Cantidad de matices led
const int numberOfVerticalDisplays = 1; // Cantidad de matices led vertical

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);  // Configuración de la matriz

String tape = "..";  //tu mensaje
String sep = "H=";
String sep1 = "C=";
String humedad = "..";
String temperatura = "..";

const int wait = 30; // Constante para el muestreo de la matriz

const int spacer = 1; // Constante para el espacion entre letras
const int width = 5 + spacer; // 5 pixels por letra

byte value; // Variable para lectura y escritura de eeprom
Time t; // Variable para separar las horas de los minutos

void setup() {
  matrix.setIntensity(0); // Configuración del brillo de la matriz de 0 a 15

  //
  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 1, 0); // The second display is at <1, 0>
  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>

  matrix.setRotation(0, 1);    // Display is position upside down
  matrix.setRotation(1, 1);    // Display is position upside down
  matrix.setRotation(2, 1);    // Display is position upside down
  matrix.setRotation(3, 1);    // Display is position upside down

  /* // retirar comentario a esto y comentar lo de arriba para una sola matriz
     matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
     matrix.setRotation(0, 1);    // Display is position upside down
  */

  rtc.halt(false);  // Habilita el reloj
  rtc.writeProtect(false);  // Deshabilita protección contra escritura

  // Configuración de la hora, al iniciarlo por primera vez la posición 20 de la memoria eeprom será diferente de 1 por lo que configura la nueva hora y escribirá el valor de 1 en la memoria eeprom para no configurarlo en caso de perder la energía, la hora se mantendrá si la batería del ds1302 está conectada.
  value = EEPROM.read(20);  // Lectura de memoria eeprom
  if (value = ! 1) {
    rtc.setDOW(FRIDAY);        // Configuración del día
    rtc.setTime(22, 33, 0);     // Configuración de la hora
    rtc.setDate(10, 1, 2020);   // Configuración de la fecha
    EEPROM.write(20, 1); // Escritura de la memoria eeprom
  }
  dht.begin(); //Iniciamos el sensor dht11
}
void loop() {
  t = rtc.getTime();  // Lectura de la hora.

  //La intensidad de luz será mas fuerte o suave según la hora.
  if (t.hour == 0) {
    matrix.setIntensity(0);
  }
  if (t.hour == 1) {
    matrix.setIntensity(0);
  }
  if (t.hour == 2) {
    matrix.setIntensity(0);
  }
  if (t.hour == 3) {
    matrix.setIntensity(0);
  }
  if (t.hour == 4) {
    matrix.setIntensity(0);
  }
  if (t.hour == 5) {
    matrix.setIntensity(0);
  }
  if (t.hour == 6) {
    matrix.setIntensity(0);
  }
  if (t.hour == 7) {
    matrix.setIntensity(3);
  }
  if (t.hour == 8) {
    matrix.setIntensity(7);
  }
  if (t.hour == 9) {
    matrix.setIntensity(9);
  }
  if (t.hour == 10) {
    matrix.setIntensity(11);
  }
  if (t.hour == 11) {
    matrix.setIntensity(13);
  }
  if (t.hour == 12) {
    matrix.setIntensity(15);
  }
  if (t.hour == 13) {
    matrix.setIntensity(15);
  }
  if (t.hour == 14) {
    matrix.setIntensity(15);
  }
  if (t.hour == 15) {
    matrix.setIntensity(15);
  }
  if (t.hour == 16) {
    matrix.setIntensity(13);
  }
  if (t.hour == 17) {
    matrix.setIntensity(11);
  }
  if (t.hour == 18) {
    matrix.setIntensity(9);
  }
  if (t.hour == 19) {
    matrix.setIntensity(7);
  }
  if (t.hour == 20) {
    matrix.setIntensity(3);
  }
  if (t.hour == 21) {
    matrix.setIntensity(0);
  }
  if (t.hour == 22) {
    matrix.setIntensity(0);
  }
  if (t.hour == 23) {
    matrix.setIntensity(0);
  }

  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahreheit
  float f = dht.readTemperature(true);
  humedad = h;  //Guardamos la lectura en la cadena.
  temperatura = t;  //Guardamos la lectura en la cadena.

  // Muestreo de la hora.

  tape = rtc.getTimeStr();  // Guardamos la hora en la cadena.

  for (int i = 0; i < 31; i++) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while (x + width - spacer >= 0 && letter >= 0) {
      if (letter < tape.length()) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }
  }
  matrix.write(); // Enviar los datos a la matriz.

  delay(4000);  // Espera para visualizar la hora.

  // Se repite el proceso anterior para mostrar la humedad, el tiempo y la temperatura.

  // Humedad.

  tape = sep + humedad;

  for (int i = 0; i < 30; i++) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while (x + width - spacer >= 0 && letter >= 0) {
      if (letter < tape.length()) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }
  }
  matrix.write();

  delay(1000);

  //tiempo

  tape = rtc.getTimeStr();

  for (int i = 0; i < 31; i++) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while (x + width - spacer >= 0 && letter >= 0) {
      if (letter < tape.length()) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }
  }
  matrix.write();

  delay(4000);

  // Temperatura.

  tape = sep1 + temperatura;

  for (int i = 0; i < 30; i++) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while (x + width - spacer >= 0 && letter >= 0) {
      if (letter < tape.length()) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }
  }
  matrix.write();

  delay(1000);
}

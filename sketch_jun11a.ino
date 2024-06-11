#include <DHT.h>

#define DHTPIN 7     // Pin al que está conectado el sensor DHT22
#define DHTTYPE DHT22   // Tipo del sensor DHT22 (AM2302)

#define TEMP_THRESHOLD 25.0  // Umbral de temperatura para activar la bomba (en grados Celsius)
#define HUM_THRESHOLD 50.0    // Umbral de humedad para activar la bomba (%)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT); // Pin para controlar la bomba
  pinMode(A5, OUTPUT); // Pin para controlar la bomba
  dht.begin();
}

void loop() {  
  // Leer datos de humedad y temperatura
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  // Imprimir valores de temperatura y humedad en el monitor serial
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");

  // Activar la bomba si la temperatura y la humedad superan los umbrales
  if (temp >= TEMP_THRESHOLD && hum < HUM_THRESHOLD) {
    Serial.println("Activando la bomba...");
    digitalWrite(4, HIGH); // Encender la bomba
    delay(3000); // Mantener la bomba activada por 5 segundos
    digitalWrite(4, LOW); // Apagar la bomba
  }

  // Leer desde el puerto serial para activar manualmente la bomba
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'h') {
      Serial.println("Activando la bomba manualmente...");
      digitalWrite(4, HIGH); // Encender la bomba
      delay(3000); // Mantener la bomba activada por 3 segundos
      digitalWrite(4, LOW); // Apagar la bomba
    }
  }
  int brightness = map(hum, 0, 100, 0, 255);
  // Control LED brightness
  analogWrite(A5, brightness);

  delay(10); // Esperar 10 segundos antes de la próxima lectura
  // Map humidity range to LED brightness range (0-255)
  
}

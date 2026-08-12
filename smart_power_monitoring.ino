#define BLYNK_TEMPLATE_ID "TMPL3WHvw15Mi"
#define BLYNK_TEMPLATE_NAME "Smart Motor Monitoring System"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/* ---------------- WIFI ---------------- */
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

/* ---------------- PIN DEFINITIONS ---------------- */
#define currentSensorPin 34
#define voltageSensorPin 32
#define tempSensorPin 4
#define vibrationPin 27
#define motorPin 23   // 🔥 NEW: transistor control pin

/* ---------------- DS18B20 ---------------- */
OneWire oneWire(tempSensorPin);
DallasTemperature sensors(&oneWire);

/* ---------------- CURRENT SENSOR ---------------- */
int offsetValue = 2870;
float sensitivity = 0.100;

/* ---------------- VOLTAGE MULTIPLIER ---------------- */
float voltageMultiplier = 2.0;

/* ---------------- THRESHOLDS ---------------- */
int OFF_MIN = 2860;
int OFF_MAX = 2890;

/* Overload condition */
float OVERLOAD_CURRENT = 2.0;

/* ---------------- FLAGS ---------------- */
bool overloadFlag = false;
bool tempFlag = false;
bool vibFlag = false;

BlynkTimer timer;

/* ===================================================== */
void sendData()
{
  /* ---------------- CURRENT ---------------- */
  long currentSum = 0;
  for (int i = 0; i < 100; i++) {
    currentSum += analogRead(currentSensorPin);
    delay(1);
  }

  int adcCurrent = currentSum / 100;
  int difference = adcCurrent - offsetValue;
  float voltageCurrent = difference * (3.3 / 4095.0);
  float current = voltageCurrent / sensitivity;
  if (current < 0) current = -current;

  /* ---------------- VOLTAGE ---------------- */
  long voltageSum = 0;
  for (int i = 0; i < 50; i++) {
    voltageSum += analogRead(voltageSensorPin);
    delay(1);
  }

  int adcVoltage = voltageSum / 50;
  float voltage = (adcVoltage * (3.3 / 4095.0)) * voltageMultiplier;

  /* ---------------- TEMPERATURE ---------------- */
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  /* ---------------- VIBRATION ---------------- */
  int vibrationState = digitalRead(vibrationPin);

  /* ===================================================== */
  /* ---------------- MOTOR CONTROL LOGIC ---------------- */
  bool motorOn = true;

  if (current > OVERLOAD_CURRENT || temperature > 40 || vibrationState == LOW)
  {
    motorOn = false;   // fault condition → motor OFF
  }

  if (motorOn)
    digitalWrite(motorPin, HIGH);   // transistor ON
  else
    digitalWrite(motorPin, LOW);    // transistor OFF

  /* ---------------- BLYNK SEND ---------------- */
  Blynk.virtualWrite(V0, current);
  Blynk.virtualWrite(V1, voltage);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, vibrationState);

  Blynk.virtualWrite(V4, motorOn ? "MOTOR ON" : "MOTOR OFF");

  /* ---------------- ALERTS ---------------- */
  if (current > OVERLOAD_CURRENT)
  {
    if (!overloadFlag)
    {
      Blynk.logEvent("overload", "⚠ Motor Overload Detected");
      overloadFlag = true;
    }
  }
  else overloadFlag = false;

  if (temperature > 40)
  {
    if (!tempFlag)
    {
      Blynk.logEvent("temp_high", "🔥 High Temperature Alert");
      tempFlag = true;
    }
  }
  else tempFlag = false;

  if (vibrationState == LOW)
  {
    if (!vibFlag)
    {
      Blynk.logEvent("vibration_fault", "⚠ Vibration Fault Detected");
      vibFlag = true;
    }
  }
  else vibFlag = false;

  /* ---------------- SERIAL ---------------- */
  Serial.println("========= MOTOR HEALTH MONITOR =========");

  Serial.print("Current: "); Serial.print(current); Serial.println(" A");
  Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Vibration: "); Serial.println(vibrationState);

  Serial.print("Motor Status: ");
  Serial.println(motorOn ? "ON" : "OFF");

  Serial.println("=======================================");
  Serial.println();
}

/* ===================================================== */
void setup()
{
  Serial.begin(115200);

  sensors.begin();

  pinMode(vibrationPin, INPUT);
  pinMode(motorPin, OUTPUT);

  digitalWrite(motorPin, HIGH); // start motor ON

  WiFi.begin(ssid, pass);
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();

  timer.setInterval(2000L, sendData);
}

/* ===================================================== */
void loop()
{
  Blynk.run();
  timer.run();
}
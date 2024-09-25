#include <Arduino.h>

static const uint8_t LED_PIN = 8U;
static uint8_t count = 0U;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.setDebugOutput(true);
}

void loop()
{
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    Serial.printf("Hello World Tuan: %d\n", count);
    log_i("Hello World LOG: %d", count++);
}
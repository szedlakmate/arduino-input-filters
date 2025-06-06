// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include "InputPipeline.h"

#define TRIGGER_PIN 12    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 13       // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

InputPipeline sonarInput;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.

float sonar_distance = 0.0;

void setup() {
  Serial.begin(115200);                      // Open serial monitor at 115200 baud to see ping results.
  sonarInput.useClampedGuard(10, 100);       // Acceptable range
  sonarInput.useDeadband(2.0);               // Stable unless change exceeds ±2
  sonarInput.useAdaptiveSmoother(0.2, 3.0);  // Smooth flickers within ±3
}

void loop() {
  delay(100);                        // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  sonar_distance = sonar.ping_cm();  // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("Distance [cm] RAW: ");
  Serial.print(sonar_distance);

  if (sonarInput.update(sonar_distance)) {
    float cleanDistance = sonarInput.get();
    Serial.print(" - filtered: ");
    Serial.print(cleanDistance);
  }
  Serial.println();
}
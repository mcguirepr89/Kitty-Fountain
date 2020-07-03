/* Kitty Fountain -- Prototype 1
   Sonar triggered water fountain for the kitties
   07.03.2020 -- Patrick McGuire
*/
#include <NewPing.h>     // Include the Sonar library

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 30  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define PUMP 13          // Relay module's signal pin (controls the water pump)

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int distance = 0;                                   // Declare 'distance' integer variable

void setup() {
  Serial.begin(115200);  // Open serial monitor at 115200 baud to see ping results.
  pinMode(PUMP, OUTPUT); // Set relay module pinMode
}

void loop() {
  delay(100);                        // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping();    // Send ping, get ping time in microseconds (uS).
  distance = (uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.print(distance);            // Print distance in serial monitor
  Serial.println("cm");              // Print distance units in serial monitor

  if ( distance > 1 ) {              // If anyting is in range . . .
    digitalWrite(PUMP, HIGH);        // turn on the water pump
  } else {                           // else, if nothing is in range . . .
    delay(1000);                     // wait one second
    unsigned int uS = sonar.ping();  // check the distance again
    distance = (uS / US_ROUNDTRIP_CM);
    if ( distance == 0 ) {           // if there is STILL nothing in range . . .
      delay(2000);                   // then wait two seconds
      digitalWrite(PUMP, LOW);       // and then turn the pump off
    }
  }
}

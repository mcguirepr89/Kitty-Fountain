/* Kitty Fountain -- Prototype 1
   Sonar triggered water fountain for the kitties
   07.03.2020 -- Patrick McGuire
*/

//Library
#include <NewPing.h>    // Import the library

//Definitions
#define TRIGGER_PIN  12 // Sonar trigger to Arduino pin D12
#define ECHO_PIN     11 // Sonar echo pin to Arduino pin D11
#define MAX_DISTANCE 35 /* Maximum distance to ping in centimeters 
                           (Maximum sensor distance is rated at 400-500cm)*/
#define PUMP         13 // Relay signal pin to Arduino D13

//Sonar setup
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPin setup

//Variable(s)
int distance = 0;       // Declare 'distance' integer variable

//Setup
void setup() {
  Serial.begin(115200);  // Set serial baud rate for monitoring
  pinMode(PUMP, OUTPUT); // Set relay signal pin's pinMode as OUTPUT
}

//Main Loop
void loop() {
  delay(50);                        /* Wait 50ms between pings. 29ms should
                                       be the shortest delay between pings*/
  distance = sonar.ping_cm();       // Set the ping value to 'distance' variable
  Serial.print(distance);           // Print 'distance' value in serial monitor
  Serial.println("cm");             // Print 'distance' units in serial monitor

  if ( distance > 1 ) {             // If anyting is in range . . .
    digitalWrite(PUMP, HIGH);       // turn the pump on
  } else {                          // Else . . .
    delay(50);                      // wait 50ms
    distance = sonar.ping_cm();     // then check the 'distance' variable again
    if ( distance == 0 ) {          // if nothing is in range . . .
      delay(1000);                  // wait 1 second
      distance = sonar.ping();      // then check the 'distance' variable again
      if ( distance == 0 ) {        // if nothing is in range . . .
        delay(1000);                // wait 1 second
        distance = sonar.ping();    // then check the 'distance' variable again
        if ( distance == 0 ) {      // finally, if nothing is in range . . .
          digitalWrite(PUMP, LOW);  // turn the pump off
        }
      }
    }
  }
}

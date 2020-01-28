// Setting input / output pins
const int ledPin = 11;
const int speakerPin = 12;
const int buttonPin = 13;
const int ldrPin = A0;

// Setting variables to keep track of button reading
int state = HIGH;
int reading;
int prev = LOW;
long time = 0;
long debounce = 200;

// Setting pins to INPUT / OUTPUT
void setup(){
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  // If button is pressed and there is a bit of time between button press
  // Swap state variable accordingly and update time
  reading = digitalRead(buttonPin);
  if (reading == HIGH && prev == LOW && millis() - time > debounce){
    if (state == HIGH){
      state = LOW;
    }
    else{
      state = HIGH;
    }
    time = millis();
  }

  // If circuit is turned on...
  if (state == HIGH){
    // Turn on the LED and get reading from the photoresistor
    digitalWrite(ledPin, state);
    int ldrStatus = analogRead(ldrPin);
    Serial.println(ldrStatus);
    // If the readings from photoresistors is relatively high
    if (ldrStatus >= 400){
      // Adjust the pitch accordingly and output it
      int pitch = map(ldrStatus, 400, 1000, 120, 1500);
      tone(speakerPin, pitch, 10);
//    delay(100);
//    Serial.println("AAA");
    }
    // If threshold not reached, ensure that speaker does not sound
    else{
      noTone(speakerPin);
      delay(100);
//      Serial.println("NO LIGHT");
    }
  }
  // Circuit is turned off
  else{
    // Turn off LED and ensure that speaker does not sound
    digitalWrite(ledPin, state);
    noTone(speakerPin);
//    delay(100);
    Serial.println("OFF");
  }
  // Updating time since previous press on button
  prev = reading;
}

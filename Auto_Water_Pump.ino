//NOTE: I'm using the A0 and A5, which are Analog pins as Digital Pins. The only reason is convinience, as putting the cables on that side of the Arduino made it fit better inside the case. 

int input = A0; //Magnetic Sensor In
int output = A5; //Relay Out

int maxSecondsOn = 300; 
int minSecondsOn = 60;

int state = 0;
int secondsOn = 0;


void setup()
{
  pinMode(input, INPUT_PULLUP);
  pinMode(output, OUTPUT); 

  Serial.begin(9600);

  digitalWrite(output, 1);
  delay(500);
  digitalWrite(output, 0);

  Serial.println("Started");
  Serial.print("Min Seconds On:  ");
  Serial.println(minSecondsOn);
  Serial.print("Max Seconds On:  ");
  Serial.println(maxSecondsOn);

}

void loop()
{

  int newState = !digitalRead(input); // The value is inverted (hence the ! sign) because I used the Arduino INPUT_PULLUP. Which means that it's normally HIGH unless the sensor is tripped. 
                                      // This is to avoid introducing an extra resistor into the circuit. 

   Serial.print("Output State: ");
   Serial.print(state);
   Serial.print("  Sensor state: ");
   Serial.print(newState);
   Serial.print("  Seconds On: ");
   Serial.println(secondsOn);

  if(state == 1)
  {
    secondsOn = secondsOn + 1;

    if(secondsOn > maxSecondsOn)
    {
      newState = 0;     
      
    }
    if(secondsOn < minSecondsOn)
        newState = 1;
  }

  if(newState != state) //Status Changed
  {
    Serial.print("Changing Output to ");
    Serial.println(newState);
    state = newState;
    secondsOn = 0;
    digitalWrite(output, state);
  }
  delay(1000);
}

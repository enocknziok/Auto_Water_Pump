int input = A0; //Magnetic Sensor In
int output = A5; //Relay Out

int maxSecondsOn = 120; 
int minSecondsOn = 30;

int state = 1;
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

}

void loop()
{

  int newState = !digitalRead(input);

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

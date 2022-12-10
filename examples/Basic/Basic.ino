#include <Excelsior_Light.h>
Excelsior_Light Lightsensor;                 //takes the portnumbers as the parameters. (Red, Green, Blue, Signal). 
                                             //The signal-pin needs to be an analog pin, the other three can be both analog or digital pins
void setup()
{
  Lightsensor = Excelsior_Light(14,15,16,17);
}

void loop()
{
  Serial.print("White Value: ");
  Serial.print(Lightsensor.read());
  Serial.print("  Green Value: ");
  Serial.print(Lightsensor.read(GREEN));
  Serial.print("  Cyan percent Value: ");
  Serial.print(Lightsensor.read(CYAN, true));
  Serial.println();
}
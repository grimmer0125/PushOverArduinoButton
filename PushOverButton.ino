/*
  ArduinoButton
  Click the button and send an iOS push notification. 
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

#include <Console.h>

int led = 13;
const byte SW = 2;
boolean lastState = LOW;
boolean toggle = LOW;
byte click = 0; 

void postData()
{
  Process p;
  String cmd2 = 
"curl --data \"token=aAArpbLPeVvQqnNp6JVh5kYqN9MdHB&user=uePiGjpFymTtATVtgqcAPkU6oqzPCo&message=sendByArduinoButton\"";

  cmd2 = cmd2 + " http://api.pushover.net/1/messages.json";

  p.runShellCommand(cmd2);
  Console.println(cmd2);
  p.close();
  
}

// the setup routine runs once when you press reset:
void setup() {                
  
  Serial.begin(9600);
  
  // Initialize Console and wait for port to open:
  Bridge.begin();
  Console.begin(); 
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);         
  pinMode(SW, INPUT);
  lastState = digitalRead(SW);  
  
}

// the loop routine runs over and over again forever:
void loop() {
  
  boolean b1= digitalRead(SW);
  
  if (b1 != lastState)
  {
    delay(30);
    boolean b2 = digitalRead(SW);
    if (b1 == b2)
    {
      lastState = b1; 
      click ++;
      //Serial.print("button state is changed");
    }    
  }
  
  if (click ==2)
  {
    click =0;
    toggle = !toggle;
    digitalWrite(led, toggle);
    Serial.print("button has been clicked\n");
    Console.println("button has been clicked, wifi \n");
    Serial.print("try to post\n");
    postData();
    Serial.print("end to post\n");

  }
  
  //digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);               // wait for a second
  //digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);               // wait for a second
  
  //Serial.print(led);
}

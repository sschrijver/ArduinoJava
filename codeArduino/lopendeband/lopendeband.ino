int  updownSnelheid, updown, leftrightSnelheid, leftright, lijnSensorDefault;
String currentTask;
int lijnSensorDetectie = 700;
boolean goLeft;
void setup()
{
  Serial.begin(9600);
  
  updownSnelheid = 5; // omhoog / omlaag: motorsnelheid
  updown = 4; // omhoog / omlaag : motorrichting
  leftrightSnelheid = 6; // links / rechts : motorsnelheid
  leftright = 7; // links / rechts: motorrichting


}

void vanBandEenAf()
{
  while(analogRead(0) <= lijnSensorDetectie)
      {
        //terwijl een pakket wordt gedetecteerdt niks doen.
      }
      delay(1000);//genoeg delay zodat het artikel tijd heeft om van de band af te vallen
      digitalWrite(leftright, HIGH);
      analogWrite(leftrightSnelheid, 0);
}

void leftOrRight()
{
  if(currentTask == "left")
  {
    digitalWrite(updown, HIGH);
    analogWrite(updownSnelheid, 255);
  }
  else if(currentTask == "right"){
    digitalWrite(updown, LOW);
    analogWrite(updownSnelheid, 255);
  }
}

void nextTask()
{
    String recv = Serial.readStringUntil('\n');

    int commaIndex = recv.lastIndexOf(',');
    int tweedeCommaIndex = recv.lastIndexOf(',', commaIndex + 1);

    String currentTask = recv.substring(0, commaIndex);
}

void loop()
{if (Serial.available() > 0)
  {

    
    Serial.println(analogRead(0));
//    digitalWrite (updown, LOW);
//    analogWrite(updownSnelheid, 255);
    digitalWrite(updown, HIGH);
    analogWrite(updownSnelheid, 0);
    nextTask();
    if(currentTask == "empty")//delay van een paar sceonden als een bin moet worden leeg gemaakt.
    {
      delay(10000);
    }else{
  
      digitalWrite (leftright, HIGH);
      analogWrite(leftrightSnelheid, 255);
      
      if(analogRead(0) <= lijnSensorDetectie)
      {
        vanBandEenAf();
        leftOrRight();
        delay(5000);//delay om te wachten tot het artikel in het pakket zit      
      }
    }
  }
}

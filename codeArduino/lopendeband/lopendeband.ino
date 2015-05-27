int  updownSnelheid, updown, leftrightSnelheid, leftright, lijnSensorDefault;
String currentTask;
int lijnSensorDetectie = 760;
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
      if(analogRead(0) <= lijnSensorDetectie)
      {
      delay(1000);//genoeg delay zodat het artikel tijd heeft om van de band af te vallen
      digitalWrite(leftright, HIGH);
      analogWrite(leftrightSnelheid, 0);
      leftOrRight();
      }
      
      else if(analogRead(0) > lijnSensorDetectie)
      {
      digitalWrite(leftright, HIGH);
      analogWrite(leftrightSnelheid,255);
      
      }
}

void leftOrRight()
{
  //if(currentTask == "left")
  
    digitalWrite(updown, HIGH);
    analogWrite(updownSnelheid, 255);
  
//  else if(currentTask == "right"){
//    digitalWrite(updown, LOW);
//    analogWrite(updownSnelheid, 255);
  
}



void loop()
{
    vanBandEenAf();
    
    Serial.println(analogRead(0));
    Serial.println(currentTask);
  
}

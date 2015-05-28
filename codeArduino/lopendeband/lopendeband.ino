int  updownSnelheid, updown, leftrightSnelheid, leftright, lijnSensorDefault;
String currentTask;
int lijnSensorDetectie = 700;
boolean goLeft;
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  updownSnelheid = 5; // omhoog / omlaag: motorsnelheid
  updown = 4; // omhoog / omlaag : motorrichting
  leftrightSnelheid = 6; // links / rechts : motorsnelheid
  leftright = 7; // links / rechts: motorrichting
}

void leftOrRight()
{
  if (currentTask == "left") {

    digitalWrite(updown, HIGH);
    analogWrite(updownSnelheid, 255);
    delay(6000);
    analogWrite(updownSnelheid, 0);
  }
  else if (currentTask == "right") {
    digitalWrite(updown, LOW);
    analogWrite(updownSnelheid, 255);
    delay(6000);
    analogWrite(updownSnelheid, 0);
  }
  else if (currentTask == "newLeft")
  {
    digitalWrite(3, HIGH);
    digitalWrite(updown, LOW);
    analogWrite(updownSnelheid, 0);
    delay(2000);
    Serial.println("Nieuw pakket links");
    while (Serial.available() <= 0)
    {
      // do nothing
    }
    currentTask = Serial.readStringUntil('\n');
    digitalWrite(3, LOW);
    leftOrRight();

  }

  else if (currentTask == "newRight")
  {
    digitalWrite(2, HIGH);
    digitalWrite(updown, LOW);
    analogWrite(updownSnelheid, 0);
    delay(2000);
    Serial.println("Nieuw pakket rechts");
    while (Serial.available() <= 0)
    {
      // do nothing
    }
    currentTask = Serial.readStringUntil('\n');
    digitalWrite(2,LOW);
    leftOrRight();
  }
  
  else {
    // do nothing
  }

}



void loop()
{
  digitalWrite(leftright, HIGH);
  analogWrite(leftrightSnelheid, 255);

  while (analogRead(0) > lijnSensorDetectie)
  {
    // do nothing

  }

  Serial.println("lijn gedetecteerd");

  delay(800);//genoeg delay zodat het artikel tijd heeft om van de band af te vallen
  digitalWrite(leftright, HIGH);
  analogWrite(leftrightSnelheid, 0);

  digitalWrite(leftright, LOW);
  analogWrite(leftrightSnelheid, 255);
  delay(1000);
  digitalWrite(leftright, HIGH);
  analogWrite(leftrightSnelheid, 0);

  while (Serial.available() <= 0)
  {
    // do nothing
  }
  currentTask = Serial.readStringUntil('\n');
  leftOrRight();


}

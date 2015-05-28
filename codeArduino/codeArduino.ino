#include <Servo.h> // Servo include

int xActie, yActie, updownSnelheid, updown, leftrightSnelheid, leftright, lijnSensorWaarde, lijnenGeteld;
int lijnSensorDetectie = 500;
int lijnSensor2Detectie = 400;
int motorSnelheid1 = 150;
int motorSnelheid2 = 150;
int grijpDelay = 800;
String recv;

Servo myservo;  // variabele voor servo
int pos = 0;   // default servo positie

void setup()
{
  Serial.begin(9600);
  updownSnelheid = 5; // omhoog / omlaag: motorsnelheid
  updown = 4; // omhoog / omlaag : motorrichting
  leftrightSnelheid = 6; // links / rechts : motorsnelheid
  leftright = 7; // links / rechts: motorrichting

  myservo.attach(13); // Servo op pin 9

  pinMode(12, OUTPUT);


}

int lijnTellerLinksRechts(int i)
{
  while (analogRead(0) >= lijnSensorDetectie && analogRead(0) != 1023 && lijnenGeteld < i)
  {
    lijnenGeteld++;
    int tachtig = 80;

    if (lijnenGeteld < i)
    {
      while (analogRead(0) > tachtig)
      {
        // do nothing
      }
    }

  }

  return lijnenGeteld;
}

int lijnTellerOmhoogOmlaag(int i)
{
  while (analogRead(1) >= lijnSensor2Detectie && analogRead(1) != 1023 && lijnenGeteld < i)
  {
    lijnenGeteld++;
    int honderd = 100;


    if (lijnenGeteld < i)
    {
      while (analogRead(1) > honderd)
      {
        // do nothing
      }
    }

  }

  return lijnenGeteld;
}

void bovenOnder(int i)
{
  int honderd = 100;
  if (i < 0)
  {
    // Motor omhoog
    digitalWrite (updown, LOW);
    analogWrite(updownSnelheid, motorSnelheid2);
    lijnenGeteld = 0;

    if (analogRead(1) > honderd)
    {
      while (analogRead(1) > honderd)
      {
        // do nothing
      }
    }

    while (lijnenGeteld < abs(i))
    {
      lijnTellerOmhoogOmlaag(abs(i));
    }
    analogWrite(updownSnelheid, 0);
  }
  else if (i > 0)
  {
    // Motor omlaag
    digitalWrite (updown, HIGH);
    analogWrite(updownSnelheid, 100);

    lijnenGeteld = 0;

    if (analogRead(1) > honderd)
    {
      while (analogRead(1) > honderd)
      {
        // do nothing
      }
    }


    while (lijnenGeteld < i)
    {
      lijnTellerOmhoogOmlaag(i);
    }
    analogWrite(updownSnelheid, 0);
  }
  else
  {
    // Motor omhoog omlaag uit!
    analogWrite(updownSnelheid, 0);
  }
}

void linksRechts(int i)
{
  int tachtig = 80;
  if (i < 0)
  {
    // Motor naar links
    digitalWrite (leftright, LOW);
    analogWrite(leftrightSnelheid, motorSnelheid1);

    lijnenGeteld = 0;


    if (analogRead(0) > tachtig)
    {
      while (analogRead(0) > tachtig)
      {
        // do nothing
      }
    }

    while (lijnenGeteld < abs(i))
    {
      lijnTellerLinksRechts(abs(i));
    }
    digitalWrite (leftright, HIGH);
    analogWrite(leftrightSnelheid, 0);
  }
  else if (i > 0)
  {

    // Motor naar rechts
    digitalWrite (leftright, HIGH);
    analogWrite(leftrightSnelheid, motorSnelheid1);

    lijnenGeteld = 0;


    if (analogRead(0) > tachtig)
    {
      while (analogRead(0) > tachtig)
      {
        // do nothing
      }
    }

    while (lijnenGeteld < i)
    {
      lijnTellerLinksRechts(i);
    }
    digitalWrite (leftright, HIGH);
    analogWrite(leftrightSnelheid, 0);
  }
  else
  {
    // Motor links rechts uit!
    analogWrite(updownSnelheid, 0);
  }
}
void pak()
{
  myservo.write(0);
  delay(600);
  myservo.write(100);
}
void terug()
{
  myservo.write(180);
  delay(600);
  myservo.write(100);
}

void dropOpBand()
{
  myservo.write(0);
  delay(1000);
  myservo.write(100);
}
void terugVanBand()
{
  myservo.write(180);
  delay(1300);
  myservo.write(100);
}

void loop()
{
  myservo.write(100);
  if (Serial.available() > 0)
  {
    recv = Serial.readStringUntil('\n');
    if (recv == "drop")
    {
      linksRechts(-1);

      // Motor omhoog
      digitalWrite (updown, LOW);
      analogWrite(updownSnelheid, motorSnelheid2);
      delay(1300);
      analogWrite(updownSnelheid, 0);

      dropOpBand();

      bovenOnder(1);

      terugVanBand();

      linksRechts(1);
    }

    else if (recv == "startpositie")
    {
      Serial.println("done");
      while (Serial.available() == 0)
      {
        // do nothing
      }
      recv = Serial.readStringUntil('\n');
      int commaIndex = recv.lastIndexOf(',');
      int tweedeCommaIndex = recv.lastIndexOf(',', commaIndex + 1);

      String eersteWaarde = recv.substring(0, commaIndex);
      String tweedeWaarde = recv.substring(commaIndex + 1  );

      xActie = eersteWaarde.toInt();
      yActie = tweedeWaarde.toInt();

      linksRechts(xActie);

      bovenOnder(yActie);
    }

    else
    {
      int commaIndex = recv.lastIndexOf(',');
      int tweedeCommaIndex = recv.lastIndexOf(',', commaIndex + 1);

      String eersteWaarde = recv.substring(0, commaIndex);
      String tweedeWaarde = recv.substring(commaIndex + 1  );

      xActie = eersteWaarde.toInt();
      yActie = tweedeWaarde.toInt();

      linksRechts(xActie);

      bovenOnder(yActie);

      pak();

      // Motor omhoog
      digitalWrite (updown, LOW);
      analogWrite(updownSnelheid, motorSnelheid2);
      delay(1350);
      analogWrite(updownSnelheid, 0);

      terug();

      bovenOnder(1);
    }
    Serial.println("done");
  }

}

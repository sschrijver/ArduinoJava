int xActie, yActie, updownSnelheid, updown, leftrightSnelheid, leftright, lijnSensorWaarde, lijnenGeteld;
int lijnSensorDetectie = 700;
int lijnSensorDefault = 100;
int x = 0;
int y = 4;

void setup()
{
  Serial.begin(9600);
  updownSnelheid = 5; // omhoog / omlaag: motorsnelheid
  updown = 4; // omhoog / omlaag : motorrichting
  leftrightSnelheid = 6; // links / rechts : motorsnelheid
  leftright = 7; // links / rechts: motorrichting


}

int lijnTeller(int i)
{
  Serial.println(analogRead(0));

  while (analogRead(0) >= lijnSensorDetectie && analogRead(0) != 1023 && lijnenGeteld < i)
  {
    Serial.println(analogRead(0));
    lijnenGeteld++;
    Serial.println("plus een");
    Serial.println(lijnenGeteld);
    Serial.println(analogRead(0));

    if (lijnenGeteld < i)
    {
      while (analogRead(0) >= lijnSensorDefault)
      {
        // do nothing
      }
    }

  }

  return lijnenGeteld;
}

void bovenOnder(int i)
{
  if (i < 0)
  {
    // Motor omhoog
    digitalWrite (updown, HIGH);
    analogWrite(updownSnelheid, 255);
    lijnenGeteld = 0;

    while (lijnenGeteld < abs(i))
    {
      lijnTeller(abs(i));
    }
    analogWrite(updownSnelheid, 0);
    y = y - abs(i);
  }
  else if (i > 0)
  {
    // Motor omlaag
    digitalWrite (updown, LOW);
    analogWrite(updownSnelheid, 255);

    lijnenGeteld = 0;
    while (lijnenGeteld < i)
    {
      lijnTeller(i);
    }
    analogWrite(updownSnelheid, 0);
    y = y + i;
  }
  else
  {
    // Motor omhoog omlaag uit!
    analogWrite(updownSnelheid, 0);
  }
}

void linksRechts(int i)
{
  if (i < 0)
  {
    // Motor naar links
    digitalWrite (leftright, LOW);
    analogWrite(leftrightSnelheid, 255);

    lijnenGeteld = 0;
    while (lijnenGeteld < abs(i))
    {
      lijnTeller(abs(i));
    }
    digitalWrite (leftright, HIGH);
    analogWrite(leftrightSnelheid, 0);
    x = x - abs(i);
  }
  else if (i > 0)
  {

    // Motor naar rechts
    digitalWrite (leftright, HIGH);
    analogWrite(leftrightSnelheid, 255);

    lijnenGeteld = 0;
    while (lijnenGeteld < i)
    {
      lijnTeller(i);
    }
    digitalWrite (leftright, HIGH);
    analogWrite(leftrightSnelheid, 0);
    x = x + i;
  }
  else
  {
    // Motor links rechts uit!
    analogWrite(updownSnelheid, 0);
  }
}

void loop()
{

  if (Serial.available() > 0)
  {
    String recv = Serial.readStringUntil('\n');
    int commaIndex = recv.lastIndexOf(',');
    int tweedeCommaIndex = recv.lastIndexOf(',', commaIndex + 1);

    String eersteWaarde = recv.substring(0, commaIndex);
    String tweedeWaarde = recv.substring(commaIndex + 1  );

    xActie = eersteWaarde.toInt();
    yActie = tweedeWaarde.toInt();

    linksRechts(xActie);

    bovenOnder(yActie);

    Serial.println("Gepakt!");
  }

  bovenOnder(-4);
  linksRechts(-3);
  delay(100000);
}

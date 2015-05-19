int xActie, yActie, updownSnelheid, updown, leftrightSnelheid, leftright, lijnSensorWaarde, lijnenGeteld;
int lijnSensorDetectie = 700;
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

int lijnTeller()
{
  lijnSensorWaarde = analogRead(0);
  
  Serial.println(lijnSensorWaarde);
  

  while (lijnSensorWaarde >= lijnSensorDetectie)
  {
    lijnenGeteld++;
    Serial.println("plus een");
    Serial.println(lijnSensorWaarde);
    delay(1000);
  }
  return lijnenGeteld;
}

void bovenOnder(int i)
{
  if (i < 0)
  {
    // Motor omhoog
    digitalWrite (updown, HIGH);
    analogWrite(updownSnelheid, 150);
    lijnenGeteld = 0;

    while (lijnenGeteld < abs(i))
    {
    lijnTeller(); 
    
      // do nothing
    }
    analogWrite(updownSnelheid, 0);
    y = y - abs(i);
  }
  else if (i > 0)
  {
    // Motor omlaag
    digitalWrite (updown, LOW);
    analogWrite(updownSnelheid, 150);
    y = y + i;
  }
  else
  {
    // Motor omhoog omlaag uit!
    analogWrite(updownSnelheid, 150);
  }
}

void linksRechts(int i)
{
  if (i < 0)
  {
    // Motor naar links
    digitalWrite (leftright, HIGH);
    analogWrite(leftrightSnelheid, 150);
    x = x - abs(i);
  }
  else if (i > 0)
  {

    // Motor naar rechts
    digitalWrite (leftright, LOW);
    analogWrite(leftrightSnelheid, 150);
    x = x + i;
  }
  else
  {
    // Motor links rechts uit!
    analogWrite(updownSnelheid, 150);
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
  bovenOnder(-3);
}

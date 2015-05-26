int xActie, yActie, updownSnelheid, updown, leftrightSnelheid, leftright, lijnSensorWaarde, lijnenGeteld;
int lijnSensorDetectie = 600;
int lijnSensor2Detectie = 600;
int lijnSensorDefault = 300;
int lijnSensor2Default = 300;
int motorSnelheid1 = 150;
int motorSnelheid2 = 150;
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

int lijnTellerLinksRechts(int i)
{
//  Serial.println(analogRead(0));

  while (analogRead(0) >= lijnSensorDetectie && analogRead(0) != 1023 && lijnenGeteld < i)
  {
//    Serial.println(analogRead(0));
    lijnenGeteld++;
//    Serial.println("plus een");
//    Serial.println(lijnenGeteld);

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

int lijnTellerOmhoogOmlaag(int i)
{
//  Serial.println(analogRead(1));

  while (analogRead(1) >= lijnSensor2Detectie && analogRead(1) != 1023 && lijnenGeteld < i)
  {
    Serial.print("Waarde: ");
    Serial.println(analogRead(1));
    lijnenGeteld++;
    Serial.println("+1");
    Serial.println(lijnenGeteld);

    if (lijnenGeteld < i)
    {
      while (analogRead(1) >= lijnSensor2Default)
      {
        Serial.print("Waarde te hoog, waarde is ");
        Serial.print(analogRead(1)); 
        Serial.print(", dat is hoger dan ");
        Serial.println(lijnSensor2Default);        // do nothing
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
    digitalWrite (updown, LOW);
    analogWrite(updownSnelheid, motorSnelheid2);
    lijnenGeteld = 0;
    if (analogRead(1) > lijnSensor2Detectie)
    {
      while (analogRead(1) > lijnSensor2Detectie)
      {
        // do nothing
      }
    }

    while (lijnenGeteld < abs(i))
    {
      lijnTellerOmhoogOmlaag(abs(i));
    }
    analogWrite(updownSnelheid, 0);
    y = y - abs(i);
  }
  else if (i > 0)
  {
    // Motor omlaag
    digitalWrite (updown, HIGH);
    analogWrite(updownSnelheid, 80);

    lijnenGeteld = 0;

    if (analogRead(1) > lijnSensorDetectie)
    {
      while (analogRead(1) > lijnSensor2Detectie)
      {
        // do nothing
      }
    }


    while (lijnenGeteld < i)
    {
      lijnTellerOmhoogOmlaag(i);
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
    analogWrite(leftrightSnelheid, motorSnelheid1);

    lijnenGeteld = 0;

    if (analogRead(0) > lijnSensorDetectie)
    {
      while (analogRead(0) > lijnSensorDetectie)
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
    x = x - abs(i);
  }
  else if (i > 0)
  {

    // Motor naar rechts
    digitalWrite (leftright, HIGH);
    analogWrite(leftrightSnelheid, motorSnelheid1);

    lijnenGeteld = 0;

    if (analogRead(0) > lijnSensorDetectie)
    {
      while (analogRead(0) > lijnSensorDetectie)
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
  delay(5000);
  Serial.println(analogRead(1));
  
  linksRechts(4);
  bovenOnder(-4);
  delay(1000);
  linksRechts(-4);
  bovenOnder(4);
  delay(1000);
  linksRechts(4);
  bovenOnder(-4);
  delay(1000);
  linksRechts(-4);
  bovenOnder(4);
  delay(5000);
}

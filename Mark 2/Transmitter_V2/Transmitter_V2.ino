#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins

const int SW_pin = 2;
int joyX = A0;
int joyY = A1;
int x, y;
int x1 = 90, y1 = 90, z1 = 90, value = 90;

const byte address[6] = "10101";

void setup()
{
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(address);

  Serial.begin(9600);
  pinMode(SW_pin, INPUT);

  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
}

void loop()
{
  x = analogRead(joyX);
  y = analogRead(joyY);
  value = analogRead(A3);
  x = map(x, 0, 1023, 135, 670);
  y = map(y, 0, 1023, 135, 670);
  value = map(value, 0, 1023, 0, 360);

  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print("\n");

  int y2 = digitalRead(3);
  if (y2 == HIGH ) y1++;

  if (digitalRead(4) == HIGH ) y1--;

  if (digitalRead(5) == HIGH ) x1++;

  if (digitalRead(6) == HIGH ) x1--;

  if (digitalRead(7) == HIGH ) z1++;

  if (digitalRead(8) == HIGH ) z1--;


  int data[7] = {x, y, x1, y1, z1, 100, value};

  radio.write(data, sizeof(data));
  delay(50);
}
// put your main code here, to run repeatedly:

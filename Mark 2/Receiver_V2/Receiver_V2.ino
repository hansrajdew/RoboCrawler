#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_MIN 200 
#define SERVO_MAX 500 

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
RF24 radio(7, 8); // CE, CSN pins

const byte address[6] = "10101";

void setup()
{
    Serial.begin(9600);

    pwm.begin();
    pwm.setPWMFreq(60);

    radio.begin();
    radio.setPALevel(RF24_PA_MAX);
    radio.openReadingPipe(0, address);
    radio.startListening();
    delay(100);
}

void loop()
{

    while (radio.available() == 0)
    {
    } 
    int x, y, data[7];
    digitalWrite(LED_BUILTIN, HIGH);
    radio.read(data, sizeof(data));
    x = data[0];
    y = data[1];

    Serial.print(x);

    pwm.setPWM(0, 0, x);
    pwm.setPWM(2, 0, x);
    pwm.setPWM(4, 0, x);

    pwm.setPWM(8, 0, y);
    pwm.setPWM(10, 0, y);
    pwm.setPWM(12, 0, y);

    moveToAngle(data[2], data[3], data[4], data[5],data[6]);

    digitalWrite(LED_BUILTIN, LOW);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.print(data[2]);
    Serial.print(" ");
    Serial.print(data[3]);
    Serial.print(" ");
    Serial.print(data[4]);
    Serial.print("\n");

    delay(50);
}

void moveToAngle(double t1, double t2, double t3,double t4,double t5)
{
    t1 = map(t1, 0, 180, SERVO_MIN, SERVO_MAX);
    t2 = map(t2, 0, 180, SERVO_MIN, SERVO_MAX);
    t3 = map(t3, 0, 180, SERVO_MIN, SERVO_MAX);
    t4 = map(t4, 0, 180, SERVO_MIN, SERVO_MAX);
    t5 = map(t5, 0, 180, SERVO_MIN, SERVO_MAX);
    pwm.setPWM(14, 0, t5);
    pwm.setPWM(5, 0, t1);
    pwm.setPWM(6, 0, t2);
    pwm.setPWM(13, 0, t3);
    pwm.setPWM(15, 0, t4);
}



double mod(double x)

{
    if (x < 0)
        return 180 + x;
    else
        return x;
}

void moveToPos(int x, int y, int z)
{
    double b = atan(1.0 * y / x) * (180 / 3.1415); // base angle
    
    b = mod(b);

    double l = sqrt(1.0 * x * x + y * y); // x and y extension

    double h = sqrt(1.0 * l * l + z * z);

    double phi = atan(1.0 * z / l) * (180 / 3.1415);

    phi = mod(phi);
    
    double theta = acos((1.0 * h / 2) / 120) * (180 / 3.1415);
    
    theta = mod(theta);
    
    double a1 = (phi + theta);     // angle for the first part of the arm
    
    double a2 = (180 - 2 * theta); // angle for the second part of the arm
    
    Serial.print(" ");
    Serial.print(b);
    Serial.print(" ");
    Serial.print(a1);
    Serial.print(" ");
    Serial.print(a2);
    moveToAngle(b, a1, a2,90,90);
}

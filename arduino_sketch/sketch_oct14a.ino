#include <Firmata.h>
#include <Servo.h>

Servo servo8;
Servo servo9;
Servo servo10;
Servo servo11;



void analogWriteCallback(byte pin, int value)
{
if(pin == 8) {
servo8.write(value);
}

if(pin == 9) {
servo9.write(value);
}

if(pin == 10) {
servo10.write(value);
}

if(pin == 11) {
servo11.write(value);
}

}

void setup()
{
Firmata.setFirmwareVersion(0, 2);
Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);

servo8.attach(8);
servo9.attach(9);
servo10.attach(10);
servo11.attach(11);

Firmata.begin(9600);
}

void loop()
{
while(Firmata.available())
Firmata.processInput();
}

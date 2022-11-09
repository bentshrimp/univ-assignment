#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 0 // Potentiometer at Pin A0
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define LED 9
#define _EMA_ALPHA 0.8

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

Servo myservo;
unsigned long last_loop_time;   // unit: msec
float dist_ema;

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 1);
  
  Serial.begin(57600);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;
  float dist_raw;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  a_value = analogRead(PIN_POTENTIOMETER);
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
  dist_raw = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;
  if (dist_raw < 100){
    dist_raw = 90;
  } else if (dist_raw > 250){
    dist_raw = 260;
  }
  // we need distance range filter here !!!
  // we need EMA filter here !!!
  dist_ema = dist_raw * _EMA_ALPHA + (1-_EMA_ALPHA) * dist_ema;

  if (100 < dist_ema && dist_ema < 250){
    digitalWrite(LED, 0);
  } else {
    digitalWrite(LED, 1);
  }

  // map distance into duty
//  duty = map(a_value, 0, 1023, _DUTY_MIN, _DUTY_MAX);
  duty = (_DUTY_MAX - _DUTY_MIN)/150.0 * (dist_ema - 100.0) + 553;
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("ADC Read: "); Serial.print(a_value);
  Serial.print(" = ");
  Serial.print((a_value / 1024.0) * 5.0);
  Serial.print(" dist_raw: "); Serial.print(dist_raw);
  Serial.print(" dist_ema: "); Serial.print(dist_ema);
  Serial.print(" Volt => Duty : ");
  Serial.print(duty);
  Serial.println("usec");
}

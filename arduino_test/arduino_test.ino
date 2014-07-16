//motor pulse time
#define MOTOR_TIME 3000

//pin definitions
#define PWM_WHITE 3
#define PWM_BLACK 1
#define PWM_RED 2

void setup()
{
  //configure pin modes
  pinMode(PWM_WHITE,OUTPUT);
  pinMode(PWM_BLACK,OUTPUT);
  pinMode(PWM_RED,OUTPUT);
  
  //configure constant states
  digitalWrite(PWM_BLACK,LOW);  //set to ground
  digitalWrite(PWM_RED,HIGH);   //set to +5 volts
}

//called repeatedly
void loop()
{
  //change motor speed based on sine curve
  analogWrite(PWM_WHITE,(int)(127.0 * sin(2.0 * PI *(millis() % MOTOR_TIME) / MOTOR_TIME) + 127));
}

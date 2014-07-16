#define PWM_WHITE 3
#define PWM_RED 4
#define PWM_BLACK 5

//Jaguar PWM definitions
#define PWM_MIN 1
#define PWM_NEUTRAL 47
#define PWM_MAX 73

#define POTENTIOMETER A0
#define DIR_FWD 7
#define DIR_REV 8

void setup()
{
  //configure pin modes
  pinMode(PWM_WHITE,OUTPUT);
  pinMode(PWM_BLACK,OUTPUT);
  pinMode(PWM_RED,OUTPUT);
  pinMode(POTENTIOMETER,INPUT);
  pinMode(DIR_FWD,INPUT_PULLUP);
  pinMode(DIR_REV,INPUT_PULLUP);
  
  //configure constant states
  digitalWrite(PWM_BLACK,LOW);  //set to ground
  digitalWrite(PWM_RED,HIGH);   //set to +5 volts
  
  /*
   * Set TCCR2B (Timer/Counter Control Register 2B), clock divisor bits to 0x6.
   * which changes PWM frequency on pins 3 & 11 to approx 122 Hz. Necessary
   * for Jaguar motor controller, as 122 Hz = 8 msec period = within Jaguar's range.
   *
   * Jaguar PWM parameters:
   * Servo signal period: 5 - 29 ms
   * Minimum pulse width: .67 ms = 1
   * Maximum pulse width: 2.33 ms = 73
   * Neutral pulse width: 1.5 ms = 47
   */
  TCCR2B = (TCCR2B & 0xF8) | 0x06;
  
  Serial.begin(9600);
}

void loop()
{
  //0 - 1023 (from ADC)
  int pot = analogRead(POTENTIOMETER);
  
  int pwm = 0; //holds pwm value converted from pot value
  
  //HIGH = 5V, LOW = Ground (0 V)
  if(digitalRead(DIR_FWD) == LOW)
  {
    //map: uses a proportion to map a value from one range to another
    //map(value to map, low1, high1, low2, high2)
    pwm = map(pot,0,1024,PWM_NEUTRAL,PWM_MAX);
  }else if(digitalRead(DIR_REV) == LOW)
  {
    pwm = map(pot,0,1024,PWM_NEUTRAL,PWM_MIN);
  }
  
  analogWrite(PWM_WHITE,pwm);
}

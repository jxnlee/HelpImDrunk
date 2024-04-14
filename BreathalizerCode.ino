const int breath_pin = A0;
const int button_pin = 2;
const int breathe_led_pin = 13;
const int calibrate_led_pin = 12;
const int record_duration = 5;
const int calibrate_duration = 2;
int breath_level;
int base_reading;
int button_state = 0;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(breath_pin, INPUT);
  pinMode(button_pin, INPUT);
  pinMode(breathe_led_pin, OUTPUT);
  pinMode(calibrate_led_pin, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  button_state = digitalRead(button_pin);
  if(button_state == HIGH)
  {
    record_breath();
  }
  
}

void record_breath()
{
  int highest_input = 0;
  double calibration = 0.0;
  digitalWrite(calibrate_led_pin, HIGH);
  for( int j = 0; j < calibrate_duration * 500; j++ )
  {
    calibration += (analogRead(breath_pin) / 100);
    delay(2);
  }
  calibration = calibration / (calibrate_duration*5);
  Serial.println(calibration);
  digitalWrite(calibrate_led_pin, LOW);
  digitalWrite(breathe_led_pin, HIGH);
  for( int i = 0; i < record_duration * 500; i++)
  {
    int breath_reading = analogRead(breath_pin);
    if(breath_reading > highest_input)
    {
      highest_input = breath_reading;
    }
    delay(2);
  }
  digitalWrite(breathe_led_pin, LOW);
  Serial.println(highest_input);
}

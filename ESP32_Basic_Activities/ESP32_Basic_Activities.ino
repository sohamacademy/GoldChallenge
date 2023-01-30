#define BLINK_LED 13
#define LED_PIN 5
#define BUTTON_PIN  18
#define BLINKING_SPEED 1000
#define FLOWING_SPEED 150
#define FLOWING_LED1 14
#define FLOWING_LED2 27
#define FLOWING_LED3 26
#define FLOWING_LED4 25

boolean blink_led_state = LOW;
boolean led_state = LOW;
int button_state;
int last_button_state;
int previousButtonState = LOW;
unsigned long previousMillis = 0;
unsigned long previousMillisFL = 0;
int count = 0 ;
boolean forward =  true;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BLINK_LED, OUTPUT);
  pinMode(FLOWING_LED1,OUTPUT);
  pinMode(FLOWING_LED2,OUTPUT);
  pinMode(FLOWING_LED3,OUTPUT);
  pinMode(FLOWING_LED4,OUTPUT);
  button_state = digitalRead(BUTTON_PIN);
}

void loop() {
  unsigned long currentMillisFL = millis();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= BLINKING_SPEED) {
    blink_led_state = (blink_led_state == LOW) ? HIGH : LOW;
    digitalWrite(BLINK_LED, blink_led_state);
    previousMillis = currentMillis;
  }
  if (currentMillisFL - previousMillisFL >= FLOWING_SPEED) {
    Serial.println("count " + String(count));
    previousMillisFL = currentMillisFL;
    if(forward){
      if(count == 0){
        digitalWrite(FLOWING_LED1, HIGH);
        count = 1;
      }
      else if(count == 1){
       digitalWrite(FLOWING_LED2, HIGH);
       count = 2;
      }
      else if(count == 2){
       digitalWrite(FLOWING_LED3, HIGH);
       count = 3;
      }
      else if(count == 3){
       digitalWrite(FLOWING_LED4, HIGH);
       count = 0; 
       forward = false ;
      } 
    }
    else if(!forward){
        if(count == 0){
        digitalWrite(FLOWING_LED1, LOW);
        count = 1;
      }
      else if(count == 1){
       digitalWrite(FLOWING_LED2, LOW);
       count = 2;
      }
      else if(count == 2){
       digitalWrite(FLOWING_LED3, LOW);
       count = 3;
      }
      else if(count == 3){
       digitalWrite(FLOWING_LED4, LOW);
       count = 0; 
       forward = true ;
      } 
    }
  } 
  last_button_state = button_state;
  button_state = digitalRead(BUTTON_PIN);
  if (last_button_state == HIGH && button_state == LOW) {
    Serial.println("The button is pressed");
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
  }
}

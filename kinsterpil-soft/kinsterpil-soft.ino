#include <RC5.h>

#define IR_PIN        2 
#define RELAY_1_PIN   3 
#define RELAY_2_PIN   4
#define baudrate      9600

void relay_on(int relay_pin);
void relay_off(int relay_pin);
void relay_toogle(int number);

unsigned char ir_address=0;
unsigned char ir_toggle=0;
unsigned char ir_command=0;

RC5 rc5(IR_PIN);
  
void setup() {
  Serial.begin(baudrate);
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  digitalWrite(RELAY_1_PIN,HIGH);
  digitalWrite(RELAY_2_PIN,HIGH);
  pinMode(IR_PIN, INPUT);

}

void loop(){
  if(rc5.read(&ir_toggle, &ir_address, &ir_command)){
    Serial.print("\nTest ");
    Serial.print(ir_command);
    relay_toogle(RELAY_1_PIN);
  }
}

void relay_on(int relay_pin){
  digitalWrite(relay_pin,LOW);
}

void relay_off(int relay_pin){
  digitalWrite(relay_pin,HIGH);
}

void relay_toogle(int relay_pin){
  if (digitalRead(relay_pin) == HIGH) {
    digitalWrite(relay_pin, LOW); 
  }
  else { 
    digitalWrite(relay_pin, HIGH); 
  }
}

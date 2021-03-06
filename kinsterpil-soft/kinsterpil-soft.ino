#include <RC5.h>

#define IR_PIN        2
#define RELAY_1_PIN   3
#define RELAY_2_PIN   4
#define baudrate      9600

#define COMMAND_FOR_RELAY_1 13
#define COMMAND_FOR_RELAY_2 13 //nieuzywany rugi kanal 

void relay_on(int relay_pin);
void relay_off(int relay_pin);
void relay_toogle(int number);

unsigned char ir_address = 0;
unsigned char ir_toggle = 0;
unsigned char ir_command = 0;
unsigned int ir_delay = 250; //czas (ms) blokady miedzy kolejnymi odbiorami 

RC5 rc5(IR_PIN);
  
void setup() {
  Serial.begin(baudrate);
  digitalWrite(RELAY_1_PIN,LOW);
  digitalWrite(RELAY_2_PIN,LOW);
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
}

void loop(){
  if(rc5.read(&ir_toggle, &ir_address, &ir_command)){
    Serial.print(ir_command);
    if (ir_command == COMMAND_FOR_RELAY_1){
      ir_command = 0;
      relay_toogle(RELAY_1_PIN);
      Serial.write("\nOdebrana komenda: ");
      Serial.write(COMMAND_FOR_RELAY_1);
      delay(ir_delay);
    }
    if (ir_command == COMMAND_FOR_RELAY_2){
      ir_command = 0;
      relay_toogle(RELAY_2_PIN);
      Serial.write("Odebrana komenda: ");
      Serial.write(COMMAND_FOR_RELAY_2);
      Serial.write("\n" );
      delay(ir_delay);
    }
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

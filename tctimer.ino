#include <Button.h>
#include <Led.h>
#define GATES_PIN 3
//#define GATES_PIN 6

#define TRACK_PIN1 4
#define TRACK_PIN2 5
#define TRACK_PIN3 6

const unsigned int LED_PINS[]={14,15,16};

Button b_gates(GATES_PIN);
Button b_track1(TRACK_PIN1);
Button b_track2(TRACK_PIN2);
Button b_track3(TRACK_PIN3);

Led led_track1(LED_PINS[0]);
Led led_track2(LED_PINS[1]);
Led led_track3(LED_PINS[2]);

unsigned long timer;
//bool start_open;

void ledsOn(){
  led_track1.on();
  led_track2.on();
  led_track3.on();
  };
void ledsOff(){
  led_track1.off();
  led_track2.off();
  led_track3.off();
  };

void setup() {
	b_gates.begin();
	while (!Serial) { }; // Enable serial
	Serial.begin(9600);
  ledsOn();
  delay(100);
  ledsOff();
  //start_open=false;
  }

void track(byte track_num, unsigned long t){
  unsigned long lap_time(millis()-timer);
  unsigned long seconds = lap_time / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  unsigned long days = hours / 24;
  if (timer != 0){
    lap_time %= 1000;
    seconds %= 60;
    minutes %= 60;
    hours %= 24;
    Serial.print(track_num);
    Serial.print(": ");
    Serial.print(hours);Serial.print(":");Serial.print(minutes);Serial.print(":");Serial.print(seconds);Serial.print(".");Serial.println(lap_time);
    }
    else{
      Serial.print("Err:Start");Serial.println(track_num);
    };
  };

void loop() {
	if (b_gates.toggled()) {
		if (b_gates.read() == Button::PRESSED)
			{
        timer=millis();
        ledsOn();
        Serial.println("Start:Open");
			}
		else 
			{
      ledsOn();
      delay(100);
      ledsOff();
			Serial.println("Start:Closed");
      timer=0;
			}
    }
  if (b_track1.pressed()){
      track(0,millis());
      led_track1.off();
    };
  if (b_track2.pressed()){
      track(1,millis());
      led_track2.off();
    };
  if (b_track3.pressed()){
      track(2,millis());
      led_track3.off();
    };
}

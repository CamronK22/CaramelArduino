// New commands go under loop()

#include "SoftwareSerial.h"

const int btPwrPin = 8;
SoftwareSerial bt(2, 3); // TX/RX pins
const int btKeyPin = 4;
const int spkrPin = 5;
const int doorForward = 6;
const int doorReverse = 7;
 
void setup()  {
  	Serial.begin(38400);
  	bt.begin(9600);
  	
  	pinMode(btPwrPin, OUTPUT);
  	pinMode(btKeyPin, OUTPUT);
  	digitalWrite(btPwrPin, HIGH);
  	pinMode(spkrPin, OUTPUT);
  	pinMode(doorForward, OUTPUT);
  	pinMode(doorReverse, OUTPUT);
}

// Main commands
void help() {
	print("Commands:");
	print("help - opens this menu");
	print("open - opens door");
	print("close - closes door");
	print("alert - plays alert noise");
}

void openDoor() {
	print("Opening door...");
	
	buzz(165);
	buzz(165);
	buzz(165);
	buzz(300);
	
	digitalWrite(doorForward, HIGH);
	delay(3000);
	digitalWrite(doorForward, LOW);
	
	print("Door openend successfully!");
}

void closeDoor() {
	print("Closing door...");
	
	buzz(165);
	buzz(165);
	buzz(165);
	buzz(100);
	
	digitalWrite(doorReverse, HIGH);
	delay(3000);
	digitalWrite(doorReverse, LOW);
	
	print("Door closed successfully!");
}

void alert() {
	print("Alerting...");
	
	buzz(NOTE_C6);
	buzz(NOTE_C6);
	buzz(NOTE_C6);
	buzz(NOTE_C6);
	
	print("Successfully alerted.");
}

// Helper methods

void print(String s) {
	Serial.println(s);
    bt.println(s);
}

void buzz(int pitch) {
	tone(spkrPin, pitch, 250);
	delay(250);
	noTone(spkrPin);
	delay(5);
}

String getMessage() {
  	String msg = "";
  	char a;
  
  	while (bt.available()) {
    	a = bt.read();
      	msg += String(a);
  	}
  
  	return msg;
}

void okDisconnect() {
	print("$okDisconnect");
}

void command() {
	Serial.println("AT enabled. Remember to restart Arduino.");
	bt.end();
	digitalWrite(btKeyPin, HIGH);
	digitalWrite(btPwrPin, LOW);
	delay(200);
	digitalWrite(btPwrPin, HIGH);
	bt.begin(38400);
	
	while (true) {
		if (bt.available())
    		Serial.write(bt.read());

  		if (Serial.available())
    		bt.write(Serial.read());
	}
}

// Meat
 
void loop() {
    String msg = getMessage();
    
    if (Serial.available() && Serial.read() == '#')
    	command();
    
    // Command filters here via else if's
    if (msg.startsWith("help")) 
    	help();
    else if (msg.startsWith("open")) 
    	openDoor();
    else if (msg.startsWith("close"))
    	closeDoor();
    else if (msg.startsWith("alert"))
    	alert();
    	
    else if (msg != "") {
    	print("\"" + msg + "\" is not a supported command ☹");
    	print("Enter command \"help\" for a list of commands.");
    }
    
    if (msg != "") okDisconnect();
    
    delay(10);
}

/*
 * This is a 1 channel nrf24l01 transmitter and receiver code.
 * There is a single output(led control) in the receiver which can controlled with the pushbutton in transmitter;
 * 
 * To know more refer the below links:
 *  https://youtu.be/UoeU79G09Dk
 *  https://dhirajkushwaha.com/elekkrypt
 *  
 */

#include <Adafruit_SSD1306.h>
#define OLED_SDA D2
#define OLED_SCL D1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(128, 64, &Wire, OLED_ADDR);

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
const int buzzerPin = 2;

RF24 radio(7,8); // declaring CE and CSN pins
const byte address[] = "node1";

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT); 
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  radio.begin(); // initializes the operations of the chip
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  
}


void loop() {
  while(radio.available()){  
    int i =0;
    // alert(i);
    radio.read(&i, sizeof(i));
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Saline level");
    display.setCursor(0, 30);
    display.println(i);
    display.display();
    Serial.println(i);
    
  }


}

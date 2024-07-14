#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUM_DROPS 10

struct Raindrop {
  int x;
  int y;
  int speed;
};

Raindrop drops[NUM_DROPS];

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  randomSeed(analogRead(0));
  
  for(int i = 0; i < NUM_DROPS; i++) {
    drops[i].x = random(0, SCREEN_WIDTH);
    drops[i].y = random(0, SCREEN_HEIGHT);
    drops[i].speed = random(1, 6);
  }
}

void loop() {
  display.clearDisplay();

  for(int i = 0; i < NUM_DROPS; i++) {
    display.drawLine(drops[i].x, drops[i].y, drops[i].x, drops[i].y + 4, SSD1306_WHITE);
    drops[i].y += drops[i].speed;
    
    if(drops[i].y > SCREEN_HEIGHT) {
      drops[i].x = random(0, SCREEN_WIDTH);
      drops[i].y = 0;
      drops[i].speed = random(1, 6);
    }
  }
  
  display.display();
  delay(30);
}


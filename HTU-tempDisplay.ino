#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "Adafruit_HTU21DF.h"
#include "SparkFunHTU21D.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE); 
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock= SCL*/ 14, /* data= SDA*/ 12, /* reset=*/ U8X8_PIN_NONE);
//Adafruit_HTU21DF htu = Adafruit_HTU21DF();
HTU21D myHumidity;
char *txt = "test";

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_test(void) {
  //u8g2.clearBuffer();
  //u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0,20,"test");
  //u8g2.sendBuffer();
}

void u8g2_Roland(void) {
  //u8g2.clearBuffer();
  //u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0,20,"Roland");
  //u8g2.sendBuffer();
}

void u8g2_HTU(void) {
  //u8g2.clearDisplay();
  Serial.println("StarteHTU");
  //Serial.print("Temp: "); Serial.print(htu.readTemperature());
  Serial.print("Temp: "); Serial.print(myHumidity.readTemperature());
  //Serial.print("HTU auf Display");
  //float temp = htu.readTemperature();
  float temp = myHumidity.readTemperature();
  //txt = "Hallo Conny";
  delay(300);
  //char buf[100];
  //sprintf(buf, "%f", temp);
  //sprintf(txt, "%f", temp);
  String newData;
  char buffer[20];
  String txt2 = String(temp);        
  txt2.toCharArray(buffer, 20);
    //u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0,20,buffer);
}

uint8_t draw_state = 0;

void draw(void) {
  //u8g2_prepare();
  switch(draw_state) {
    case 0: u8g2_test(); break;
    case 1: u8g2_Roland(); break;
    case 2: u8g2_HTU(); break;
    //case 3: u8g2_string(draw_state&7); break;
    //case 4: u8g2_line(draw_state&7); break;
    //case 5: u8g2_triangle(draw_state&7); break;
    //case 6: u8g2_ascii_1(); break;
    //case 7: u8g2_ascii_2(); break;
    //case 8: u8g2_extra_page(draw_state&7); break;
  }
}
void setup() {
  delay(5000);
  Serial.begin(9600);
  //Serial.print("Temp: "); Serial.print(htu.readTemperature());
  //htu.reset();
  myHumidity.begin();
  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB14_tr); // choose a suitable font
  u8g2.drawStr(0,20,"Starting Up");
  u8g2.sendBuffer();
  delay(1000);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB14_tr); // choose a suitable font
  u8g2.drawStr(0,20,"Roland");
  u8g2.sendBuffer();
  delay(1000);
}

void loop() {
  u8g2.clearBuffer();
  draw_state = 0;
  draw();
  //u8g2_test();
  u8g2.sendBuffer();
  delay(1000);
  u8g2.clearBuffer();
  draw_state = 1;
  draw();
  u8g2.sendBuffer();
  //draw_state++;
  //if ( draw_state >= 1 )
  //draw_state = 0;
  // deley between each page
  delay(1000);
  u8g2.clearBuffer();
  draw_state = 2;
  draw();
  u8g2.sendBuffer();
  delay(1000);
}

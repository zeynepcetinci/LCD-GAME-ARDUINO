#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

float playerLine = 0;
float playerColumn = 0;
float starColumn = 0;
float starLine = 0;
float left_column_boundary = 0;
float right_column_boundary = 0;
float top_line_boundary = 0;
float bottom_line_boundary = 0;
float countScore = 0;
float totalScore = 5;
float countStep = 30;
float totalStep = 0;

void image1() { // Mugs
  lcd.clear();
  byte image06[8] = {B00000, B00000, B01111, B01000, B01000, B00100, B00010, B00001};
  byte image11[8] = {B00000, B00000, B11110, B00010, B00010, B00100, B01000, B10000};
  byte image07[8] = {B00000, B00000, B11110, B00010, B00010, B00100, B01000, B10000};
  byte image22[8] = {B00001, B00001, B00011, B00111, B00000, B00000, B00000, B00000};
  byte image23[8] = {B10000, B10000, B11000, B11100, B00000, B00000, B00000, B00000};
  byte image10[8] = {B00000, B00000, B01111, B01000, B01000, B00100, B00010, B00001};
  byte image26[8] = {B00001, B00001, B00011, B00111, B00000, B00000, B00000, B00000};
  byte image27[8] = {B10000, B10000, B11000, B11100, B00000, B00000, B00000, B00000};
  
  lcd.createChar(0, image06);
  lcd.createChar(1, image11);
  lcd.createChar(2, image07);
  lcd.createChar(3, image22);
  lcd.createChar(4, image23);
  lcd.createChar(5, image10);
  lcd.createChar(6, image26);
  lcd.createChar(7, image27);
  
  lcd.setCursor(5, 0);
  lcd.write(byte(0));
  lcd.setCursor(10, 0);
  lcd.write(byte(1));
  lcd.setCursor(6, 0);
  lcd.write(byte(2));
  lcd.setCursor(5, 1);
  lcd.write(byte(3));
  lcd.setCursor(6, 1);
  lcd.write(byte(4));
  lcd.setCursor(9, 0);
  lcd.write(byte(5));
  lcd.setCursor(9, 1);
  lcd.write(byte(6));
  lcd.setCursor(10, 1);
  lcd.write(byte(7));
}
void image2() { // SMILE EMOJI
  lcd.clear();
  byte image08[8] = {B00000, B00001, B00001, B00001, B00001, B00001, B00001, B10001};
  byte image09[8] = {B00000, B10000, B10000, B10000, B10000, B10000, B10000, B10001};
  byte image24[8] = {B01000, B00100, B00011, B00000, B00000, B00000, B00000, B00000};
  byte image25[8] = {B00010, B00100, B11000, B00000, B00000, B00000, B00000, B00000};
  
  lcd.createChar(0, image08);
  lcd.createChar(1, image09);
  lcd.createChar(2, image24);
  lcd.createChar(3, image25);
  
  lcd.setCursor(7, 0);
  lcd.write(byte(0));
  lcd.setCursor(8, 0);
  lcd.write(byte(1));
  lcd.setCursor(7, 1);
  lcd.write(byte(2));
  lcd.setCursor(8, 1);
  lcd.write(byte(3));
}

void starting(){
  lcd.setCursor(0, 0);
  lcd.print("Your Score 5");
  lcd.setCursor(0, 1);
  lcd.print("to win the game");
  delay(4000);
  lcd.clear();
}

void drawCharacter(){
  byte woman[8] = {B01110, B01110, B00100, B01110, B10101, B01110, B11111, B01010};
  lcd.createChar(0, woman);
  lcd.setCursor(playerColumn - 1, playerLine - 1);
  lcd.write(byte(0));

  byte flower[8] = {B00000, B01010, B11011, B00100, B11011, B01010, B00000, B00000};
  lcd.createChar(1, flower);
  lcd.setCursor(starColumn - 1, starLine - 1);
  lcd.write(byte(1));

  lcd.setCursor(12, 0);
  lcd.print("S:");
  lcd.setCursor(14, 0);
  lcd.print(String(countScore).toInt());
  lcd.setCursor(12, 1);
  lcd.print("C:");
  lcd.setCursor(14, 1);
  lcd.print(countStep); //Countdown
    
  if(countStep == 0 && countScore < totalScore){
    lcd.clear();
    lcd.print("YOU LOST GAME");
  }
  delay(1000);
}

void ending (){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("YOU ARE WIN");
  delay(3000);
  lcd.clear();
}

void _delay(float seconds) {
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) 
    _loop();
}

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  
  starting();
  
  left_column_boundary = 1;
  right_column_boundary = 12;
  bottom_line_boundary = 1;
  top_line_boundary = 2;
  playerLine = 1;
  playerColumn = left_column_boundary;

  while(1) {
      starLine = random(1, 3);
      starColumn = random(left_column_boundary, right_column_boundary +1);
      drawCharacter();
 
      if(countScore < totalScore && countStep!=totalStep){
          while(!((playerLine == starLine) && (playerColumn == starColumn))){
            _loop();
            // MOVE UP
            if(analogRead(A1) > 600){
                if(playerLine == bottom_line_boundary){
                    countStep=countStep-1;
                    playerLine += 1;
                    lcd.clear();
                    drawCharacter();
                }
                
            }
            // MOVE DOWN
            if(analogRead(A1) < 400){
                if(playerLine == top_line_boundary){
                    countStep=countStep-1;
                    playerLine += -1;
                    lcd.clear();
                    drawCharacter();
                }
            }
            // MOVE LEFT
            if(analogRead(A0) < 400){
                if(playerColumn > left_column_boundary){
                    countStep=countStep-1;
                    playerColumn += -1;
                    lcd.clear();
                    drawCharacter();
                }
            }
            // MOVE RIGHT
            if(analogRead(A0) > 600){
                if(playerColumn < right_column_boundary){
                    countStep=countStep-1;
                    playerColumn += 1;
                    lcd.clear();
                    drawCharacter();
                }
            }
          }
          countScore += 1;
      }
      else{
          ending();
          while(1){
            image1();
            delay(500);
            image2();
            delay(500);
            image1();
          }
      }
      _loop();
  }
}

void _loop() {
}

void loop() {
  _loop();
}

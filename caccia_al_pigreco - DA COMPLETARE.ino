#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int ciao = 0;
const int b1 = 9;
const int b2 = 10;
const int b3 = 11;
const int b4 = 12;
const int b5 = 13;

int[] posPiGreco = { 1, 5, 9, 13,};

bool start = false;

byte fantasmino[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B11111,
  B10101,
  B00000
};
byte freccia[8] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000
};
byte Heart[8] = {
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000,
0b00000
};
String msg[2] = {"    Premi il     tasto centrale  per cominciare", "Press the centerbutton to start"};


void setup() {
  // put your setup code here, to run once:
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  lcd.createChar(0, fantasmino);
  lcd.createChar(1, freccia);
  lcd.createChar(2, Heart);
  lcd.begin(16, 2);
  lcd.print("IT   selez.   EN");
  lcd.setCursor(2, 1);
  lcd.print("  -lingua-  ");
  lcd.setCursor(1,2); 
  lcd.write(byte(1));
  lcd.setCursor(14,2); 
  lcd.write(byte(1));
  //lcd.setCursor(11,2); 
  //lcd.write(byte(0));
  //delay(100000);
}

void loop() {
  while(true){//digitalRead(b3) == LOW && digitalRead(b1) == LOW
    if(digitalRead(b1) == HIGH){
      introduzione(0);
      break;
    }
    if(digitalRead(b5) == HIGH){
      introduzione(1);
      break;
    }
  }
  if(start){
    lcd.clear();
    startGioco(3);
    delay(10000);
  }else{
    lcd.clear();
    delay(10000);
  }
  setup();
}

void introduzione(int ciao){
  lcd.clear();
  int r = 0;
  int c = 0; 
  for (int i = 0; i < msg[ciao].length(); i++) {
    char ch = msg[ciao].charAt(i);
    String str = "riga:" + String(r) + " col:" + String(c);
    Serial.println(str);
    lcd.setCursor(c, r);
    lcd.print(ch);
    delay(100);
    c++; 
    if (c == 16) {
      r++; 
      c = 0;  
    }
    if (r == 2) {
      r = 0;
      delay(700);
      lcd.clear();
    }
  }    
  delay(2000);
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print("start");
  lcd.setCursor(15, 0);
  lcd.print("?");
  //delay(100000);
  lcd.setCursor(7,2); 
  lcd.write(byte(1));
  lcd.setCursor(15,2); 
  lcd.write(byte(1));
  while(true){//digitalRead(b3) == LOW && digitalRead(b1) == LOW
    if(digitalRead(b3) == HIGH){
      start = true;
      break;
    }
    if(digitalRead(b5) == HIGH){
      start = false;
      break;
    }
  }
}

void startGioco(int vite){
  
  stampaVite(vite);
  
  delay(100000);



  
}
void stampaVite(int vite){
  int pos = 16 - vite;
  lcd.setCursor(pos,0); 
  for(int i = 0; i < vite; i++ ){
    lcd.write(byte(2));
  }
}

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int ciao = 0;
const int b1 = 9;
const int b2 = 10;
const int b3 = 11;
const int b4 = 12;
const int b5 = 13;
int vite;
int posPiGreco[] = { 1, 4, 7, 10, 13};
int punti = 0;
bool start = false;
int punteggioTot = 0;
int record = 0;
int j = 0;

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
byte PiGreco[8] = {
  0b00000,
  0b11111,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01011,
  0b00000
};
String msg[2] = {"    Premi il     tasto centrale  per cominciare", "Press the centerbutton to start"};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  lcd.createChar(0, fantasmino);
  lcd.createChar(1, freccia);
  lcd.createChar(2, Heart);
  lcd.createChar(3, PiGreco);
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
  //start = true;
  vite = 3;
  if(start){
    lcd.clear();
    startGioco();
    //delay(10000);
  }else{
    lcd.clear();
    delay(1000);
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
      while(digitalRead(b3) == HIGH);
      break;
    }
    if(digitalRead(b5) == HIGH){
      start = false;
      while(digitalRead(b3) == HIGH);
      break;
    }
  }
}

void startGioco(){
  int rPrima = 0;
  while(digitalRead(b1) == HIGH);
  while(vite > 0){
    Serial.println(vite);
    while(digitalRead(b1) == HIGH);
    stampaVite();
    for(int i = 0; i < 5; i++){
      lcd.setCursor(posPiGreco[i],2); 
      lcd.write(byte(0));
      Serial.print(i);
    }
    int r = 0;
    while(r == rPrima){
      r = random(0, 5);
    }
    rPrima = r;
    int pos = posPiGreco[r];
    lcd.setCursor(pos,2); 
    lcd.write(byte(3));
    //int d = 0;
    /*if(j == 5){
      while(d == rPrima){
        d = random(0, 5);
      }
      lcd.setCursor(pos,2); 
      lcd.write(byte(2));
      j = 0;
    }*/
    j++;
    //Serial.print(r);
    //Serial.print(pos);
    int t1 = millis();
    while(true){
      if(digitalRead(b1) == HIGH){
        Serial.println("b1");
        controlloPreso(r, 0);
        while(digitalRead(b1) == HIGH);
        break;
      }
      if(digitalRead(b2) == HIGH){
        Serial.println("b2");
        controlloPreso(r, 1);
        while(digitalRead(b2) == HIGH);
        break;
      }
      if(digitalRead(b3) == HIGH){
        Serial.println("b3");
        controlloPreso(r, 2);
        while(digitalRead(b3) == HIGH);
        break;
      }
      if(digitalRead(b4) == HIGH){
        Serial.println("b4");
        controlloPreso(r, 3);
        while(digitalRead(b4) == HIGH);
        break;
      }
      if(digitalRead(b5) == HIGH){
        Serial.println("b5");
        controlloPreso(r, 4);
        while(digitalRead(b5) == HIGH);
        break;
      }
      int ora = millis();
      if((ora - t1) > 5000){
        Serial.println("tempo");
        vite--;  
        lcd.clear();
        lcd.setCursor(5,0); 
        lcd.print("-1 vita");
        lcd.setCursor(2,1); 
        lcd.print("Tempo scaduto");
        delay(2000);
        break;
      }
    }
    lcd.clear();
  }
  //delay(100000);
  lcd.clear();

  lcd.setCursor(3,2); 
  lcd.print("GAME OVER");
  if(punteggioTot > record){
    record = punteggioTot;
    lcd.setCursor(2,0); 
    lcd.print("Nuovo record!");
  }
  delay(3000);
  lcd.clear();
  lcd.setCursor(1,0); 
  lcd.print("Punti tot: ");
  lcd.print(punteggioTot);
  lcd.setCursor(2,1); 
  lcd.print("RECORD: ");
  lcd.print(record);
  delay(5000);
  punteggioTot = 0;
  punti = 0;
  vite = 3;
}
void controlloPreso(int r, int bN){
  if(r == bN){
    punti++;
    punteggioTot++;
    if( punti == 10){
      if(vite != 5){
        vite++; 
      }
      punti = 0;
    }
    /*lcd.clear();
    lcd.setCursor(5,2); 
    lcd.print("BRAVO");
    delay(2000);    
    lcd.print(vite);
    delay(2000);
    lcd.print(r);
    delay(2000);
    lcd.print(bN);
    delay(2000);*/
    //while(digitalRead(b1) == LOW);
  }else{
    vite--;
  }
  stampaVite();
  
}
void stampaVite(){
  int pos = 16 - vite;
  lcd.setCursor(pos,0); 
  for(int i = 0; i < vite; i++ ){
    lcd.write(byte(2));
  }
  lcd.setCursor(0,0); 
  lcd.print("Punti: ");
  lcd.print(punti);
}

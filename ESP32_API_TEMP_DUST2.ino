/*----------Lチカ用LED----------*/
const int LED_1 = 19;
/*----------Wi-Fi用ピン----------*/
const int WIFI_POWER_LED = 18;
/*----------GP2Y1014AU用ピン----------*/
const int sharpLEDPin = 25;   // Arduino digital pin 7 connect to sensor LED.
const int sharpVoPin = 35;   // Arduino analog pin 5 connect to sensor Vo.
/*----------LM61CIZPin用ピン----------*/
const int LM61CIZPin = 34;
/*--------------------*/

void setup() {
  Serial.begin(115200);
  api_setup();
  GP2Y1014AU_setup();
  pinMode(LED_1,OUTPUT);
}

void loop() {
  Serial.print("GP=");
  Serial.println(GP2Y1014AU());
  Serial.print("LM=");
  Serial.println(LM61CIZ());
  delay(1000);
  //api_send();
  delay(1000);
}

/*----------Lチカ関数----------*/
void L_tika(int cnt){
  for(int i=0;i<cnt;i++){
    digitalWrite(LED_1,HIGH);
    delay(100);
    digitalWrite(LED_1,LOW);
    delay(100);
  }
}

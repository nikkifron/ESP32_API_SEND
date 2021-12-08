/*
 * temp(c)  mv
 * 100      1600
 * 85       1450
 * 25       850
 * 0        600
 * -25      350
 * -30      300
 */
 
float LM61CIZ() {  
  float analog , temp , vout; 
  analog = analogRead(LM61CIZPin);
  vout = (analog * 1000) / 1023;//電圧に変換しmv単位に修正
  temp = (vout - 700) / 10;
  return temp;
}

/////////////////////////////////////////////////////////////////////////////
// Sharp GP2Y1014AU0F Dust Sensor Demo
//
// Board Connection:
//   GP2Y1014    Arduino
//   V-LED       Between R1 and C1
//   LED-GND     C1 and GND
//   LED         Pin 27
//   S-GND       GND
//   Vo          A16
//   Vcc         5V
//
// Serial monitor setting:
//   9600 baud
/////////////////////////////////////////////////////////////////////////////

// Choose program options.
#define USE_AVG

// Arduino pin numbers.
//const int sharpLEDPin = ;   // Arduino digital pin 7 connect to sensor LED.
//const int sharpVoPin = ;   // Arduino analog pin 5 connect to sensor Vo.

// For averaging last N raw voltage readings.
#ifdef USE_AVG
#define N 100
static unsigned long VoRawTotal = 0;
static int VoRawCount = 0;
#endif // USE_AVG

// Set the typical output voltage in Volts when there is zero dust. 
static float Voc = 0.6;

// Use the typical sensitivity in units of V per 100ug/m3.
const float K = 0.5;

// Arduino setup function.
void GP2Y1014AU_setup() {
  pinMode(sharpLEDPin, OUTPUT);
  delay(2000);
}

// Arduino main loop.
float GP2Y1014AU() {  
  // Turn on the dust sensor LED by setting digital pin LOW.
  digitalWrite(sharpLEDPin, LOW);

  // Wait 0.28ms before taking a reading of the output voltage as per spec.
  delayMicroseconds(280);

  // Record the output voltage. This operation takes around 100 microseconds.
  int VoRaw = analogRead(sharpVoPin);
  
  // Turn the dust sensor LED off by setting digital pin HIGH.
  digitalWrite(sharpLEDPin, HIGH);

  // Wait for remainder of the 10ms cycle = 10000 - 280 - 100 microseconds.
  delayMicroseconds(9620);
  
  // Use averaging if needed.
  float Vo = VoRaw;
  #ifdef USE_AVG
  VoRawTotal += VoRaw;
  VoRawCount++;
  if ( VoRawCount >= N ) {
    Vo = 1.0 * VoRawTotal / N;
    VoRawCount = 0;
    VoRawTotal = 0;
  }
  #endif // USE_AVG

  // Compute the output voltage in Volts.
  Vo = Vo / 1024.0 * 5.0;
  //printFValue("Vo", Vo*1000.0, "mV");

  // Convert to Dust Density in units of ug/m3.
  float dV = Vo - Voc;
  if ( dV < 0 ) {
    dV = 0;
    Voc = Vo;
  }
  
  float dustDensity = dV / K * 100.0;
  return dustDensity;
  
}

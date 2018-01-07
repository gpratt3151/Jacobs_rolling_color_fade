/* ARDUINO CONSTANT & VARIABLE DEFINITIONS
   ---------------------------------------  */
// Arduino output pin receiving brightness levels for a specific color
#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 3

// # of milliseconds to pause between each pass of the main Arduino loop
#define Loop_Delay 30
  
// Brightness level of each color (0..255)
int Brightness_R;
int Brightness_G;
int Brightness_B;
  
// Fade step counter for LED cycle through off (510 steps), fade on (255 steps),
// on (510 steps), fade off (255 steps) 1530 total steps
int FadeStep_R;  
int FadeStep_G;
int FadeStep_B;


// =====================================
// ARDUINO SETUP ROUTINE
// -------------------------------------
void setup() {
  //Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Set initial strip color. 0(off) to 255(on). can be anything or nothing. 
  // This value is constrained to 0 - 255. any number higher than 255 will be rounded down to 255.
  //                                       any number lower than 0 will be rounded up to 0.
  Brightness_R = 0;
  Brightness_G = 0;
  Brightness_B = 0;

  /* Set starting fade step position. -764 to -255 = on (brightness level is 255)
                                      -254 to 0 = fading on (this number *-1 = brightness level)
                                         0 to 510 = off (brightness level is 0)
                                       511 to 765 = fading off (this number - 510 = brightness level
  must each be 510 steps apart for smooth color pauses. 
  if pauses removed by commenting out or removing ColorValue if statements and replacing 
  with setLEDS (Brightness_R, Brightness_G, Brightness_B); ,which I've already done, these number 
  can be any value from -764 to 765 in any combination, likely making many unplesant fade patterns,
  but also with many possibilities for interesting patterns.  If all values are 510 steps apart   
  the results will ROY G BIV either forward or backward and starting at different positions 
  depending on the values given. the farther off the 510 steps of seperationg the further from
  ROY G BIV the pattern will move. */
  FadeStep_R = 0;      //0      These settings for normal ROY G BIV
  FadeStep_G = 325;    //510
  FadeStep_B = 650;    //-510
}

// =====================================
// ARDUINO MAIN LOOP ROUTINE
// -------------------------------------
void loop() {
  // Secrement each LED's fade step counter by one at the start of each loop
  FadeStep_R = FadeStep_R - 1;
  FadeStep_G = FadeStep_G - 1;
  FadeStep_B = FadeStep_B - 1;

  // Fade red LED according to it's fade step counter.
  if (FadeStep_R == -764) {FadeStep_R = 765;}
  if (FadeStep_R < 0) {Brightness_R = FadeStep_R * -1;}
  if (FadeStep_R >= 510) {Brightness_R = FadeStep_R - 510;}
 
  // Fade green LED according to it's fade step counter.  
  if (FadeStep_G == -764) {FadeStep_G = 765;}
  if (FadeStep_G < 0) {Brightness_G = FadeStep_G * -1;}
  if (FadeStep_G >= 510) {Brightness_G = FadeStep_G - 510;}
 
  // Fade blue LED according to it's fade step counter.
  if (FadeStep_B == -764) {FadeStep_B = 765;}
  if (FadeStep_B < 0) {Brightness_B = FadeStep_B * -1;}
  if (FadeStep_B >= 510) {Brightness_B = FadeStep_B - 510;}
  
  // if step counters are intialized 510 steps apart, -510 is the step in each LED's fade cycle
  // that it will be on full brightness while the other 2 LED's are off.
  Brightness_B = constrain(Brightness_B, 0, 255);
  Brightness_G = constrain(Brightness_G, 0, 255);
  Brightness_R = constrain(Brightness_R, 0, 255); 

  //Send brightness levels to LED strip
  setLEDS(Brightness_R, Brightness_G, Brightness_B);

  // slow the loop down a bit
  delay(Loop_Delay);
}

// send the LED levels to the Arduino pins
void setLEDS (int ipR, int ipG, int ipB) {
  analogWrite(RED_PIN, ipR);     // send the red brightness level to the red LED's pin
  analogWrite(GREEN_PIN, ipG);
  analogWrite(BLUE_PIN, ipB);
}

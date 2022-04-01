/////////////////////////////////////////////////////////////////////// led screen _ matrix 8x32 ///////////////////////////////////////////////////////////////////////////////////

#include <Adafruit_NeoPixel.h>
#define schermo A4 // matrice 8x32
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(256, schermo, NEO_GRB + NEO_KHZ800);


//////////////////////////////////////////////////////////////////////// MP3 _ speaker ////////////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(11, 10); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

///////////////////////////////////////////////////////////////////////// Servo motor /////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Servo.h>
Servo Mrotation; 
Servo Mfront; 
Servo Mleft; 
Servo Mright; 
int pos = 0;

//////////////////////////////////////////////////////////////////////// IR _ controller //////////////////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
int receiver = 34;
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

///////////////////////////////////////////////////////////////////////// potentiometer /////////////////////////////////////////////////////////////////////////////////////

int volumePIN  = A2;
int volume = 0;

int lumenPIN = A3;
int lumen = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  // IR controller
  irrecv.enableIRIn(); // Start the receiver


  // screen
  strip.begin();
  strip.setBrightness(255);
  strip.show();   // Initialize all pixels to 'off'
  showEyes(0);
  delay(300);


  // MP3 _ voice set up
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(25);  //Set volume value. From 0 to 30
  myDFPlayer.play(0);


  //////////////////////////////////////////////////////////////////////////////////////

  // head motor  _ go to home position 0
  Mfront.attach(6);
  Mfront.write(0);// move servos to center position 0

  Mleft.attach(4);
  Mleft.write(0);// move servos to center position 0

  Mright.attach(2);
  Mright.write(0);// move servos to center position 0


  // rotation motor _ turn left and right
  Mrotation.attach(8);
  Mrotation.write (90);

  /*
    for (pos = 90; pos <= 180; pos += 1) { // look to the right
      Mrotation.write(pos);
      delay(5);
    }
    delay(500);

    for (pos = 180; pos >= 0; pos -= 1) { //look to the left
      Mrotation.write(pos);
      delay(6);
    }
    delay(500);

    for (pos = 0; pos <= 90; pos += 1) { // look ahead
      Mrotation.write(pos);
      delay(6);
    }
  */
}

void loop()
{

  /*  
      volume = analogRead(volumePIN);
      volume = map(volumePIN, 0, 1023, 0, 30); // check mp3 volume
      myDFPlayer.volume(volume);

      lumen = analogRead(lumenPIN);
      lumen = map(lumenPIN, 0, 1023, 0, 255); // check led brightness
      strip.setBrightness(lumen);

  */

  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }
}

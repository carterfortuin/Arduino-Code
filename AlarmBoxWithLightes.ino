
// Imports
#include <DS3231.h>                     // Importing real time clock from library
#include <Wire.h>                       // Importing I2B wire comand? from library
#include <LiquidCrystal.h>              // Importing LCD from library

// LCD Screen
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);    // Seting pins on board to LCD, Unknown order motivation


// Real time clock
DS3231  rtc(SDA, SCL);                  // Assigning varribles to RTC


// Setting varible t to time
Time  t;                                // Time varrible


// Initilising time varribles
int Hor;                                //
int Min;                                //
int Sec;                                //

// Setting pins
#define buz 11                          // Alarm set to pin 11 on arduino
#define light 12                        // Lights set to pin 12 on arduino



// Set up and initilization on the board, runs for the first 2 seconds
void setup()
  {  

    Wire.begin();                       // Unknown
    rtc.begin();                        // Unknown
    Serial.begin(9600);                 // Unknown
    pinMode(buz, OUTPUT);               // Setting alarm pin to be given pixies when commanded (aka not a sensor)
    lcd.begin(16,2);                    // Size of LCD Screen, two rows with 16 spots for symbols
    lcd.setCursor(0,0);                 // Addressing to top line of LCD Screen
    lcd.print("ALARM BOX");             // Print on start up
    lcd.setCursor(0,1);                 // Addressing to bottom line of LCD Screen
    lcd.print("Arduino Alarm ");        // Print on start up
  
    // The following lines can be uncommented to set the date and time

    rtc.setDOW(SATURDAY);               // Set Day-of-Week to SUNDAY
    rtc.setTime(7, 44, 0);              // Set the time to 12, 00, 00 (24hr format)
    rtc.setDate(11, 4, 2018);           // Set the date to 8 25 2015

    delay(2000);                        // The 2 second delay on the start up display

}



//-----------Main loop----------------
void loop()

  {
    t = rtc.getTime();                         // Retrieves time from the real time clock, (how unknown)
    Hor = t.hour;                              // 
    Min = t.min;                               //
    Sec = t.sec;                               //
    lcd.setCursor(0,0);                        // First row of LCD Screen
      lcd.print("Time: ");                     // 
      lcd.print(rtc.getTimeStr());             //
    lcd.setCursor(0,1);                        // Second row of LCD Screen
      lcd.print("Date: ");                     //
      lcd.print(rtc.getDateStr());             //
    // Comparing the current time with the Alarm time, will go of for the two minutes listed in the or statment
    if( Hor == 7 &&  (Min == 00 || Min == 30)) // run time for each time found true (5 seconds) so 20 laps a minute with 80 soundings of the alarm
      {
        Buzzer();                              // Run loop called "Buzzer" from below (takes 1 second)
        Buzzer();                              // run looop (1 second)
        lcd.clear();                           // remove image from LCD
        lcd.print("Alarm ON");                 // Print on first row of LCD 
        lcd.setCursor(0,1);                    // Second row of LCD
        lcd.print("Alarming");                 // Print on second row
        Buzzer();                              // (1 second)
        Buzzer();                              // (1 second)
      }                                        // (4 seconds total ?)

     if( Hor == 7 &&  (Min == 01|| Min == 31)) // run time for each time found true 
      {
        LightsLong();                          // Run loop called "LightsLong" from below (takes 61 second)
        
      }                                        // (61 seconds total ?)
      
     delay(1000);                              // delay and rerun if statment (1 second)
}

//---------Call up programs-------------------
void Buzzer()
  {
    digitalWrite(buz,HIGH);                    //
    digitalWrite(light, HIGH);
    delay(500);                                //
    digitalWrite(buz, LOW);                    //
    digitalWrite(light, LOW);
    delay(500);                                //
  }

void LightsLong ()                             //
  {
    digitalWrite(light, HIGH);                 //
    delay(55000);                              //
    digitalWrite(light, LOW);
    delay(6000);
  }

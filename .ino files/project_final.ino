/*
  DS1307 RTC (Real-Time-Clock) Example

  Uno       A4 (SDA), A5 (SCL)
  Mega      20 (SDA), 21 (SCL)
  Leonardo   2 (SDA),  3 (SCL)
 */


 /*
     buzzer-->+ve_pin-->Digital 9
     immediate_pin-->Digital 11
   
  */

#include <Wire.h>
#include <DS1307.h>


DS1307 rtc;
int buzzer=9;
//const int exampin=10;
const int immediate=11;
const int high=8;

void setup()
{
  pinMode(buzzer, OUTPUT);
  digitalWrite(high,HIGH);
  /*init Serial port*/
  Serial.begin(9600);
  while(!Serial); /*wait for serial port to connect - needed for Leonardo only*/

  /*init RTC*/
  Serial.println("Initializing RTC...");

  /*only set the date+time one time*/
      rtc.set(0, 1, 8, 29, 2, 2020); /*11:30:00 22.02.2020 //sec, min, hour, day, month, year*/
    //rtc.adjust(DateTime(2020, 02, 26, 20, 06, 00 )); 

  /*stop/pause RTC*/
  // rtc.stop();

  /*start RTC*/
  rtc.start();
}

int ComputeDayOfWeek(int month, int day, int year)
 {
   int day_of_week;
  
   if (month < 3)
     {
      month += 12;
      --year;
     }
   day_of_week = day + (13 * month - 27) / 5 + year + year/4 - year/100 + year/400;
   return ((int)(day_of_week % 7) + 1);
 }

 void activatebuzzer()
 {
   tone(buzzer, 1000); // Send 1KHz sound signal...
   delay(5000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
   delay(1000);        // ...for 1sec
 }

//FOR WEEKDAYS 10:00  11:00  12:00  13:00  13:30  14:30  15:30  16:30
//FOR SATURDAY 10:00  11:00  12:00  13:00  13:45

 void weekdays(int sec,int min,int hour)
 {
   if(hour==10&&min==0&&sec==0)
     activatebuzzer();
   else if(hour==11&&min==0&&sec==0)
     activatebuzzer();
   else if(hour==12&&min==0&&sec==0)
     activatebuzzer();
   else if(hour==13&&min==0&&sec==0)
     activatebuzzer();
   else if(hour==13&&min==30&&sec==0)
     activatebuzzer();
   else if(hour==14&&min==30&&sec==0)
     activatebuzzer();
   else if(hour==15&&min==30&&sec==0)
     activatebuzzer();
   else if(hour==16&&min==30&&sec==0)
     activatebuzzer();
 }
 
void saturday(int sec,int min,int hour)
{
   if(hour==10&&min==0&&sec==0)
     activatebuzzer();
   else if(hour==11&&min==0&&sec==0)
     activatebuzzer();
   else if(hour==12&&min==0&&sec==0)
     activatebuzzer();
   else if(hour==13&&min==0&&sec==0)
     activatebuzzer();
   else if(hour==13&&min==45&&sec==0)
     activatebuzzer();
  
}


void loop()
{
  uint8_t sec, min, hour, day, month;
  uint16_t year;

  /*get time from RTC*/
  rtc.get(&sec, &min, &hour, &day, &month, &year);

  
   /*serial output*/
   //if(min%2==0)
   //{
  Serial.print("\nCurrent time and date is :\n");
  Serial.print("\nTime: ");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(min, DEC);
  Serial.print(":");
  Serial.print(sec, DEC);

  Serial.print("\nDate: ");
  Serial.print(day, DEC);
  Serial.print(".");
  Serial.print(month, DEC);
  Serial.print(".");
  Serial.print(year, DEC);
  // }
  /*wait a second*/
 // delay(1000);



  int dayno=ComputeDayOfWeek(month,day,year);
  if((dayno>1)&&(dayno<7))
  {
    weekdays(sec,min,hour);
  }
  else if(dayno==7)
  {
    saturday(sec,min,hour);
  }

  //if(digitalRead(exampin)==1)
    //exam(
    
    if(digitalRead(immediate)==1)
        activatebuzzer();
}

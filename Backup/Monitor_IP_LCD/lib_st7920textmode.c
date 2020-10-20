// Biblioteca LCD ST7920 no modo texto
// Rudi @ 09/04/2020

#include <wiringPi.h>           //WiringPi headers
#include <stdio.h>              //Needed for the printf function below
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Pino  4 LCD funcao RS  ligado a Raspberry pino 24 WiringPi 10
// Pino  5 LCD funcao RW  ligado a Raspberry pino 19 WiringPi 12 
// Pino  6 LCD funcao EN  ligado a Raspberry pino 23 WiringPi 14 
// Pino 17 LCD funcao RST ligado a Raspberry pino 22 WiringPi  6 

#define CS     10  
#define SID    12  
#define SCLK   14    
#define RESET   6   

void setbit(unsigned char a)
{
 digitalWrite (a, HIGH);
 usleep(1);
}

void clrbit(unsigned char a)
{
 digitalWrite (a,  LOW);
 usleep(1);
}

void write_ctr_lcd(unsigned char a)
{
 setbit(CS);
 setbit(SID);
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0 RW
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0 RS
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0 
 clrbit(SCLK); ((a & 0x80) == 0x80) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D7
 clrbit(SCLK); ((a & 0x40) == 0x40) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D6
 clrbit(SCLK); ((a & 0x20) == 0x20) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D5
 clrbit(SCLK); ((a & 0x10) == 0x10) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D4
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); ((a & 0x08) == 0x08) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D3
 clrbit(SCLK); ((a & 0x04) == 0x04) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D2
 clrbit(SCLK); ((a & 0x02) == 0x02) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D1
 clrbit(SCLK); ((a & 0x01) == 0x01) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK);
 clrbit(CS);
 usleep(200);
}

void write_data_lcd(unsigned char a)
{
 setbit(CS);
 setbit(SID);
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0 RW
 clrbit(SCLK); setbit(SID); setbit(SCLK); // 1 RS
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); ((a & 0x80) == 0x80) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D7
 clrbit(SCLK); ((a & 0x40) == 0x40) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D6
 clrbit(SCLK); ((a & 0x20) == 0x20) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D5
 clrbit(SCLK); ((a & 0x10) == 0x10) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D4
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); ((a & 0x08) == 0x08) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D3
 clrbit(SCLK); ((a & 0x04) == 0x04) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D2
 clrbit(SCLK); ((a & 0x02) == 0x02) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D1
 clrbit(SCLK); ((a & 0x01) == 0x01) ? setbit(SID) : clrbit(SID); setbit(SCLK); // D0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK); clrbit(SID); setbit(SCLK); // 0
 clrbit(SCLK);
 clrbit(CS);
 usleep(100);
}

void goto_lcd(unsigned char l, unsigned char c )
{
 unsigned char a;
 if (l==1) a=0x80;
 if (l==2) a=0x90;
 if (l==3) a=0x88;
 if (l==4) a=0x98;
 switch(c)
 { case  1:write_ctr_lcd(a);   break;
   case  2:write_ctr_lcd(a);   write_data_lcd(' '); break;
   case  3:write_ctr_lcd(a+1); break;
   case  4:write_ctr_lcd(a+1); write_data_lcd(' '); break;
   case  5:write_ctr_lcd(a+2); break;
   case  6:write_ctr_lcd(a+2); write_data_lcd(' '); break;
   case  7:write_ctr_lcd(a+3); break;
   case  8:write_ctr_lcd(a+3); write_data_lcd(' '); break;
   case  9:write_ctr_lcd(a+4); break;
   case 10:write_ctr_lcd(a+4); write_data_lcd(' '); break;
   case 11:write_ctr_lcd(a+5); break;
   case 12:write_ctr_lcd(a+5); write_data_lcd(' '); break;
   case 13:write_ctr_lcd(a+6); break;
   case 14:write_ctr_lcd(a+6); write_data_lcd(' '); break;
   case 15:write_ctr_lcd(a+7); break;
   case 16:write_ctr_lcd(a+7); write_data_lcd(' '); break;
 }
}

void lcd_str(char s[])
{
 do write_data_lcd(*s);
 while (*++s);
}

void lcd_bcd(unsigned char a)
{
 write_data_lcd('0'+a/100);
 a=a%100;
 write_data_lcd('0'+a/10);
 write_data_lcd('0'+a%10);
}

void setup_rasp_lcd(void)
{
  wiringPiSetup ();
 // wiringPiSetupGpio();  //
  pinMode (CS,   OUTPUT);
  pinMode (SID,  OUTPUT);
  pinMode (SCLK, OUTPUT);
  pinMode (RESET,OUTPUT);
  clrbit(RESET);
  usleep(50000);
  setbit(RESET);
  write_ctr_lcd(0x30); //   sendByte(0, 0b00110000)  # function set (8 bit)
  write_ctr_lcd(0x34); //   sendByte(0, 0b00110100)  # function set (extend instruction set)
  write_ctr_lcd(0x36); //   sendByte(0, 0b00110110)  # function set (graphic OFF)
  write_ctr_lcd(0x02); //   sendByte(0, 0b00000010)  # Enable CGRAM (after reset to BASIC instruction set)
  write_ctr_lcd(0x30); //   sendByte(0, 0b00110000)  # function set (basic instruction set)
  write_ctr_lcd(0x0c); //   sendByte(0, 0b00001100)  # displ.=ON , cursor=OFF , blink=OFF
  write_ctr_lcd(0x01); //   Clear LCD
  usleep(2000);
  write_ctr_lcd(0x80); //   sendByte(0, 0b10000000)  # Address Counter na left horni roh    
}


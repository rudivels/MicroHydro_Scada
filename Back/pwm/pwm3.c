#include <wiringPi.h>           //WiringPi headers
#include <stdio.h>              //Needed for the printf function below
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <softPwm.h>


void setup_adc(void)
{
	int i;
	wiringPiSetup(); // Gpio();
//	wiringPiSetupGpio();
	pinMode(2,INPUT);
	pullUpDnControl(2,PUD_OFF);
	pinMode(3,INPUT);
	pullUpDnControl(3,PUD_OFF);
	i=softPwmCreate(1,0,0x100); //0xff);

//	pinMode(1,PWM_OUTPUT);
//    pwmSetMode(PWM_MODE_MS);
//    pwmSetClock(2400);
//    pwmSetRange(8);
//	sleep(3); */
}

void adc_sequencial(void)
{
 int i=0;
 int dummy=0; 
 while (i<255) 
 {
	printf("%d - Pino 3 antes   = %d  Pwm= %d  | ", i, digitalRead(3),dummy);
	softPwmWrite(1,dummy);
	usleep(200000);
	printf("%d - Pino 3 depois  = %d  Pwm= %d\n", i, digitalRead(3),dummy);
	if (digitalRead(3)==0) i=256; else
    {i++;
     dummy=dummy + 1;
    } 
 }
}


void adc_app_suc(void) 
{
 int i=0;
 int d;
 int valor=0;
 int dummy=0; 
 dummy=0x80; 
 while (i<8)
 {  d=digitalRead(3);
	printf("%d - Pino 3 antes   = %d  Pwm= %d  | ", i, d,dummy+valor);
	softPwmWrite(1,dummy+valor);
	usleep(200000);
	d=digitalRead(3);
	printf("%x - Pino 3 depois  = %d  valor= %d\n", dummy, d,valor);
    if (d==0)
    { valor = valor + 0; }
    else 
    { valor = valor + dummy;}
    i++;
    dummy=dummy >> 1;
 }  
}

int leia_adc(int pino) 
{
 int i=0;
 int d;
 int valor=0;
 int dummy=0; 
 dummy=0x80; 
 while (i<8)
 {  d=digitalRead(pino);
	softPwmWrite(1,dummy+valor);
	usleep(200000);
	d=digitalRead(pino);
    if (d==0)
    { valor = valor + 0; }
    else 
    { valor = valor + dummy;}
    i++;
    dummy=dummy >> 1;
 } 
 return(valor); 
}

float adc_rede(void)
{ 
  return((220*leia_adc(3))/63);
}

float adc_bateria(void)
{
  return((11*leia_adc(2))/130);
}


int main(void)
{
 setup_adc();
 
 //adc_sequencial();
 //printf("\n aprox suc \n");
 //adc_app_suc();
 //printf("\n aprox dec \n");
 //adc_app_suc_dec();
 while(1)
 printf(" rede = %3.0f   bateria = %2.1f \n",adc_rede(),adc_bateria());

}


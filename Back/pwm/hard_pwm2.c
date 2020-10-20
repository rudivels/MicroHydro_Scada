#include <stdio.h>             
#include <unistd.h>
#include <stdlib.h>
#include <string.h>  
#include <time.h>
#include <string.h>

#include <wiringPi.h> 


/*
$ gpio mode 1 pwm   // configura GPIO.1 ou BCM-18 como pwm ou função alternativa alt 5
$ gpio pwm-ms       // configura o pwm para mark-space
$ gpio pwmc 10     // configura a frequencia do pwm (750hz)
$ gpio pwmr 256     // configura o ratio, neste caso para uma resolução de 8 bits
*/


void setup_pwm(void)
{
  /* faca o setup do ADC com system call do gpio */  
  system("gpio mode 1 pwm"); // configura pwm 
  system("gpio pwm-ms");
  system("gpio pwmc 10");    // 750hz
  system("gpio pwmr 256");   // conversor 8 bits
  system("gpio pwm 1 0");    // escreve 0 no pwm 

  pinMode(2,INPUT);
  pullUpDnControl(2,PUD_OFF);
  pinMode(3,INPUT);
  pullUpDnControl(3,PUD_OFF);
}




FILE *f2;
FILE *f3;

void mapea_pinos(void)
{
 system("gpio export 27 in"); // exporta GPIO.2 para /sys/class/gpio/gpio27/value  
 system("gpio export 22 in"); // exporta GPIO.3 para /sys/class/gpio/gpio22/value
} 


int leia_gpio(int i) 
{  return(digitalRead(i));
}


/*int leia_gpio(int i)
{
 int x;
 char c;
 if (i==2) {f2=fopen("/sys/class/gpio/gpio27/value","r"); fscanf(f2, "%c", &c);fclose(f2);}
 if (i==3) {f3=fopen("/sys/class/gpio/gpio22/value","r"); fscanf(f3, "%c", &c);fclose(f3);}
 return(c-'0');
}*/

void escreve_pwm(int i)
{ 
 char str1[50];
 char str2[50];
 strcpy(str1, "gpio pwm 1 ");
 sprintf(str2,"%d",i); 
 strcat(str1,str2); 
 system(str1); 
}

int leia_adc(int num_gpio) 
{
 int i=0;
 int valor=0;
 int dummy=0x80;
 while (i<8)
 { 
   escreve_pwm(dummy+valor);
   usleep(10000);  // 10 mil micro espera filtrar e estabilizar
   if(leia_gpio(num_gpio)==1) {valor = valor + dummy;}
   i++;
   dummy=dummy >> 1;
 } 
 return(valor); 
}

float adc_rede(void)
{ 
  return((220*leia_adc(3))/72);
}

float adc_bateria(void)
{
  return((11*leia_adc(2))/145);
}

int main(void)
{
 int estado;
 int res;
 int i=0;
 setup_pwm();
// mapea_pinos();
 printf("Canal 2 %d  ",adc_bateria()); //leia_adc(2));
 printf("Canal 3 %d\n",adc_rede()); //leia_adc(3));

 //printf("Canal 2 %d  ",leia_adc(2));
 //printf("Canal 3 %d\n",leia_adc(3));

/* while (i < 20)
 { 
  escreve_pwm(i*10);
  sleep(1);
  i++;
  printf("rpm=%d  pino  %d\n",i,leia_gpio(3));
 }*/
 escreve_pwm(0);

} 
 

#include <stdio.h>             
#include <unistd.h>
#include <stdlib.h>
#include <string.h>  
#include <time.h>
#include <string.h>

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
}

FILE *f6;

void mapea_pinos(void)
{
 system("gpio mode 6 up"); 
 system("gpio export 6 in"); // exporta GPIO.14 para /sys/class/gpio/gpio22/value
} 


int leia_gpio(int i)
{
 int x;
 char c;
 if (i==6) {f6=fopen("/sys/class/gpio/gpio6/value","r"); fscanf(f6, "%c", &c);fclose(f6);}
 return(c-'0');
}

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
 escreve_pwm(0);  
 int dummy=0x80;
 while (i<8)
 { 
   escreve_pwm(dummy+valor);
   usleep(10000);  // 10 mil micro espera filtrar e estabilizar
   if(leia_gpio(num_gpio)!=1) {valor = valor + dummy;}
   i++;
   dummy=dummy >> 1;
 } 
 return(valor); 
}


float adc_corr_bateria(void)
{
//  return(leia_adc(6)) ;
  return(  (3.3 * leia_adc(6))/255) ;

}



int main(void)
{
 int estado;
 int res=0;
 int i=0;
 float a,b;
 setup_pwm();
 mapea_pinos();
 
  while (res==0){
  
  i=leia_adc(6);
  a= (3.3*i)/256;
  b= (a - 2.5)/0.185;  
  
  //  Devido a ruido do 60 hz da rede vamos ter que fazer um filtro ativo no acs712
  //  depois amplificar o sinal 4 vezes e subtrair 1 volt para melhorar a resolução..
  
  
  printf("%d  %4.2f %3.2f  \n",i, a , b );  
  
//  printf("%d  %4.2f %3.1f  \n",leia_adc(6), adc_corr_bateria());  
  usleep(100000);

 }
} 
 


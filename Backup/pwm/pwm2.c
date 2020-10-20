#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
int main (void)
{
  printf ("Gerando sinais PWM na Raspberry Pi\n") ;
 
  // Inicializa o sistema wiringPi para usar o pinos de GPIO
  if (wiringPiSetupGpio() == -1)
    exit (1) ;
 
  // seta o modo do pino para INPUT, OUTPUT ou PWM_OUTPUT
  pinMode(18,PWM_OUTPUT);
  // Configura o PWM para o modo mark:space
  pwmSetMode(PWM_MODE_MS);
  // seta o divisor para o clock do PWM
  pwmSetClock(2400);  // valor para 1KHz
  // seta o registrador de intervalo no gerador de PWM
  pwmSetRange (8);    // valor para 1KHz
 
  for (;;) {
     // escreve o valor para registrador do PWM em um pino dado 
     // Gera o sinal de PWM no pino 18 
     pwmWrite (18, 5);  
     delay(1000);
  }
  
  return 0;
}

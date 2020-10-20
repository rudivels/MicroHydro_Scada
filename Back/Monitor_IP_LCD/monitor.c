// Programa monitor Raspberry com LCD ST7920 mostra IP
// Interface de comandos simples com teclado de 3 botoes
// Biblioteca de LCD ST7920 testado e funcioando
// Rudi @ 09/04/2020

// Adicionar leitura de tensao rede e bateria  26-07-2020
// Adicionar 3 botoes no painel 26-07-2020

// Novo hardware 23 de agosto com Raspberry Zero


// Funcionalidade
// Testa comunicacao Modbus e escreve no LCD
// imprime endereco IP no LCD
// imprime data e hora at boot time
// imprime data e hora atual
// leia botoes no painel

// Pino  4 LCD funcao RS ou /CS  chip select        === Fio branco  === ligado a Raspberry pino 24 WiringPi 10 SPI0 CS0
// Pino  5 LCD funcao RW ou /SID Sserial data input === Fio cinza   === ligado a Raspberry pino 19 WiringPi 12 SPI0 MOSI
// Pino  6 LCD funcao EN ou /SCLK serial clock      === Fio violeta === ligado a Raspberry pino 23 WiringPi 14 SPI0 SCLK
// Pino 17 LCD funcao RST                           === Fio amarela === ligado a Raspberry pino 22 WiringPi  6 PIO  Reset 
//#define CS     10  
//#define SID    12  
//#define SCLK   14    
//#define RESET   6   

// Pwm pino 35 - wiringpi 24 
// saida comparador tensao pino 33 wiringpi 23


#include <wiringPi.h>           //WiringPi headers
#include <stdio.h>              //Needed for the printf function below
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>

//#include <softPwm.h>

// A definicao dos pinos do Raspberry e a configuracao do display estah neste arquivo 
#include "lib_st7920textmode.h"

char IPpath[20];

// #define CS     10  
// #define SID    12  
// #define SCLK   14    
// #define RESET   6   

// void setup_rasp_lcd_pinos( 10, 12, 14, 6 ) //CS,  SID, SCLK, RESET);
// falta implementar essa rotina para permitir portabilidade


void liga_lcd(void)
{
	setup_rasp_lcd();
	pinMode (25,INPUT);
	pinMode (28,INPUT);
	pinMode (29,INPUT);
	pullUpDnControl(25,PUD_UP);
	pullUpDnControl(28,PUD_UP);
	pullUpDnControl(29,PUD_UP);	
}

int leia_IP(void)
{
 FILE *fp;
 fp = popen("hostname -I", "r");
 strcpy(IPpath,"Sem numero IP   ");
 if (fp == NULL) {
    strcpy(IPpath,"Erro abertura   ");
    return(0);
  }
 fgets(IPpath, 16, fp); 
 IPpath[15]=0;
 pclose(fp);
 return(1);
}

int leia_status_modbus(void)
{
 FILE *fp1;
 char c;
 fp1 = fopen("/home/pi/src/MicroHydro_Scada/modbuscon.log","r");
 fscanf(fp1,"%c",&c);
 fclose(fp1);
 // printf("%c",c);
 if (c=='1') return(1); else return(0);
}

char bateria[5];
char rede[4];
char corr_rede[3];
char corr_bat[3];



void leia_status_tensoes(void)
{
 FILE *fp2;
 fp2 = fopen("/home/pi/src/leia_tensoes/bateria.log","r");
 fscanf(fp2,"%s",&bateria);
 fclose(fp2);
 fp2 = fopen("/home/pi/src/leia_tensoes/rede.log","r");
 fscanf(fp2,"%s",&rede);
 fclose(fp2);
 
 fp2 = fopen("/home/pi/src/leia_tensoes/corr_rede.log","r");
 fscanf(fp2,"%s",&corr_rede);
 fclose(fp2);
 
 fp2 = fopen("/home/pi/src/leia_tensoes/corr_bat.log","r");
 fscanf(fp2,"%s",&corr_bat);
 fclose(fp2);
}


void tela_inicial(void)
{
 goto_lcd(2,1);
 lcd_str("Mqqt   Modbus"); 
 goto_lcd(3,1);
 lcd_str("V=    B=        ");
}

void sig_handler_shutdown(int signo)
{
	switch(signo)
	{ case SIGHUP: case SIGINT: 
		write_ctr_lcd(1); exit(1); break;
	  case SIGKILL : case SIGTERM: case SIGSTOP:
	    write_ctr_lcd(1); exit(1); break;
	  default: goto_lcd(1,1); lcd_bcd(signo); break;  
	}	
}


int main(void)
{
 int estado;
 int res;
 int i=0;
 char datum[80]; 
 char str[10];
 int c;
 time_t rawtime;  // timer = time(NULL);
 time_t rawtime_boot;
 struct tm * timeinfo;
 res=leia_IP();
 
 time(&rawtime_boot); 
 strftime(datum, 20, "%m-%d %H:%M:%S", localtime(&rawtime_boot)); 
 liga_lcd(); //setup_rasp_lcd(); 
// setup_adc();
 lcd_str(IPpath);
 tela_inicial();
// goto_lcd(4,1); 
// lcd_str(datum);
 
 if (signal(SIGINT, sig_handler_shutdown)== SIG_ERR)
 {
	 goto_lcd(4,1);
	 lcd_str("Erro signal");
 }
 
 sleep(2);
// goto_lcd(3,1);
// lcd_str("V=    B=        ");
 estado=0;
 while(1) 
 {
  switch(estado)
  {
   case 0: 	goto_lcd(2, 6);write_data_lcd('0');
			goto_lcd(2,15);
			c=leia_status_modbus(); // printf("%d", c);
			if (c==0) write_data_lcd('0');else write_data_lcd('1');

			time(&rawtime);
//			strftime(datum,20, "%m-%d %H:%M:%S", localtime(&rawtime)); 
			strftime(datum,20, "%H:%M:%S", localtime(&rawtime)); 
			goto_lcd(4,8);
			lcd_str(datum);

			if (i++ > 5) {
				res=leia_IP();
				goto_lcd(1,1);
				if (res==1) lcd_str(IPpath); else lcd_str("Sem IP wifi    ");
				i=0; 
			}
			
			leia_status_tensoes();
			
			goto_lcd(3,3); // sprintf(str, "%3.0f",adc_rede());
			lcd_str(rede); //str); 			
			
			
			goto_lcd(3,9); //sprintf(str, "%2.1f",adc_bateria());
			lcd_str(bateria); //"V=221 B=12.7    ");
			goto_lcd(3,14); if (digitalRead(25)==1)	write_data_lcd('1'); else write_data_lcd('0');
			goto_lcd(3,15); if (digitalRead(29)==1)	write_data_lcd('1'); else write_data_lcd('0');	
			
			goto_lcd(4,1); lcd_str(corr_rede);
			goto_lcd(4,4); lcd_str(corr_bat);
			
					
			break;
	case 1: // mostra outra tela a partir de comando de tecla
			break;
	}		
   usleep(70000);
 }
} 
 


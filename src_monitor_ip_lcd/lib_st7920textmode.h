// Biblioteca LCD ST7920 no modo texto
// Rudi @ 09/04/2020


// Pino  4 LCD funcao RS  ligado a Raspberry pino 24 WiringPi 10
// Pino  5 LCD funcao RW  ligado a Raspberry pino 19 WiringPi 12 
// Pino  6 LCD funcao EN  ligado a Raspberry pino 23 WiringPi 14 
// Pino 17 LCD funcao RST ligado a Raspberry pino 22 WiringPi  6 

void setbit(unsigned char a);
void clrbit(unsigned char a);
void write_ctr_lcd(unsigned char a);
void write_data_lcd(unsigned char a);
void goto_lcd(unsigned char l, unsigned char c );
void lcd_str(char s[]);
void lcd_bcd(unsigned char a);
void setup_rasp_lcd(void);

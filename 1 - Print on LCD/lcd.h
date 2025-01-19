#ifndef LCD_H_
#define LCD_H_

#define LCDPORT                          GPIO_PORTB_BASE
#define LCDPORTENABLE                    SYSCTL_PERIPH_GPIOB
#define RS                               GPIO_PIN_0
#define E                                GPIO_PIN_1
#define D4                               GPIO_PIN_4
#define D5                               GPIO_PIN_5
#define D6                               GPIO_PIN_6
#define D7                               GPIO_PIN_7

void Lcd_command(unsigned char);        //Sends a command to the LCD
void Lcd_clear(void);                   //Clears the LCD screen
void Lcd_Puts(char*);                   //Print string expression
void Lcd_Goto(char,char);               //Sends the courser to the desired location
void Lcd_init(void);                    //LCD initial settings
void Lcd_Putch(unsigned char);          //Print single character
#endif /* LCD_H_ */

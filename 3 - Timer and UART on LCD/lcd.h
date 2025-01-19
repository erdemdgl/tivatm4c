#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

// LCD Pin Tanımları
#define LCDPORT    GPIO_PORTB_BASE
#define RS         GPIO_PIN_0
#define E          GPIO_PIN_1
#define D4         GPIO_PIN_4
#define D5         GPIO_PIN_5
#define D6         GPIO_PIN_6
#define D7         GPIO_PIN_7

// Fonksiyon Prototipleri
void lcdkomut(unsigned char c);          // Komut gönderme
void lcdkarakteryaz(unsigned char c);    // Karakter yazma
void LCDilkayarlar();                    // LCD'yi başlatma ve ilk ayarlar
void LCDTemizle();                       // LCD ekranını temizleme
void LCDgit(unsigned char row, unsigned char col); // Belirli bir satır ve sütuna git
void lcdyaz(const char *str);            // LCD'ye string yazma
void lcdSayiyaz(int value);              // LCD'ye sayısal değer yazma

#endif /* LCD_H_ */

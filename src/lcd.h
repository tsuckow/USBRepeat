#include <sys/types.h>

//Commands
#define LCD_ON      0xAF

#define LCD_GLYPH_CANADA   4
#define LCD_GLYPH_PAPER    14
#define LCD_GLYPH_BATTERY1 19
#define LCD_GLYPH_BATTERY2 18
#define LCD_GLYPH_BATTERY3 20
#define LCD_GLYPH_BATTERY  21
#define LCD_GLYPH_COMPUTER 37
#define LCD_GLYPH_WIRELESS 48
#define LCD_GLYPH_SPEAKER1 54
#define LCD_GLYPH_SPEAKER  57
#define LCD_GLYPH_SPEAKER2 62
#define LCD_GLYPH_PHONE    70
#define LCD_GLYPH_MAIL     81
#define LCD_GLYPH_BELL     92
#define LCD_GLYPH_CLOCK    103
#define LCD_GLYPH_NOTICE   114
#define LCD_GLYPH_LOOP     124

void initLCD();
void lcdClear();
void lcdSetPixel( uint8_t val, uint8_t x, uint8_t y );
void lcdSetGlyph( uint8_t on, uint8_t glyph );

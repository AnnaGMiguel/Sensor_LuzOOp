#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"
#include "oled.h"


void oledClass(){
	oled_init();
}
void oledPrint( uint8_t buf[10] ){

	oled_clearScreen(OLED_COLOR_WHITE);
	oled_putString(1,1,  (uint8_t*)"LUM: ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);

	oled_fillRect((1+6*6),1, 80, 8, OLED_COLOR_WHITE);
	oled_putString((1+6*6),1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

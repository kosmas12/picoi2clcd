#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "picoi2clcd.h"

// By default these LCD display drivers are on bus address 0x3F
static int addr = 0x3F;

struct i2c_inst *i2cbus;

/* Set the I2C bus to use */
void lcd_seti2cbus(struct i2c_inst *i2cbusToUse) {
    i2cbus = i2cbusToUse;
}

/* Get the currently used I2C bus */
struct i2c_inst *lcd_geti2cbus() {
    return i2cbus;
}

/* Set I2C address to use */
void lcd_seti2caddr(int addrToUse) {
    addr = addrToUse;
}

/* Get the currently used I2C address */
int lcd_geti2caddr() {
    return addr;
}

/* Quick helper function for single byte transfers */
void i2c_write_byte(uint8_t val) {
#ifdef i2c_default
    i2c_write_blocking(i2cbus, addr, &val, 1, false);
#endif
}

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
#define DELAY_US 600
    sleep_us(DELAY_US);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t val, int mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

// go to location on LCD
void lcd_set_cursor(int line, int position) {
    int val;
    if (line == 0) {
       val = 0x80 + position;
    }
    else {
        val = 0xC0 + position;
    }
    lcd_send_byte(val, LCD_COMMAND);
}

static void inline lcd_char(char val) {
    lcd_send_byte(val, LCD_CHARACTER);
}

void lcd_string(const char *s) {
    while (*s) {
        lcd_char(*s++);
    }
}

void lcd_init(struct i2c_inst *i2cbusToUse, uint baudrate) {
    lcd_seti2cbus(i2cbusToUse);
    i2c_init(i2cbus, baudrate);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x02, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}

#include <pico/stdlib.h>
#include <hardware/i2c.h>
#include "../picoi2clcd.h"

#define I2C_SDA 1
#define I2C_SCL 2

int main() {
    stdio_init_all();
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    /* Optionally, set the I2C address before initializing
     * the LCD by calling lcd_seti2caddr(int addr).
     * The library default-initializes to address 0x3F.
     */

    lcd_init(i2c_default, 400 * 1000);
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_string("Hello World!");

    return 0;
}

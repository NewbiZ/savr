#include "uart.h"

#include <string.h>
#include <avr/power.h>

void clock_init()
{
    clock_prescale_set(clock_div_1);
}

int main()
{
    clock_init();
    uart_init(128, 1);

    const char* str = "> UART initialized\n";
    uart_write(str, strlen(str));

    while (1) {}
}

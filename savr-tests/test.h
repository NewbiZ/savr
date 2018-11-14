#include <avr/sleep.h>

#include <stdio.h>

void test();

static int __uart_putchar(char c, FILE* stream)
{
    if (c == '\n')
        __uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}

static FILE dbgstdout = \
    FDEV_SETUP_STREAM(__uart_putchar, NULL, _FDEV_SETUP_WRITE);

void test_failure(const char* msg)
{
    printf("NOK: %s\n", msg);
    sleep_cpu();
}

void test_init()
{
    stdout = &dbgstdout;
}

int main()
{
    test_init();

    test();

    sleep_cpu();

    __builtin_unreachable();
}

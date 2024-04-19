
#include "ft_printf.h"
#include <string.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

int main(int ac, char *av[])
{
    char *a = av[1];
    char b1 = a[0];
    char b2 = a[1];
    char b3 = a[2];
    char b4 = a[3];
    ft_printf("%d %u %c "BYTE_TO_BINARY_PATTERN"\n", b1, (unsigned char)b1, b1, BYTE_TO_BINARY(b1));
    ft_printf("%d %u %c\n", b2, (unsigned char)b2, b2);
    ft_printf("%d %u %c\n", b3, (unsigned char)b3, b3);
    ft_printf("%d %u %c\n", b4, (unsigned char)b4, b4);
    ft_printf("%d\n", strlen(av[1]));
    ft_printf("%s", av[1]);

    return 0;
}
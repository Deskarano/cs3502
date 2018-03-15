#ifndef CS3502_BASE_CONVERSIONS_H
#define CS3502_BASE_CONVERSIONS_H

#include <cstdio>

static unsigned int hex_to_dec(const char *hex, unsigned int length)
{
    unsigned int result = 0;

    for(int i = 0; i < length; i++)
    {
        int shift = 4 * (length - i - 1);

        if(hex[i] == '0') result += (0 << shift);
        if(hex[i] == '1') result += (1 << shift);
        if(hex[i] == '2') result += (2 << shift);
        if(hex[i] == '3') result += (3 << shift);
        if(hex[i] == '4') result += (4 << shift);
        if(hex[i] == '5') result += (5 << shift);
        if(hex[i] == '6') result += (6 << shift);
        if(hex[i] == '7') result += (7 << shift);
        if(hex[i] == '8') result += (8 << shift);
        if(hex[i] == '9') result += (9 << shift);
        if(hex[i] == 'A' || hex[i] == 'a') result += (10 << shift);
        if(hex[i] == 'B' || hex[i] == 'b') result += (11 << shift);
        if(hex[i] == 'C' || hex[i] == 'c') result += (12 << shift);
        if(hex[i] == 'D' || hex[i] == 'd') result += (13 << shift);
        if(hex[i] == 'E' || hex[i] == 'e') result += (14 << shift);
        if(hex[i] == 'F' || hex[i] == 'f') result += (15 << shift);
    }

    return result;
}

static char *dec_to_hex(int dec)
{
    auto result = new char[8];
    sprintf(result, "%08x", dec);
    return result;
}
#endif //CS3502_BASE_CONVERSIONS_H

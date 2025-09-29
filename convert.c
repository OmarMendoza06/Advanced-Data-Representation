#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "convert.h"

void oct_to_bin(const char* oct, char* out) {
    out[0] = '\0';

    for (int i = 0; oct[i] != '\0'; i++) {
        switch (oct[i]) {
        case '0': strcat(out, "000"); break;
        case '1': strcat(out, "001"); break;
        case '2': strcat(out, "010"); break;
        case '3': strcat(out, "011"); break;
        case '4': strcat(out, "100"); break;
        case '5': strcat(out, "101"); break;
        case '6': strcat(out, "110"); break;
        case '7': strcat(out, "111"); break;
        default:
            printf("Error: Invalid octal digit '%c'\n", oct[i]);
            out[0] = '\0';
            return;
        }
    }
}

void oct_to_hex(const char* oct, char* out) {
    char bin[100];
    oct_to_bin(oct, bin);

    int len = (int)strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[104];
    memset(padded, '0', pad);
    strcpy(padded + pad, bin);

    char* p = out;
    for (int i = 0; i < len + pad; i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++)
            val = (val << 1) | (padded[i + j] - '0');
        *p++ = (val < 10) ? '0' + val : 'A' + (val - 10);
    }
    *p = '\0';
    while (out[0] == '0' && out[1] != '\0') memmove(out, out + 1, strlen(out));
}

void hex_to_bin(const char* hex, char* out) {
    char* p = out;
    for (size_t i = 0; hex[i] != '\0'; i++) {
        char c = toupper((unsigned char)hex[i]);
        int d = (c <= '9') ? c - '0' : c - 'A' + 10;
        for (int bit = 3; bit >= 0; bit--)
            *p++ = (d & (1 << bit)) ? '1' : '0';
    }
    *p = '\0';
}

static void u32_to_bin(uint32_t val, char* out) {
    for (int i = 31; i >= 0; i--)
        out[31 - i] = (val & (1u << i)) ? '1' : '0';
    out[32] = '\0';
}


void to_sign_magnitude(int32_t n, char* out) {
    uint32_t mag = (n < 0) ? (uint32_t)(-n) : (uint32_t)n;
    u32_to_bin(mag, out);
    if (n < 0) out[0] = '1';
}

void to_ones_complement(int32_t n, char* out) {
    uint32_t val = (n >= 0) ? (uint32_t)n : ~((uint32_t)(-n));
    u32_to_bin(val, out);
}

void to_twos_complement(int32_t n, char* out) {
    u32_to_bin((uint32_t)n, out);
}


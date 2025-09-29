#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

int main(void) {
    FILE* file = fopen("a2_test.txt", "r");
    if (!file) {
        printf("Error: Could not open a2_test.txt\n");
        return 1;
    }

    char line[256];
    int total = 0;
    int passed = 0;

    while (fgets(line, sizeof line, file)) {
        line[strcspn(line, "\r\n")] = '\0';

        if (line[0] == '\0' || line[0] == '#')
            continue;

        char func[32] = "";
        char arg1[64] = "";
        char arg2[64] = "";
        char expected[65] = "";
        char result[128] = "";

        int count = sscanf(line, "%31s %63s %63s %64s", func, arg1, expected);
        if (count < 2) {
            printf("Warning: Unrecognized or malformed test line: %s\n", line);
            continue;
        }

        
        if (strcmp(func, "oct_to_bin") == 0 && count == 3) {
            oct_to_bin(arg1, result);
            total++;
            if (strcmp(result, expected) == 0) {
                printf("Test %d: oct_to_bin(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                    total, arg1, expected, result);
                passed++;
            }
            else {
                printf("Test %d: oct_to_bin(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                    total, arg1, expected, result);
            }
        }
        else if (strcmp(func, "oct_to_hex") == 0 && count == 3) {
            oct_to_hex(arg1, result);
            total++;
            if (strcmp(result, expected) == 0) {
                printf("Test %d: oct_to_hex(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                    total, arg1, expected, result);
                passed++;
            }
            else {
                printf("Test %d: oct_to_hex(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                    total, arg1, expected, result);
            }
		}
		else if (strcmp(func, "hex_to_bin") == 0 && count == 3) {
			hex_to_bin(arg1, result);
            total++;
            if (strcmp(result, expected) == 0) {
                printf("Test %d: hex_to_bin(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                    total, arg1, expected, result);
                passed++;
            }
            else {
                printf("Test %d: hex_to_bin(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                    total, arg1, expected, result);
            }
		}
		else if (strcmp(func, "to_sign_magnitude") == 0 && count == 3) {
			int32_t n = (int32_t)strtol(arg1, NULL, 10);
			to_sign_magnitude(n, result);
            total++;
            if (strcmp(result, expected) == 0) {
                printf("Test %d: to_sign_magnitude(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                    total, arg1, expected, result);
                passed++;
            }
            else {
                printf("Test %d: to_sign_magnitude(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                    total, arg1, expected, result);
            }
		}
		else if (strcmp(func, "to_ones_complement") == 0 && count == 3) {
			int32_t n = (int32_t)strtol(arg1, NULL, 10);
			to_ones_complement(n, result);
            total++;
            if (strcmp(result, expected) == 0) {
                printf("Test %d: to_ones_complement(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                    total, arg1, expected, result);
                passed++;
            }
            else {
                printf("Test %d: to_ones_complement(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                    total, arg1, expected, result);
            }
		}
		else if (strcmp(func, "to_twos_complement") == 0 && count == 3) {
			int32_t n = (int32_t)strtol(arg1, NULL, 10);
			to_twos_complement(n, result);
            total++;
            if (strcmp(result, expected) == 0) {
                printf("Test %d: to_twos_complement(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                    total, arg1, expected, result);
                passed++;
            }
            else {
                printf("Test %d: to_twos_complement(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                    total, arg1, expected, result);
            }
		}
		else {
			printf("Warning: Unrecognized or malformed test line: %s\n", line);
		}
	}

    fclose(file);
    printf("Summary: %d/%d tests passed\n", passed, total);
    return 0;
}

#include "common.h"
#include <math.h>
#include <stdio.h>

long task1(char **lines, int count) {
  long result = 0;
  for (int i = 0; i < count; i++) {
    char *line = lines[i];
    int length = strlen(line);
    int max_first = line[0] - '0';
    int max_first_index = 0;
    for (int j = 0; j < length - 1; j++) {
      int current = line[j] - '0';
      if (current > max_first) {
        max_first = current;
        max_first_index = j;
      }
    }

    int max_second = line[max_first_index + 1] - '0';
    for (int j = max_first_index + 1; j < length; j++) {
      int current = line[j] - '0';
      if (current > max_second) {
        max_second = current;
      }
    }

    result += max_first * 10 + max_second;
  }
  return result;
}

#define BATTERIES_COUNT 12

long task2(char **lines, int count) {
  long result = 0;
  for (int line_i = 0; line_i < count; line_i++) {
    char *line = lines[line_i];
    long bank_joltage = 0;
    int length = strlen(line);
    int joltage_start_index = 0;
    for (int battery_i = 0; battery_i < BATTERIES_COUNT; battery_i++) {
      int max_joltage = 0;
      for (int joltage_i = joltage_start_index;
           joltage_i <= length - BATTERIES_COUNT + battery_i; joltage_i++) {
        int joltage = line[joltage_i] - '0';
        if (joltage > max_joltage) {
          max_joltage = joltage;
          joltage_start_index = joltage_i + 1;
        }
      }
      int exp = BATTERIES_COUNT - battery_i - 1;
      bank_joltage += powl(10, exp) * max_joltage;
    }
    result += bank_joltage;
  }
  return result;
}

BEGIN_SOLUTION_MAIN(argc, argv)
ASSERT_VALID_INPUT(argc, argv);

int count;
char **lines = read_lines(argv[1], &count);
if (!lines)
  return 1;

printf("Part 1: %ld\n", task1(lines, count));
printf("Part 2: %ld\n", task2(lines, count));

free_lines(lines, count);
return 0;
END_SOLUTION_MAIN

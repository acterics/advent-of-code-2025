#include "common.h"
#include <stdio.h>

int count_problems(const char *line);
long get_problem_number(char **lines, int number_index, int digits_count);

long task1(char **lines, int count) {
  long result = 0;
  int problems_count = 0;
  long **problems = NULL;

  for (int i = 0; i < count; i++) {
    char *line = lines[i];
    char *line_copy = strdup(line);
    if (i == count - 1) {
      char *token = strtok(line_copy, " ");
      int j = 0;

      while (token) {
        long problem_result = problems[j][0];
        if (token[0] == '+') {
          for (int k = 1; k < count - 1; k++) {
            problem_result += problems[j][k];
          }
        } else if (token[0] == '*') {
          for (int k = 1; k < count - 1; k++) {
            problem_result *= problems[j][k];
          }
        }
        result += problem_result;
        token = strtok(NULL, " ");
        j++;
      }

    } else {
      if (!problems) {
        if (!problems_count) {
          problems_count = count_problems(line);
        }
        problems = malloc(problems_count * sizeof(long *));
        for (int j = 0; j < problems_count; j++) {
          problems[j] = malloc((count - 1) * sizeof(long));
        }
      }
      char *token = strtok(line_copy, " ");
      int j = 0;
      while (token) {
        problems[j][i] = atol(token);
        j++;
        token = strtok(NULL, " ");
      }
    }
    free(line_copy);
  }

  for (int i = 0; i < problems_count; i++) {
    free(problems[i]);
  }
  free(problems);

  return result;
}

long task2(char **lines, int count) {
  long result = 0;
  char *operators_line = strdup(lines[count - 1]);
  char *token = strtok(operators_line, " ");
  int char_index = 0;

  while (token) {
    int problem_finished = 0;
    long problem_result = -1;

    while (!problem_finished) {
      long number = get_problem_number(lines, char_index, count - 1);
      if (number == 0) {
        problem_finished = 1;
      } else {
        if (problem_result == -1) {
          problem_result = number;
        } else if (token[0] == '+') {
          problem_result += number;
        } else if (token[0] == '*') {
          problem_result *= number;
        }
      }
      char_index++;
    }
    result += problem_result;
    token = strtok(NULL, " ");
  }

  free(operators_line);
  return result;
}

long get_problem_number(char **lines, int number_index, int digits_count) {
  long number = 0;
  for (int i = 0; i < digits_count; i++) {
    char digit_char = lines[i][number_index];
    if (digit_char >= '0' && digit_char <= '9') {
      long digit = digit_char - '0';
      number = number * 10 + digit;
    }
  }
  return number;
}

int count_problems(const char *line) {
  char *line_copy = strdup(line);
  int count = 0;

  char *token = strtok(line_copy, " ");
  while (token) {
    count++;
    token = strtok(NULL, " ");
  }
  free(line_copy);
  return count;
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

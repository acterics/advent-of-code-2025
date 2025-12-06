#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROLL '@'
#define MAX_ROLLS 4
#define OFFSETS 8

int get_adjacent_rolls_count(char **lines, int rows, int columns, int row,
                             int col);

long task1(char **lines, int count) {
  int result = 0;
  for (int i = 0; i < count; i++) {
    const char *line = lines[i];
    int line_len = strlen(line);
    for (int j = 0; j < line_len; j++) {
      char value = line[j];
      if (value == ROLL) {
        int adjacent_rolls_count =
            get_adjacent_rolls_count(lines, count, line_len, i, j);
        if (adjacent_rolls_count < MAX_ROLLS) {
          result++;
        }
      }
    }
  }
  return result;
}

// First is row offset, second is column offset
static int CELL_OFFSETS[OFFSETS][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};

int get_adjacent_rolls_count(char **lines, int rows, int columns, int row,
                             int col) {
  int rolls_count = 0;
  for (int i = 0; i < OFFSETS; i++) {
    int adjacent_row = row + CELL_OFFSETS[i][0];
    int adjacent_column = col + CELL_OFFSETS[i][1];

    if (adjacent_row >= 0 && adjacent_row < rows && adjacent_column >= 0 &&
        adjacent_column < columns) {
      char value = lines[adjacent_row][adjacent_column];
      if (value == ROLL) {
        rolls_count += 1;
      }
    }
  }
  return rolls_count;
}

long task2(char **lines, int count) {
  int result = 0;
  int *line_stack = malloc(2 * count * sizeof(int));
  int line_stack_top = -1;

  for (int i = count - 1; i >= 0; i--) {
    line_stack[++line_stack_top] = i;
  }
  int min_row_with_rolls = 0;

  while (line_stack_top >= 0) {
    int i = line_stack[line_stack_top--];
    char *line = lines[i];
    int line_len = strlen(line);
    int *char_stack = malloc(2 * line_len * sizeof(int));
    int char_stack_top = -1;
    int removed_rolls_count = 0;
    int rolls_count = 0;

    for (int j = line_len - 1; j >= 0; j--) {
      char_stack[++char_stack_top] = j;
    }

    while (char_stack_top >= 0) {
      int j = char_stack[char_stack_top--];
      char value = line[j];
      if (value == ROLL) {
        rolls_count++;
        int adjacent_rolls_count =
            get_adjacent_rolls_count(lines, count, line_len, i, j);
        if (adjacent_rolls_count < MAX_ROLLS) {
          lines[i][j] = 'x';
          if (j > 0) {
            char_stack[++char_stack_top] = j - 1;
          }
          if (removed_rolls_count == 0) {
            if (i < count - 1) {
              line_stack[++line_stack_top] = i + 1;
            }
            if (i > min_row_with_rolls) {
              line_stack[++line_stack_top] = i - 1;
            }
          }
          removed_rolls_count++;
        }
      }
    }
    free(char_stack);
    if (rolls_count == 0 && i == min_row_with_rolls) {
      min_row_with_rolls++;
    }

    result += removed_rolls_count;
  }

  free(line_stack);

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

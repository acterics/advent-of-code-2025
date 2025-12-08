#include "common.h"
#include <stdio.h>
#include <stdlib.h>

long *parse_range(const char *line);
int is_ingredient_is_fresh(long ingredient_id, RangeNode *ranges);
long count_ingredients(RangeNode *ranges);

long task1(char **lines, int count) {
  int result = 0;
  int is_parsing_available_ingredients = 0;
  RangeNode *ranges = NULL;
  for (int i = 0; i < count; i++) {
    char *line = lines[i];
    if (line[0] ==
        '\0') { // Empty line is delimiter between available and fresh ranges
      // Start parsing available ids
      is_parsing_available_ingredients = 1;
      continue;
    } else {
      if (is_parsing_available_ingredients) {
        // Parse available ids
        long ingredient_id = atol(line);
        if (is_ingredient_is_fresh(ingredient_id, ranges)) {
          result++;
        }
      } else {
        // Parse fresh ranges
        long *range = parse_range(line);
        ranges = insert_range(ranges, range[0], range[1]);
        free(range);
      }
    }
  }
  free_ranges(ranges);
  return result;
}

long task2(char **lines, int count) {
  RangeNode *ranges = NULL;
  for (int i = 0; i < count; i++) {
    char *line = lines[i];
    // Empty line is delimiter between available and fresh ranges
    if (line[0] == '\0') {
      break;
      continue;
    } else {
      // Parse fresh ranges
      long *range = parse_range(line);
      ranges = insert_range(ranges, range[0], range[1]);
      free(range);
    }
  }
  long result = count_ingredients(ranges);
  free_ranges(ranges);
  return result;
}

long *parse_range(const char *line) {
  char *dash = strchr(line, '-');
  if (!dash) {
    fprintf(stderr, "Invalid range: %s\n", line);
    return NULL;
  }
  // Range int bounds
  long *range = malloc(2 * sizeof(long));
  range[0] = atol(line);     // min
  range[1] = atol(dash + 1); // max
  return range;
}

long count_ingredients(RangeNode *ranges) {
  long count = 0;
  RangeNode *current = ranges;
  while (current) {
    long range_sum = current->range_max - current->range_min + 1;
    count += range_sum;
    current = current->next;
  }
  return count;
}

int is_ingredient_is_fresh(long ingredient_id, RangeNode *ranges) {
  return contains_in_ranges(ranges, ingredient_id);
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

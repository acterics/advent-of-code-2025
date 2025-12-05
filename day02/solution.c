#include "common.h"
#include <math.h>
#include <stdio.h>

long generate_task1_invalid_id(long repeating_part);
long generate_task2_invalid_id(long repeating_part, int repeats);
long task_2_range_sum(long range_min, long range_max);

long task1(char **ranges, int count) {
  long result = 0;

  for (int i = 0; i < count; i++) {
    char *range = ranges[i];
    char *dash = strchr(range, '-');
    if (!dash) {
      fprintf(stderr, "Invalid range: %s\n", range);
      return 1;
    }
    // Range int bounds
    long range_min = atol(range);
    long range_max = atol(dash + 1);

    int end_len = strlen(dash + 1);
    int start_len = strlen(range) - end_len - 1;

    // Only half of the range value could be a repeating part
    int min_repeating_part_len = start_len / 2;
    int max_repeating_part_len = end_len / 2;

    // Range with odd number of min and max bounds and without crossing numbers
    // with even number of digits could not have any invalid ids
    if (start_len % 2 != 0 && end_len % 2 != 0 &&
        abs(min_repeating_part_len - max_repeating_part_len) <= 1) {
      continue;
    }

    // Extract min repeating part from the range
    char *range_min_repeating_part_str = malloc(min_repeating_part_len + 1);
    range_min_repeating_part_str[min_repeating_part_len] = '\0';
    for (int j = 0; j < min_repeating_part_len; j++) {
      range_min_repeating_part_str[j] = range[j];
    }

    // Extract max repeating part from the range
    char *range_max_repeating_part_str = malloc(max_repeating_part_len + 1);
    range_max_repeating_part_str[max_repeating_part_len] = '\0';
    for (int j = 0; j < max_repeating_part_len; j++) {
      range_max_repeating_part_str[j] = dash[j + 1];
    }

    // Convert min and max repeating parts to ints
    int range_min_repeating_part = atoi(range_min_repeating_part_str);
    int range_max_repeating_part = atoi(range_max_repeating_part_str);

    // Adjust max repeating part if it's less than min repeating part (e.g.
    // range: 66-115 -> repeating parts range -> 6-9)
    if (range_max_repeating_part < range_min_repeating_part) {
      range_max_repeating_part = 1;
      for (int j = 0; j < max_repeating_part_len; j++) {
        range_max_repeating_part *= 10;
      }
      range_max_repeating_part -= 1;
    }

    // Check all possible invalid IDs in the range iterating by repeating part
    long current_repeating_part = range_min_repeating_part;
    do {

      long invalid_id = generate_task1_invalid_id(current_repeating_part);
      if (invalid_id >= range_min && invalid_id <= range_max) {
        result += invalid_id;
      }
      current_repeating_part++;
    } while (current_repeating_part <= range_max_repeating_part);

    free(range_min_repeating_part_str);
    free(range_max_repeating_part_str);
  }

  return result;
}

long task2(char **ranges, int count) {
  long result = 0;

  for (int i = 0; i < count; i++) {
    char *range = ranges[i];
    char *dash = strchr(range, '-');
    if (!dash) {
      fprintf(stderr, "Invalid range: %s\n", range);
      return 1;
    }
    // Range int bounds
    long range_min = atol(range);
    long range_max = atol(dash + 1);

    result += task_2_range_sum(range_min, range_max);
  }

  return result;
}


long prefix(long number, int length) {
  int number_length = log10l(number) + 1;
  return number / powl(10, number_length - length);
}

/*
V - value
L - length of the value
RL - length of repeating part
RP - repeating part
RC - repeats count
[1..len/2] -> range of possible repeating parts; example: 1234599999 -> 1(RP =
10), 12 (RP = 5), 12345(RP = 2);

L % RL == 0 -> valid repeating part;
RC = L / RL;
Duplication inside range resolved by using binary tree to store invalid ids

We need to find ranges of repeating parts with same repeatings count for
range min and range max [1234599999..[2345699999]] -> [1..2](RP = 10),
[12..23](RP = 5), [12345..23456](RP = 2) Then generate invalid ids for each
values in the ranges with corresponding repeats count and sum up those ids
 */
long task_2_range_sum(long range_min, long range_max) {
  long result = 0;

  int range_min_len = log10l(range_min) + 1;
  int range_max_len = log10l(range_max) + 1;

  int range_len_diff = range_max_len - range_min_len;

  // Normalizing range bound sizes: [23..134] -> [23..99] + [100..134]
  for (int i = 0; i < range_len_diff; i++) {
    long first_subrange_min = range_min;
    long first_subrange_min_len = log10l(first_subrange_min) + 1;
    long first_subrange_max = powl(10, first_subrange_min_len) - 1;

    result += task_2_range_sum(first_subrange_min, first_subrange_max);
    range_min = first_subrange_max + 1;
  }

  // Using binary tree to store invalid ids to avoid duplicates
  TreeNode *invalid_ids = NULL;
  for (int i = 1; i <= range_max_len / 2; i++) {
    if (range_max_len % i != 0) {
      continue;
    }

    int repeats_count = range_max_len / i;
    long repeating_part_range_min = prefix(range_min, i);
    long repeating_part_range_max = prefix(range_max, i);

    for (long j = repeating_part_range_min; j <= repeating_part_range_max;
         j++) {
      long invalid_id = generate_task2_invalid_id(j, repeats_count);
      int contains_invalid_id = contains_tree(invalid_ids, invalid_id);
      if (invalid_id >= range_min && invalid_id <= range_max &&
          !contains_invalid_id) {
        result += invalid_id;
        invalid_ids = insert_tree(invalid_ids, invalid_id, 0);
      }
    }
  }
  free(invalid_ids);
  return result;
}

long generate_task1_invalid_id(long repeating_part) {
  long length = log10l(repeating_part) + 1;
  return repeating_part * powl(10, length) + repeating_part;
}

long generate_task2_invalid_id(long repeating_part, int repeats) {
  long invalid_id = 0;
  long length = log10l(repeating_part) + 1;
  long base_power = powl(10, length);
  for (int i = 0; i < repeats; i++) {
    invalid_id += repeating_part * powl(base_power, i);
  }

  return invalid_id;
}

char **parse_task(const char *input_filename, int *count) {
  char *content = read_file(input_filename);
  /* Count ranges */
  int n = 0;
  for (char *p = content; *p; p++) {
    if (*p == ',')
      n++;
  }
  if (content[strlen(content) - 1] != ',')
    n++;

  char **lines = malloc(n * sizeof(char *));
  if (!lines) {
    free(content);
    *count = 0;
    return NULL;
  }

  /* Split into lines */
  int i = 0;
  char *line = strtok(content, ",");
  while (line && i < n) {
    lines[i] = strdup(line);
    line = strtok(NULL, ",");
    i++;
  }

  free(content);
  *count = i;
  return lines;
}

BEGIN_SOLUTION_MAIN(argc, argv)
ASSERT_VALID_INPUT(argc, argv);

int count;
char **ranges = parse_task(argv[1], &count);
if (!ranges)
  return 1;

printf("Part 1: %ld\n", task1(ranges, count));
printf("Part 2: %ld\n", task2(ranges, count));

free_lines(ranges, count);
return 0;
END_SOLUTION_MAIN

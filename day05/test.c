#include "test.h"
#include "common.h"
#include <stdio.h>

long task1(char **lines, int count);
long task2(char **lines, int count);

static int test_part1(char *filename, long expected) {
  int count;
  char **lines = read_lines(filename, &count);
  if (!lines) {
    printf(RED "Could not read sample.txt\n" RESET);
    return 1;
  }

  long result = task1(lines, count);
  free_lines(lines, count);

  ASSERT_EQ(expected, result);
  return 0;
}

static int test_part1_sample(void) {
  return test_part1("day05/inputs/sample.txt", 3);
}

static int test_part1_sample2(void) {
  return test_part1("day05/inputs/sample-2.txt", 9);
}

static int test_part2_sample(void) {
  int count;
  char **lines = read_lines("day05/inputs/sample.txt", &count);
  if (!lines) {
    printf(RED "Could not read sample.txt\n" RESET);
    return 1;
  }

  long result = task2(lines, count);
  free_lines(lines, count);

  ASSERT_EQ(14, result);
  return 0;
}

int main(void) {
  printf("Day 05 Tests\n");
  printf("============\n");

  RUN_TEST(test_part1_sample);
  RUN_TEST(test_part1_sample2);
  RUN_TEST(test_part2_sample);

  TEST_SUMMARY();
}

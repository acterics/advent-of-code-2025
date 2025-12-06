#include <stdio.h>
#include "common.h"
#include "test.h"

long task1(char** lines, int count);
long task2(char** lines, int count);

static int test_part1_sample(void) {
    int count;
    char** lines = read_lines("day04/inputs/sample.txt", &count);
    if (!lines) {
        printf(RED "Could not read sample.txt\n" RESET);
        return 1;
    }

    long result = task1(lines, count);
    free_lines(lines, count);

    ASSERT_EQ(13, result);
    return 0;
}

static int test_part2_sample(void) {
    int count;
    char** lines = read_lines("day04/inputs/sample.txt", &count);
    if (!lines) {
        printf(RED "Could not read sample.txt\n" RESET);
        return 1;
    }

    long result = task2(lines, count);
    free_lines(lines, count);

    ASSERT_EQ(43, result);
    return 0;
}

int main(void) {
    printf("Day 04 Tests\n");
    printf("============\n");

    RUN_TEST(test_part1_sample);
    RUN_TEST(test_part2_sample);

    TEST_SUMMARY();
}


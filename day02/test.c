#include <stdio.h>
#include "common.h"
#include "test.h"

long task1(char** lines, int count);
long task2(char** lines, int count);
char** parse_task(const char* input_filename, int* count);
long generate_task2_invalid_id(long repeating_part, int repeats);
long generate_task1_invalid_id(long repeating_part);
long atol_from_substr(const char* str, int start, int end);
long prefix(long number, int length);

static int test_task1(const char* input, long expected) {
    int count;
    
    char** parsed = parse_task(input, &count);
    if (!parsed) {
        printf(RED "Could not read sample.txt\n" RESET);
        return 1;
    }

    long result = task1(parsed, count);
    free_lines(parsed, count);

    ASSERT_EQ(expected, result);
    return 0;

}

static int test_task2(const char* input, long expected) {
    int count;
    
    char** parsed = parse_task(input, &count);
    if (!parsed) {
        printf(RED "Could not read sample.txt\n" RESET);
        return 1;
    }

    long result = task2(parsed, count);
    free_lines(parsed, count);

    ASSERT_EQ(expected, result);
    return 0;

}


static int test_part1_sample(void) {
    return test_task1("day02/inputs/sample.txt", 1227775554);
}
static int test_part1_sample_2(void) {
    return test_task1("day02/inputs/sample-2.txt", 1227775785);
}

static int test_part1_sample_3(void) {
    return test_task1("day02/inputs/sample-3.txt", 1227843657);
}

static int test_part2_sample(void) {
    return test_task2("day02/inputs/sample.txt", 4174379265);
}

static int test_part1_generate_invalid_id(void) {
    ASSERT_EQ(11, generate_task1_invalid_id(1));
    ASSERT_EQ(1212, generate_task1_invalid_id(12));
    ASSERT_EQ(123123, generate_task1_invalid_id(123));
    return 0;
}

static int test_part2_generate_invalid_id(void) {
    ASSERT_EQ(1, generate_task2_invalid_id(1, 1));
    ASSERT_EQ(22, generate_task2_invalid_id(2, 2));
    ASSERT_EQ(22, generate_task2_invalid_id(22, 1));
    ASSERT_EQ(11111, generate_task2_invalid_id(1, 5));
    ASSERT_EQ(232323, generate_task2_invalid_id(23, 3));
    ASSERT_EQ(123123, generate_task2_invalid_id(123, 2));
    ASSERT_EQ(2313231323132313, generate_task2_invalid_id(2313, 4));
    return 0;
}

static int test_part2_prefix(void) {
    ASSERT_EQ(1, prefix(123, 1));
    ASSERT_EQ(12, prefix(123, 2));
    ASSERT_EQ(123, prefix(123, 3));
    return 0;
}


int main(void) {
    printf("Day 02 Tests\n");
    printf("============\n");

    RUN_TEST(test_part1_sample);
    RUN_TEST(test_part1_sample_2);
    RUN_TEST(test_part1_sample_3);
    RUN_TEST(test_part1_generate_invalid_id);
    RUN_TEST(test_part2_sample);
    RUN_TEST(test_part2_generate_invalid_id);
    RUN_TEST(test_part2_prefix);
    TEST_SUMMARY();
}


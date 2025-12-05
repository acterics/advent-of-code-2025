#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

static int tests_run = 0;
static int tests_passed = 0;

#define ASSERT_EQ(expected, actual) do { \
    if ((expected) != (actual)) { \
        printf(RED "  FAIL: %s:%d: expected %lld, got %lld\n" RESET, \
               __FILE__, __LINE__, (long long)(expected), (long long)(actual)); \
        return 1; \
    } \
} while(0)

#define ASSERT_STR_EQ(expected, actual) do { \
    if (strcmp((expected), (actual)) != 0) { \
        printf(RED "  FAIL: %s:%d: expected \"%s\", got \"%s\"\n" RESET, \
               __FILE__, __LINE__, (expected), (actual)); \
        return 1; \
    } \
} while(0)

#define ASSERT_TRUE(condition) do { \
    if (!(condition)) { \
        printf(RED "  FAIL: %s:%d: condition is false\n" RESET, \
               __FILE__, __LINE__); \
        return 1; \
    } \
} while(0)

#define RUN_TEST(test_func) do { \
    tests_run++; \
    printf("  Running %s... ", #test_func); \
    if (test_func() == 0) { \
        printf(GREEN "OK\n" RESET); \
        tests_passed++; \
    } \
} while(0)

#define TEST_SUMMARY() do { \
    printf("\n%d/%d tests passed\n", tests_passed, tests_run); \
    return (tests_passed == tests_run) ? 0 : 1; \
} while(0)

#endif /* TEST_H */


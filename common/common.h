#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Read entire file into a string. Caller must free the result. */
char *read_file(const char *filename);

/* Read file as array of lines. Sets *count to number of lines. Caller must
 * free. */
char **read_lines(const char *filename, int *count);

/* Free lines array */
void free_lines(char **lines, int count);

#ifndef TESTING
#define BEGIN_SOLUTION_MAIN(argc, argv) int main(int argc, char **argv) {
#define END_SOLUTION_MAIN }
#else
#define BEGIN_SOLUTION_MAIN(argc, argv)                                        \
  int _ignored_main(int argc, char **argv) {
#define END_SOLUTION_MAIN }
#endif

#define ASSERT_VALID_INPUT(argc, argv)                                         \
  if (argc < 2) {                                                              \
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);                      \
    return 1;                                                                  \
  }

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

typedef struct TreeNode {
  long value;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *create_node(long value);
TreeNode *insert_tree(TreeNode *root, long value, int allow_duplicates);
int contains_tree(TreeNode *root, long value);
long sum_tree(TreeNode *root);
void free_tree(TreeNode *root);

typedef struct RangeNode {
  long range_min;
  long range_max;

  struct RangeNode *next;

} RangeNode;

RangeNode *create_range_node(long min, long max);
RangeNode *insert_range(RangeNode *root, long min, long max);
int contains_in_ranges(RangeNode *root, long value);
void print_ranges(RangeNode *root);
void free_ranges(RangeNode *root);

#endif /* COMMON_H */

#include "common.h"

char *read_file(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(filename);
    return NULL;
  }

  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *content = malloc(size + 1);
  if (!content) {
    fclose(f);
    return NULL;
  }

  fread(content, 1, size, f);
  content[size] = '\0';
  fclose(f);

  return content;
}

char **read_lines(const char *filename, int *count) {
  char *content = read_file(filename);
  if (!content) {
    *count = 0;
    return NULL;
  }

  /* Count lines */
  int n = 0;
  for (char *p = content; *p; p++) {
    if (*p == '\n')
      n++;
  }
  if (strlen(content) > 0 && content[strlen(content) - 1] != '\n')
    n++;

  char **lines = malloc(n * sizeof(char *));
  if (!lines) {
    free(content);
    *count = 0;
    return NULL;
  }

  /* Split into lines */
  int i = 0;
  char *start = content;
  char *p = content;
  while (*p && i < n) {
    if (*p == '\n') {
      *p = '\0';
      lines[i] = strdup(start);
      start = p + 1;
      i++;
    }
    p++;
  }
  /* Handle last line without trailing newline */
  if (start < p && i < n) {
    lines[i] = strdup(start);
    i++;
  }

  free(content);
  *count = i;
  return lines;
}

void free_lines(char **lines, int count) {
  for (int i = 0; i < count; i++) {
    free(lines[i]);
  }
  free(lines);
}

// BINARY TREE

TreeNode *create_node(long value) {
  TreeNode *node = malloc(sizeof(TreeNode));
  if (!node)
    return NULL;

  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

TreeNode *insert_tree(TreeNode *root, long value, int allow_duplicates) {
  TreeNode *current = root;
  TreeNode *parent = NULL;

  // Find the insertion point
  while (current != NULL) {
    parent = current;
    if (value < current->value) {
      current = current->left;
    } else if (value == current->value) {
      if (!allow_duplicates) {
        return root; // Don't insert duplicates
      }
      current = current->left; // Insert duplicates to the left
    } else {
      current = current->right;
    }
  }

  // Create new node
  TreeNode *new_node = create_node(value);
  if (!new_node)
    return root;

  // Insert the new node
  if (parent == NULL) {
    return new_node; // Tree was empty
  } else if (value < parent->value) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  return root;
}

int contains_tree(TreeNode *root, long value) {
  TreeNode *current = root;

  while (current != NULL) {
    if (value == current->value) {
      return 1;
    } else if (value < current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return 0;
}

long sum_tree(TreeNode *root) {
  if (root == NULL) {
    return 0;
  }

  return root->value + sum_tree(root->left) + sum_tree(root->right);
}

void free_tree(TreeNode *root) {
  if (root == NULL) {
    return;
  }

  free_tree(root->left);
  free_tree(root->right);
  free(root);
}

RangeNode *create_range_node(long min, long max) {
  RangeNode *node = malloc(sizeof(RangeNode));
  if (!node)
    return NULL;

  node->range_min = min;
  node->range_max = max;
  node->next = NULL;
  return node;
}
RangeNode *insert_range(RangeNode *root, long min, long max) {
  if (!root) {
    return create_range_node(min, max);
  }
  RangeNode *current = root;
  RangeNode *prev = NULL;
  // Find the position where we need to insert/merge
  // Skip nodes that come entirely before our range and don't overlap
  while (current && current->range_max < min - 1) {
    prev = current;
    current = current->next;
  }
  // If we've passed all nodes, append at the end
  if (!current) {
    RangeNode *new_node = create_range_node(min, max);
    prev->next = new_node;
    return root;
  }

  // If our range comes entirely before current node (no overlap)
  if (max < current->range_min - 1) {
    RangeNode *new_node = create_range_node(min, max);
    new_node->next = current;
    if (prev) {
      prev->next = new_node;
      return root;
    }
    return new_node; // New head
  }
  // We have overlap/adjacency - need to merge
  // Expand current node to include our range
  current->range_min = MIN(current->range_min, min);
  current->range_max = MAX(current->range_max, max);
  // Now merge any subsequent overlapping nodes
  while (current->next && current->next->range_min <= current->range_max + 1) {
    RangeNode *to_remove = current->next;
    current->range_max = MAX(current->range_max, to_remove->range_max);
    current->next = to_remove->next;
    free(to_remove);
  }

  return root;
}

int contains_in_ranges(RangeNode *root, long value) {
  RangeNode *current = root;

  while (current) {
    if (value >= current->range_min && value <= current->range_max) {
      return 1; // Found in this range
    }
    current = current->next;
  }

  return 0;
}

void print_ranges(RangeNode *root) {
  RangeNode *current = root;
  int i = 0;

  while (current) {
    printf("Range %d: %ld..%ld\n", i++, current->range_min, current->range_max);
    current = current->next;
  }
}

void free_ranges(RangeNode *root) {
  RangeNode *current = root;
  while (current) {
    RangeNode *next = current->next;
    free(current);
    current = next;
  }
}

int is_ranges_overlap(long lmin, long lmax, long rmin, long rmax) {
  return lmin <= rmax + 1 && rmin <= lmax + 1;
}
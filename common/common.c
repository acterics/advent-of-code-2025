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
  if (content[strlen(content) - 1] != '\n')
    n++;

  char **lines = malloc(n * sizeof(char *));
  if (!lines) {
    free(content);
    *count = 0;
    return NULL;
  }

  /* Split into lines */
  int i = 0;
  char *line = strtok(content, "\n");
  while (line && i < n) {
    lines[i] = strdup(line);
    line = strtok(NULL, "\n");
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
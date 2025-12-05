#include "common.h"

char* read_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror(filename);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* content = malloc(size + 1);
    if (!content) {
        fclose(f);
        return NULL;
    }

    fread(content, 1, size, f);
    content[size] = '\0';
    fclose(f);

    return content;
}

char** read_lines(const char* filename, int* count) {
    char* content = read_file(filename);
    if (!content) {
        *count = 0;
        return NULL;
    }

    /* Count lines */
    int n = 0;
    for (char* p = content; *p; p++) {
        if (*p == '\n') n++;
    }
    if (content[strlen(content) - 1] != '\n') n++;

    char** lines = malloc(n * sizeof(char*));
    if (!lines) {
        free(content);
        *count = 0;
        return NULL;
    }

    /* Split into lines */
    int i = 0;
    char* line = strtok(content, "\n");
    while (line && i < n) {
        lines[i] = strdup(line);
        line = strtok(NULL, "\n");
        i++;
    }

    free(content);
    *count = i;
    return lines;
}

void free_lines(char** lines, int count) {
    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);
}


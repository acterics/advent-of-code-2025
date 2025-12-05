#include <stdio.h>
#include "common.h"

#define DIAL_SIZE 100

long task1(char** lines, int count) {
    
    int position = 50;
    int result = 0;
    
    for (int i = 0; i < count; i++) {
        int rotation = atoi(&lines[i][1]);
        if (lines[i][0] == 'L') {
            position = ((position + DIAL_SIZE) - (rotation % DIAL_SIZE)) % DIAL_SIZE;
        } else if (lines[i][0] == 'R') {
            position = (position + rotation) % DIAL_SIZE;
        }
        if (position == 0) {
            result++;
        }
    }

    return result;
}

long task2(char** lines, int count) {
    int position = 50;
    int result = 0;
    for (int i = 0; i < count; i++) {
        int rotation = atoi(&lines[i][1]);
        int full_rotations = rotation / DIAL_SIZE;
        int remaind_rotation = rotation % DIAL_SIZE;

        result += full_rotations;

        int new_position;
        if (lines[i][0] == 'L') {
            new_position = ((position + DIAL_SIZE) - remaind_rotation) % DIAL_SIZE;
            if (position != 0 && position - remaind_rotation <= 0) {
                result++;
            }
        } else if (lines[i][0] == 'R') {
            new_position = (position + remaind_rotation) % DIAL_SIZE;
            if (position + remaind_rotation >= DIAL_SIZE) {
                result++;
            }
        } else {
            fprintf(stderr, "Unexpected input command: %s\n", lines[i]);
            return 1;
        }
        position = new_position;
    }

    return result;
}

BEGIN_SOLUTION_MAIN(argc, argv)
    ASSERT_VALID_INPUT(argc, argv);

    int count;
    char** lines = read_lines(argv[1], &count);
    if (!lines) return 1;

    printf("Part 1: %ld\n", task1(lines, count));
    printf("Part 2: %ld\n", task2(lines, count));

    free_lines(lines, count);
    return 0;
END_SOLUTION_MAIN


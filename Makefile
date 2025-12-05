CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g
COMMON = common/common.c

day%/solution: day%/solution.c $(COMMON)
	$(CC) $(CFLAGS) -I common $^ -o $@

run-day%: day%/solution
	./$< day$*/inputs/input.txt

day%/test: day%/test.c day%/solution.c $(COMMON)
	$(CC) $(CFLAGS) -I common -D TESTING $^ -o $@

test-day%: day%/test
	./$<

test:
	@for d in day*/; do \
		if [ -f "$$d/test.c" ]; then \
			echo "Testing $$d"; \
			$(MAKE) test-$$(basename $$d); \
		fi \
	done

clean:
	rm -f day*/solution day*/test

.PHONY: test clean

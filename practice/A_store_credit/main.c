#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SCANF(fmt, n, args...)						\
do {									\
	int __rc = scanf(fmt, args);					\
	if (__rc != (n))						\
		die("scanf: wanted %d, got %d", (int)(n), __rc);	\
} while (false)

static void
die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);

	exit(1);
}

unsigned prices[2001];

int
main(void)
{
	uintmax_t N, i;

	SCANF("%ju", 1, &N);

	for (i = 1; i <= N; i++) {
		unsigned C, I, j;

		SCANF("%u", 1, &C);
		SCANF("%u", 1, &I);

		for (j = 1; j <= I; j++) {
			unsigned P;

			SCANF("%u", 1, &P);
			prices[j] = P;
		}

		for (unsigned x = 1; x <= I; x++) {
			for (unsigned y = x + 1; y <= I; y++) {
				if (prices[x] + prices[y] == C) {
					printf("Case #%ju: %u %u\n", i, x, y);
					goto next_case;
				}
			}
		}

next_case:;
	}

	return 0;
}

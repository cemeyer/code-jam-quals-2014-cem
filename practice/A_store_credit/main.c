#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SCANF(fmt, n, args...)					\
do {								\
	int rc = scanf(fmt, args);				\
	if (rc != n)						\
		die("scanf: wanted %d, got %d", (int)(n), rc);	\
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

int
main(void)
{
	uintmax_t N;

	SCANF("%ju", 1, &N);

	return 0;
}

#include <math.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <bsd/sys/cdefs.h>
#include <bsd/sys/queue.h>
#include <bsd/sys/tree.h>

typedef uintmax_t um;

#define SCANF(fmt, n, args...)						\
do {									\
	int __rc = scanf(fmt, args);					\
	if (__rc != (n))						\
		die("scanf: wanted %d, got %d\n", (int)(n), __rc);	\
} while (false)

#define FWRITE(P, Sz, Nm, Fs)						\
do {									\
	size_t __r = fwrite((P), (Sz), (Nm), (Fs));			\
	if (__r != (Nm))						\
		die("fwrite: wanted %zu, got %zu\n", (size_t)(Nm), __r);\
} while (false)

#define ASSERT(x) ({ if (!(x)) {					\
	printf("failed assert " #x " on %s:%d\n", __func__, __LINE__);	\
	abort();							\
} })

#define min(x, y) ({					\
	typeof(x) _min1 = (x);				\
	typeof(y) _min2 = (y);				\
	(void) (&_min1 == &_min2);			\
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({					\
	typeof(x) _max1 = (x);				\
	typeof(y) _max2 = (y);				\
	(void) (&_max1 == &_max2);			\
	_max1 > _max2 ? _max1 : _max2; })

static void
die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);

	exit(1);
}

#if 0
// qsort
static int
qsort_compare(const void *a, const void *b)
{
}

// rb tree map
struct item {
	RB_ENTRY(item)	entry;
	// ...
};
RB_HEAD(item_map, item);

static struct item_map map = RB_INITIALIZER(&map);

static int
rb_compare(const struct item *a, const struct item *b)
{
}

RB_PROTOTYPE(item_map, item, entry, rb_compare);
RB_GENERATE(item_map, item, entry, rb_compare);

static void
rb_ex(void)
{
	struct item *ip, key, *exists;

	RB_FOREACH(ip, item_map, &map) {
	}

	exists = RB_INSERT(item_map, &map, ip);

	// key.key = y;
	ip = RB_FIND(item_map, &map, &key);
	// RB_NFIND ...
}

// case
void
docase(um cno)
{
}
#endif

int
main(void)
{
	um Tcases, zz, A, B, K, a, b, cnt;

	SCANF("%ju", 1, &Tcases);

	for (zz = 1; zz <= Tcases; zz++) {
		printf("Case #%ju: ", zz);

		SCANF("%ju %ju %ju", 3, &A, &B, &K);

		cnt = 0;
		for (a = 0; a < A; a++)
			for (b = 0; b < B; b++)
				if ((a&b) < K)
					cnt++;

		printf("%ju\n", cnt);

		// ...
	}

	return 0;
}

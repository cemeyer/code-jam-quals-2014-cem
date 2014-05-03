#include <ctype.h>
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

struct rep {
	char x;
	unsigned cnt;
};

um Tcases, zz, N, ni;
char line[120];
struct rep rep[101 /*N*/][120 /*LEN*/];

static um
minsolve(int idx)
{
#if 0
	for (um i = 1; i <= N; i++) {
	}
#endif

	//ASSERT(N == 2);
	return (unsigned)labs((long)rep[1][idx].cnt - (long)rep[2][idx].cnt);
}

int
main(void)
{

	SCANF("%ju", 1, &Tcases);

	for (zz = 1; zz <= Tcases; zz++) {
		printf("Case #%ju: ", zz);

		SCANF("%ju", 1, &N);

		bool samelen = true;
		int len = -1;

		memset(rep, 0, sizeof rep);
		for (ni = 1; ni <= N; ni++) {
			fgets(line, sizeof line, stdin);
			if (!isalpha(line[0]))
				fgets(line, sizeof line, stdin);
			//printf("XXX line: %s\n", line);

			unsigned i = 0;
			for (char *x = line; *x && isalpha(*x); x++) {
				if (i > 0 && rep[ni][i-1].x == *x) {
					rep[ni][i-1].cnt++;
					continue;
				}
				rep[ni][i].x = *x;
				rep[ni][i].cnt = 1;
				i++;
			}

			if (len == -1)
				len = i;
			else if (len != (int)i)
				samelen = false;
		}

		if (!samelen) {
			printf("Fegla Won\n");
			continue;
		}

		bool same = true;
		for (int i = 0; i < len; i++) {
			char x = rep[1][i].x;
			for (ni = 2; ni <= N; ni++) {
				if (rep[ni][i].x != x){ 
					same = false;
					break;
				}
			}
			if (!same)
				break;
		}

		if (!same) {
			printf("Fegla Won\n");
			continue;
		}

		um cnt = 0;
		for (int i = 0; i < len; i++)
			cnt += minsolve(i);

		printf("%zu\n", cnt);
	}

	return 0;
}

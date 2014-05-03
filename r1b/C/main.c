#include <math.h>
#include <inttypes.h>
#include <limits.h>
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

um Tcases, N, M;
bool flights[50][50];
char buf[5*50], buf2[5*50];
unsigned cities[50];
bool visited[50];

// find the shortest / best path
static unsigned
dfs(char *out, char *best, unsigned spl, int cur)
{
	char zip[6];

	unsigned bpl = UINT_MAX, tpl;

	// pick next city
	bool allvisited = true, anywheretogo = false;
	for (um xx = 0; xx < N; xx++) {
		if (cur == -1 || flights[cur][xx])
			anywheretogo = true;

		if (visited[xx]) {
			printf("Xxx: visited: %u\n", xx);
			continue;
		}

		allvisited = false;

		if (cur != -1 && !flights[cur][xx]) {
			printf("Xxx: no flight: %u->%u\n", cur, xx);
			continue;
		}

		sprintf(zip, "%u", cities[xx]);
		memcpy(out, zip, 5);

		visited[xx] = true;
		tpl = dfs(out + 5, best + 5, spl+1, xx);
		visited[xx] = false;

		if (tpl < bpl) {
			memcpy(best, out, 5 * tpl);
			bpl = tpl;
		} else if (tpl == bpl && tpl != UINT_MAX) {
			if (memcmp(out, best, 5 * tpl) < 0) {
				memcpy(best, out, 5 * tpl);
			}
		}
	}


	if (allvisited) {
		return 0;
	} else if (!anywheretogo) {
		return UINT_MAX;
	}

	return bpl;
}

int
main(void)
{
	um zz;

	SCANF("%ju", 1, &Tcases);

	for (zz = 1; zz <= Tcases; zz++) {
		printf("Case #%ju: ", zz);

		SCANF("%ju %ju", 2, &N, &M);
		for (um xx = 0; xx < N; xx++) {
			SCANF("%u", 1, &cities[xx]);
		}

		memset(flights, 0, sizeof flights);
		for (um xx = 0; xx < M; xx++) {
			unsigned a, b;
			SCANF("%u %u", 2, &a, &b);

			flights[a][b] = true;
			flights[b][a] = true;
		}

		memset(visited, 0, sizeof visited);
		memset(buf, 0, sizeof buf);
		memset(buf2, 0, sizeof buf2);

		unsigned pl = dfs(buf, buf2, 0, -1);

		if (pl == UINT_MAX)
			continue;

		printf("%.*s\n", pl * 5, buf2);

#if 0
		printf("XXX: pl %u\n", pl);
		for (unsigned i = 0; i < 5*pl; i++) {
			printf("%02x", buf2[i]);
		}
#endif


		// ...
	}

	return 0;
}

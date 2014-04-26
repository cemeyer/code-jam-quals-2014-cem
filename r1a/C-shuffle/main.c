#include <math.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

#define N 1000
static unsigned array[N];

static const char *
goodbad(void)
{
	const double exp = 500.;
	const unsigned firstseg = 350,
	      sseg = 448, ssegmax = 881,
	      tseg = 200, qseg = 100, fseg = 50,
	      sseg2 = 570, ssegmax2 = 770;

	unsigned i;
	double lsum = 0., hsum = 0., tsum = 0.,
	       qsum = 0., fsum = 0., hsum2 = 0.;

	unsigned metrics = 0;

	for (i = 0; i < firstseg; i++) {
		lsum += array[i];
	}

	lsum /= firstseg;

	for (i = 0; i < tseg; i++) {
		tsum += array[i];
	}
	tsum /= tseg;

	for (i = 0; i < qseg; i++) {
		qsum += array[i];
	}
	qsum /= qseg;

	for (i = 0; i < fseg; i++) {
		fsum += array[i];
	}
	fsum /= fseg;

	for (i = sseg; i < ssegmax; i++) {
		hsum += array[i];
	}

	hsum /= (ssegmax - sseg);

	for (i = sseg2; i < ssegmax2; i++) {
		hsum2 += array[i];
	}

	hsum2 /= (ssegmax2 - sseg2);

	if (fabs((lsum - 500.)/sqrt(1000.*1000/(12*firstseg))) >= 1.0)
		metrics++;
	if (fabs((hsum - 500.)/sqrt(1000.*1000/(12*(ssegmax-sseg )))) >= 1.645)
		metrics++;
	if (fabs((tsum - 500.)/sqrt(1000.*1000/(12*tseg))) >= 1.645)
		metrics++;
	if (fabs((qsum - 500.)/sqrt(1000.*1000/(12*qseg))) >= 1.645)
		metrics++;
	if (fabs((fsum - 500.)/sqrt(1000.*1000/(12*fseg))) >= 1.645)
		metrics++;

	if ((hsum - lsum) > 24.)
		metrics++;

	if ((hsum2 - tsum) > 41.)
		metrics++;

	if (metrics >= 2)
		return "BAD";

	printf("xxx: 1 %f\n", fabs((lsum - 500.)/sqrt(1000.*1000/(12*firstseg))));
	printf("xxx: 2 %f\n", fabs((hsum - 500.)/sqrt(1000.*1000/(12*(ssegmax-sseg )))));
	printf("xxx: 3 %f\n", fabs((tsum - 500.)/sqrt(1000.*1000/(12*tseg))));
	printf("xxx: 4 %f\n", fabs((qsum - 500.)/sqrt(1000.*1000/(12*qseg))));
	printf("xxx: 5 %f\n", fabs((fsum - 500.)/sqrt(1000.*1000/(12*fseg))));

	return "GOOD";
}

#if 0
static void
doarray(void)
{
	unsigned k, i, XX;

	for (i = 0; i < 1; i++) {
	for (XX = 0; XX < 2000; XX++) {

		for (k = 0; k < N; k++)
			array[k] = k;

		for (k = 0; k < N; k++) {
			unsigned p,t;

			if (i)
				p = random() % N;
			else
				p = (random() % (N - k)) + k;

			ASSERT(p < N);

			t = array[k];
			array[k] = array[p];
			array[p] = t;
		}

		//printf("%s: ", i? "BAD":"GOOD");
		for (k = 0; k < N; k++)
			printf("%u ", array[k]);
		printf("\n");
	}
	}
}
#endif

int
main(void)
{
	um Tcases, zz;

	SCANF("%ju", 1, &Tcases);

	for (zz = 1; zz <= Tcases; zz++) {
		um fn;

		printf("Case #%ju: ", zz);

		SCANF("%ju", 1, &fn);
		ASSERT(fn == 1000);

		for (um ii = 0; ii < N; ii++) {
			SCANF("%u", 1, &array[ii]);
		}

		printf("%s\n", goodbad());
	}


	return 0;
}

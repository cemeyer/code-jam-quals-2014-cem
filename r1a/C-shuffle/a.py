import sys
import os


def main():
    bucket = []
    for i in range(1000):
        bucket.append([])

    nl = 0
    for ln in sys.stdin.readlines():
        vs = ln.split(" ")

        for i in range(1000):
            v = int(vs[i])
            bucket[i].append(v)

        nl += 1


    for i in range(1000):
        bucket[i].sort()
        b = bucket[i]

        median = b[(len(b)+1)/2]
        avg = sum(b) / len(b)

        #sys.stdout.write("%d: M:%f A:%f" % (i, median, avg))
        sys.stdout.write("%f\n" %avg)

        #dist = {}
        #for x in b:
        #    dist[x] = dist.get(x, 0) + 1

        #fd = map(lambda x: (x[1], x[0]), dist.items())
        #fd.sort()

        #if fd[-1][0] > 10:
        #    sys.stdout.write("   highest: %d (x%d)" % (fd[-1][1], fd[-1][0]))
        #sys.stdout.write("\n")



if __name__ == "__main__":
    main()

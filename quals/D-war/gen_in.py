import random
import sys

sys.stdout.write("1\n")
sys.stdout.write("1000\n")

for j in range(2):
    for i in range(1000):
        r = random.random()
        while r == 0.0:
            r = random.random()
        sys.stdout.write("%.5f " % r)

    sys.stdout.write("\n")

import sys
import os


def main():

    lines = []

    for ln in sys.stdin.readlines():
        lines.append(ln.strip())

    print len(lines)
    for ln in lines:
        print "1000"
        print ln




if __name__ == "__main__":
    main()

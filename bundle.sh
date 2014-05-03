#!/bin/zsh

die() {
    echo "$@"
    exit 1
}

targetbin="$(basename "$(pwd)")"
rm -f "$targetbin"
        
cmd="gcc -std=gnu99 -D_GNU_SOURCE -Wall -Wextra -O3 -g -o ${targetbin} *.c -lm -lbsd"
echo "$cmd"
zsh -c "$cmd" || die "$cmd: error"
echo "============= Compile Passes ============="

for f in test*.in ; do
    texp="${f/.in/.out}"
    [ -f "$texp" ] || die "$f: Has no matching output ($exp)"

    tmpf="$(mktemp)"

    echo "\"./${targetbin}\" < \"$f\" > \"$tmpf\""
    "./${targetbin}" < "$f" > "$tmpf" || die "${targetbin}: error during test"

    diff -u "$tmpf" "$texp"
    cmp --quiet "$tmpf" "$texp" || echo "$f failed"
    rm -f "$tmpf"
done

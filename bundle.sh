#!/bin/zsh

die() {
    echo "$@"
    exit 1
}

targetbin="$(basename "$(pwd)")"
target="${targetbin}.c"
rm -f "$target" "$targetbin"

for f in *.c ; do
    sed -e "s|\\\\n|\\\\\\\\n|" "$f" | while read line ; do
        if echo "$line" | egrep -q "^#include\s\s*\"[^\"]*\"$" ; then
            incfn="$(echo "$line" | sed -e "s|^#include\s\s*\"\([^\"]*\)\"$|\1|")"
            echo "/* $line */" >> "$target"
            cat "$incfn" >> "$target"
        else
            /usr/bin/echo -E "$line" >> "$target"
        fi
    done
done
        
cmd="gcc -std=gnu99 -Wall -Wextra -O3 -g -o ${targetbin} ${target}"
echo "$cmd"
zsh -c "$cmd" || die "$cmd: error"

for f in test*.in ; do
    texp="${f/.in/.out}"
    [ -f "$texp" ] || die "$f: Has no matching output ($exp)"

    tmpf="$(mktemp)"

    "./${targetbin}" < "$f" > "$tmpf" || die "${targetbin}: error during test"

    diff -u "$tmpf" "$texp"
    cmp --quiet "$tmpf" "$texp" || echo "$f failed"
    rm -f "$tmpf"
done

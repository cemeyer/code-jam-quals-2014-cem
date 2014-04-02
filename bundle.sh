#!/bin/zsh

die() {
    echo "$@"
    exit 1
}

targetbin="$(basename "$(pwd)")"
target="${targetbin}.c"
rm -f "$target" "$targetbin"

for f in *.c ; do
    while read line ; do
        if echo "$line" | egrep -q "^#include\s\s*\"[^\"]*\"$" ; then
            incfn="$(echo "$line" | sed -e "s|^#include\s\s*\"\([^\"]*\)\"$|\1|")"
            echo "/* $line */" >> "$target"
            cat "$incfn" >> "$target"
        else
            echo "$line" >> "$target"
        fi
    done < "$f"
done
        
cmd="gcc -Wall -Wextra -O3 -g -o ${targetbin} ${target}"
echo "$cmd"
zsh -c "$cmd" || die "$cmd: error"

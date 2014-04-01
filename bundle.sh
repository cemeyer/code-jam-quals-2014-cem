#!/bin/zsh

target="$(basename "$(pwd)").c"
rm -f "$target"

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
        


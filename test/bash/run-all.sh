#!/bin/bash

for f in *.sh; do
    if [[ "$f" != "run-all.sh" ]]; then
        ./$f
    fi
done

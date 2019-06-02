#!/bin/bash
# See https://github.com/malyvsen/steganosaurus/issues/5

test () {
    name=$1
    pre=$2
    command=$3
    output=$4
    echo -n "$name "
    touch data carrier
    $pre
    if [[ $($command) =~ "$output" ]]; then
        echo "pass"
    else
        echo "fail"
    fi
    rm data carrier output 2> /dev/null
}

test "- error when could not open carrier file in write mode: " "rm carrier" "./steganosaurus -m write -c carrier -d data -o output" "error: carrier couldn't be opened"

test "- error when could not open data file in write mode: " "rm data" "./steganosaurus -m write -d data -c carrier -o output" "error: data couldn't be opened"

test "- error when could not open output file in write mode: " "" "./steganosaurus -m write -d data -c carrier -o error/output" "error: error/output couldn't be opened"

test "- error when could not open carrier file in read mode: " "rm carrier" "./steganosaurus -m read -c carrier -o output" "error: carrier couldn't be opened"

test "- error when could not open output file in read mode: " "" "./steganosaurus -m read -c carrier -o error/output" "error: error/output couldn't be opened"

test "- error when could not open carrier file in clear mode: " "rm carrier" "./steganosaurus -m clear -c carrier -o output" "error: carrier couldn't be opened"

test "- error when could not open output file in clear mode: " "" "./steganosaurus -m clear -c carrier -o error/output" "error: error/output couldn't be opened"
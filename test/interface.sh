#!/bin/bash

test () {
    name=$1
    command=$2
    output=$3
    echo -n "$name "
    touch data carrier
    if [[ $($command) = "$output" ]]; then
        echo "pass"
    else
        echo "fail"
    fi
    rm data carrier output 2> /dev/null
}

test "- user did not provide data path:" "./steganosaurus -m write -o output -c carrier" "error: data path not provided"

test "- user did not provide carrier path: " "./steganosaurus -m write -o output -d data" "error: carrier path not provided"

test "- user did not provide output path: " "./steganosaurus -m write -d data -c carrier" "error: output path not provided"

test "- user provided wrong mode: " "./steganosaurus -m hide -o output -c carrier -d data" "error: \"hide\" is not a valid mode"

test "- user provided correct arguments in write mode using implicit style: " "./steganosaurus write data carrier output" ""

test "- user provided correct arguments in write mode using explicit style: " "./steganosaurus -m write -o output -c carrier -d data" ""

test "- user provided correct arguments in read mode using implicit style: " "./steganosaurus read carrier output" ""

test "- user provided correct arguments in read mode using explicit style: " "./steganosaurus -m read -o output -c carrier" ""

test "- user provided correct arguments in clear mode using implict style: " "./steganosaurus clear carrier output" ""

test "- user provided correct arguments in clear mode using explicit style: " "./steganosaurus -m clear -o output -c carrier" ""

test "- user provided too many arguments: " "./steganosaurus -m clear -o output -c carrier -x" "error: unrecognized argument: -x"

test "- user provided data path in read mode: " "./steganosaurus -m read -o output -c carrier -d data" "error: data path provided with mode == read"

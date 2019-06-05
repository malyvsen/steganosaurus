#!/bin/bash
# See https://github.com/malyvsen/steganosaurus/issues/3


echo -n "- user decode file without message: "
output="no data encoded"
if [[ $(./steganosaurus read image.jpg output) =~ "$output" ]]; then
    echo "pass"
else
    echo "fail"
fi

rm output 2> /dev/null
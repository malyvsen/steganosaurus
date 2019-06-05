#!/bin/bash

# not a JPEG file
echo -n "- error on non-jpeg file: "

echo "secret" >> data
output="error: image.png is not JPG, or is corrupted"
if [[ $(./steganosaurus -m write -o output.jpg -c image.png -d data) =~ "$output" ]]; then
    echo "pass"
else
    echo "fail"
fi
rm data output.jpg 2> /dev/null
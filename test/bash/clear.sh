#!/bin/bash

echo -n "- clear text message from jpeg file: "
echo "secret" >> data
./steganosaurus -m write -o output.jpg -c image.jpg -d data
./steganosaurus -m clear -c output.jpg -o clear.jpg
cmp image.jpg clear.jpg
if [[ $? = 0 ]]; then
        echo "pass"
else
        echo "fail"
fi

rm data output.jpg clear.jpg 2> /dev/null

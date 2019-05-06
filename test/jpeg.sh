#!/bin/bash

# empty data file
touch data
./steganosaurus -m write -o output.jpg -c image.jpg -d data
cmp image.jpg output.jpg
 if [[ $? = 0 ]]; then
        echo "pass"
else
        echo "fail"
fi
rm data output.jpg 2> /dev/null
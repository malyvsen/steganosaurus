#!/bin/bash
# https://github.com/malyvsen/steganosaurus/issues/4

output="error: Carrier and output could not be the same file"


echo -n "- the same filename for carrier and output in write mode: "
echo "secret" >> data
cp image.jpg image2.jpg
if [[ $(./steganosaurus -m write -d data -c image2.jpg -o image2.jpg) =~ "$output" ]]; then
    echo "pass"
else
    echo "fail"
fi
rm data image2.jpg output 2> /dev/null


echo -n "- the same filename for carrier and output in read mode: "
echo "secret" >> data
./steganosaurus -m write -d data -c image.jpg -o image2.jpg
if [[ $(./steganosaurus -m read -c image2.jpg -o image2.jpg) =~ "$output" ]]; then
    echo "pass"
else
    echo "fail"
fi
rm data image2.jpg output 2> /dev/null


echo -n "- the same filename for carrier and output in clear mode: "
echo "secret" >> data
./steganosaurus -m write -d data -c image.jpg -o image2.jpg
if [[ $(./steganosaurus -m clear -c image2.jpg -o image2.jpg) =~ "$output" ]]; then
    echo "pass"
else
    echo "fail"
fi
rm data image2.jpg output 2> /dev/null
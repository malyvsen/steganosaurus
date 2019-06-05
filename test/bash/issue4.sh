#!/bin/bash
# https://github.com/malyvsen/steganosaurus/issues/4


echo -n "- the same filename for carrier and output in write mode: "
echo "secret" >> data
cp image.jpg image2.jpg
./steganosaurus -m write -d data -c image2.jpg -o image2.jpg
if [[ $? = 0 ]]; then
    echo "pass"
else
    echo "fail"
fi
rm data image2.jpg output 2> /dev/null


echo -n "- the same filename for carrier and output in read mode: "
echo "secret" >> data
./steganosaurus -m write -d data -c image.jpg -o image2.jpg
./steganosaurus -m read -c image2.jpg -o image2.jpg
if [[ $? = 0 ]]; then
    echo "pass"
else
    echo "fail"
fi
rm data image2.jpg output 2> /dev/null


echo -n "- the same filename for carrier and output in clear mode: "
echo "secret" >> data
./steganosaurus -m write -d data -c image.jpg -o image2.jpg
./steganosaurus -m clear -c image2.jpg -o image2.jpg
if [[ $? = 0 ]]; then
    echo "pass"
else
    echo "fail"
fi
rm data image2.jpg output 2> /dev/null
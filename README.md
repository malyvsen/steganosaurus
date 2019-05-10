<div align="center">
   <img src="logo.png">
</div>
Simple command-line utility for JPG steganography.

# Stega... what?
Steganography is the practice of hiding communication in a way which makes it difficult to find out that the communication happened at all.
Steganosaurus can hide any kind of data file inside a JPG image so that the image still looks the same to the unsuspecting eye. Only someone who also has steganosaurus (or a similar utility) will be able to read the data hidden in the image.

# Installation
Download the latest relevant version from [releases](https://github.com/malyvsen/steganosaurus/releases).

# Usage
To write some data onto a carrier and save the modified carrier:
```
steganosaurus write <data> <carrier> <output>
```

To read data from a carrier and save what was read:
```
steganosaurus read <carrier> <output>
```

To remove written data from a carrier:
```
steganosaurus clear <carrier> <output>
```

# Legal
Steganosaurus uses [Catch 2](https://github.com/catchorg/Catch2) for testing, which is licensed under the [Boost Software License](https://www.boost.org/users/license.html).

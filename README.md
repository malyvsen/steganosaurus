<div align="center">
   <img src="logo.png">
</div>
Simple command-line utility for JPG steganography.

# Stega... what?
[Steganography](https://en.wikipedia.org/wiki/Steganography) is the practice of hiding communication in a way which makes it difficult to find out that the communication happened at all.
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

# So how secret is it exactly?
Not very. In fact, you can open a carrier image in any text editor and find the data stored in plan text at the end of the image file. The trick is simply that this doesn't show up in an image viewer, so your carrier image doesn't raise any suspicion of anything being hidden in it at all.

# API
Steganosaurus provides a minimalist API in the form of encoders. Currently, only the [SimpleEncoder](steganosaurus/encoders/simpleencoder.hpp) is available, which reads/writes plaintext data at the end of JPG files. You are, however, most welcome to add more encoders implementing the [IEncoder](steganosaurus/encoders/iencoder.hpp) interface!

# Legal
Steganosaurus uses [Catch 2](https://github.com/catchorg/Catch2) for testing, which is licensed under the [Boost Software License](https://www.boost.org/users/license.html).

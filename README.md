<div align="center">
   <img src="logo.png">
</div>
Simple command-line utility for JPG steganography.

# Installation
Download the latest relevant version from [releases](https://github.com/malyvsen/steganosaurus/releases).

# Usage
To write some data onto a carrier and save the modified carrier:
```bash
steganosaurus write <data> <carrier> <output>
```

To read data from a carrier and save what was read:
```bash
steganosaurus read <carrier> <output>
```

# Legal
Steganosaurus uses [Catch 2](https://github.com/catchorg/Catch2) for testing, which is licensed under the [Boost Software License](https://www.boost.org/users/license.html).

# yacss-parser

> A naive C++ CSS reentrant parser implementation using Bison and Flex

**ATTENTION**: this is NOT a full spec conformant parser. It DOES NOT aim to comply with all of the requirements associated with the roles it partakes in the CSS specification.

[![Build Status](https://travis-ci.org/cirocosta/yacss-parser.svg?branch=master)](https://travis-ci.org/cirocosta/yacss-parser)

## Install

Make sure that you have all the dependencies installed:

- flex
- bison\*
- make
- cmake
- a modern c++ compiler - targetting c++11 (i recommend clang, 3.5 is good)

Then, simply:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make && make test
```

\*: If you've built `bison` from source and in the `make` step it claims that there's a problem with `m4`, try setting the `pkgdata_dir`:
```
export BISON_PKGDATADIR=/usr/local/share/bison/data
```


## LICENSE

GPLv2



# CostInstrument-llvm

## Build and install

```
> git clone <this repo>
> mkdir build && cd build
> cmake ../CostInstrument-llvm/ -DCMAKE_BUILD_TYPE=<Debug or Release> -DCMAKE_INSTALL_PREFIX=<where to install> [-DLLVM_DIR=<where LLVM is installed>]
> make && make install
```

## Dependencies

[LLVM](http://llvm.org) and [clang](https://clang.llvm.org) both need to be version 5.x

## Usage

```
> clang-instr <source files> -o <output executable file>
```

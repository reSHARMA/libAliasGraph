<h1 align="center">
  <br>
  <a href="#"><img src="https://i.ibb.co/K71cjcd/af89c61d-2400-45b1-b985-660f6d7a8452-200x200.png" alt="libAliasGraph" width="200"></a>
  <br>
  libAliasGraph
  <br>
</h1>

<h4 align="center">A minimalistic utility to create and manipulate points-to graph</h4>


## Table of Contents

- [Getting Started](#getting-started)
  - [Building from source](#build-from-source)
  - [Using with opt](#using-with-opt)

## Getting Started

### Building from source
```sh
$ git clone this_repository.git
$ cd this_repository
$ mkdir build; cd build
$ cmake .. && make
$ make install
```
### Using with opt
* Path to the headers should be searchable by the compiler
* In your LLVM IR pass:
  * Include the header file, ```AliasGraph/AliasGraph.h```
  * Use namespace ```AliasGraphUtil```

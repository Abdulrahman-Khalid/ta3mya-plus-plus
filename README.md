# ta3mya-plus-plus
ta3mya plus plus is an implementation of a programming language using the Lex and Yacc compiler generating package.

# Language
See [methal.ta3](./docs/methal.ta3) for all language features.

# Requirements
- g++
- gnu-make
- bison
- flex

```sh
$ sudo apt update && sudo apt install -y g++ make bison flex
```

# Build Compiler
```sh
$ cd src && make 
```

# Compile
```sh
$ ./ta3myac path/to/file.ta3
```

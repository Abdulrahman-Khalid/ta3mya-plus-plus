# ta3mya-plus-plus
ta3mya plus plus is an implementation of a programming language using the Lex and Yacc compiler generating package.

It's the first egyptian arabic programming language.

# Language
See [methal.ta3](./docs/methal.ta3) for all language features.

# Requirements
- g++
- gnu-make
- bison
- flex
- python 3.8.5 (for gui)

```sh
$ sudo apt update && sudo apt install -y g++ make bison flex python3
```

# Build Compiler
```sh
$ cd src && make 
```


# Compile
## Terminal way
```sh
$ ./ta3myac path/to/file.ta3
```
## Graphical way
```sh
$ cd compiler
```
```sh
$ python run.py
```

### File Menu
![](./compiler/screenshots/FileMenu.png) 

### Help Menu
![](./compiler/screenshots/HelpMenu.png) 

### Compile Menu
![](./compiler/screenshots/CompileMenu.png) 

### Success
![](./compiler/screenshots/Success.png) 

### Failure
![](./compiler/screenshots/Failure.png) 
### Symbol Table
<!-- TODO -->
<!-- ![](./compiler/screenshots/SymbolTable.png)  -->

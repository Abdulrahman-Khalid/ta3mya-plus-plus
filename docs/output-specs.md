# Ta3mya Final Output Specs
This files documents the specs of the final output of the compiler.

Every quadruple should be on its own line.
Spacing doesn't matter.
Empty lines don't matter.

## Comments
Use `;` for comments that should be ignored by assembler, like:
```
; the following puts 5 in memory address v
CPY 5 V
; end
```

## Variables and Constants
All variables are 64bits wide.
To declare a variable, use `%var`:
```
%var x 5
```

To declare a constant, use `%const`:
```
%const y 6
```

You can't store any values at constants, but you can read them.

## Registers
### `$0` to `$7`
The machine has 8 64bit registers.

## Labels
Labels are places you can jump to.
To declare `infLoop` as label:
```
infLoop:
    ADD 1 x x ; x++
    JMP infLoop
```

## Quadruples
All `x` and `y` can be either a reference to variable, constant or literal integer.
For example, this is valid: `MUL 1 0 V` but this is not `CPY x 0` as you can't put value of x at variable named 0.

`b` denotes a label, see [Labels](#labels).
You can jump to previosly declared label, or a label that is declared later in the same file.

| Quadruple  | Description                  |
|------------|------------------------------|
| CPY x z    | z = copy(x)                  |
| INT x z    | z = int(x)                   |
| ADD x y z  | z = x + y                    |
| MUL x y z  | z = x * y                    |
| DIV x y z  | z = x / y                    |
| MOD x y z  | z = x % y                    |
| NEG x z    | z = -x                       |
| POW x y z  | z = pow(x, y)                |
| REAL x z   | z = real(x)                  |
| RADD x y z | z = x + y     (real numbers) |
| RMUL x y z | z = x * y     (real numbers) |
| RDIV x y z | z = x / y     (real numbers) |
| RMOD x y z | z = x % y     (real numbers) |
| RNEG x z   | z = -x        (real numbers) |
| RPOW x y z | z = pow(x, y) (real numbers) |
| RTN        | return                       |
| JMP b      | goto b                       |
| JMPZ x b   | if x == 0 { goto b }         |
| GT  x y z  | z = x >  y? 1:0              |
| LT  x y z  | z = x >  y? 1:0              |
| GTE x y z  | z = x >= y? 1:0              |
| LTE x y z  | z = x >= y? 1:0              |
| AND x y z  | z = x & y                    |
| OR x y z   | z = x \| y                   |

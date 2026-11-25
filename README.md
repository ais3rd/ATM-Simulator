# ATM Simulator

A console ATM simulator written in C, made as a debugging exercise. The interface is in Bahasa Indonesia.

## Features
- PIN login, with the account blocked after 3 wrong attempts
- Main menu:
  1. **Cek Saldo**: check balance
  2. **Tarik Tunai**: withdraw cash
  3. **Setor Tunai**: deposit cash
  4. **Transfer**: transfer funds
  5. **Keluar**: exit
- The balance is passed between functions with pointers (starting balance Rp1.000.000)

## Demo PIN
```
1234
```

## Build and run
The project file is for Code::Blocks (`DebuggingATM.cbp`). You can also build it with GCC:

```bash
gcc main.c -o atm.exe
atm.exe
```

> This is a debugging exercise. `main.c` includes a non-existent header `<grphik.h>`, and `char pin[4]` is too small for a 4-digit PIN plus `\0`. Fixing these is part of the exercise.

## License
Released under the [MIT License](LICENSE).

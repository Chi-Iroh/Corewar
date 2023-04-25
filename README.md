# Corewar
## An Epitech Project, Year 1
### Apr-May 2023
##### Charles Madjeri
##### Lee Bingler
##### Nils Perriolat
##### Thomas Sayen

<br>

## The Project

Corewar is a project that aims to reproduce a processor's behaviour.
Check the [subject](Subject%20Corewar.pdf) for more information.

<br>

## Makefile

This [Makefile](Makefile) supports multiple compilation modes.
- **Debug** : Compiled with debug information to use with gdb or valgrind for instance.
- **Sanitize** : Compiled with GCC address and undefined sanitizers.
- **Analyzer** : Same as **Debug**, but with GCC analyzer.
- **Release** : Compiled without any debug information.
- **Tests** : Compiled Criterion unit test files, runs and writes the coverage into log files.

Please note that **Release** mode doesn't add optimizations, as many syscalls are forbidden and GCC may call them even if they're not in our code.

<br>

## Miscelleanous Tools

- **[valgrind.sh](valgrind.sh)** : Compiles a binary with debug information and runs algrind.
- **[sanitize.sh](sanitize.sh)** : Compiles a binary with GCC sanitizers (address and undefined) and runs it.

Each of these tools have a help menu (run with --help).
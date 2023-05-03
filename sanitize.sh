#!/bin/bash

if [[ "$1" == "" || "$1" == "-h" || "$1" == "--help" ]]; then
    echo "Welcome in sanitize.sh help !"
    echo -e "\tThis script aims to ease sanitizer usage."
    echo -ne "\tIt configures it to make the binary continue after "
    echo "any non-critical error (all except segfaults for instance)."
    echo -e "\n\"$0 <binary> <arguments>\""
    echo -e "\t<binary> : binary name (either 'asm' or 'corewar' here)"
    echo -e "\t<arguments> : arguments that are given to the binary."
    echo -e "\n\"$0 asm a b c\" ==> \"<corewar repository>/asm/asm a b c\""
    exit 0
fi

if [[ "$1" != "asm" && "$1" != "corewar" ]]; then
    echo -e "'$0' needs either 'asm' or 'corewar' as first argument !\n" >&2
    echo "Please check your command line or read the help :" >&2
    echo -e "\t\"$0 --help\" or \"$0 -h\"" >&2
    exit 1
fi

export ASAN_OPTIONS=halt_on_error=0
make -C lib/ resanitize
make -C $1 resanitize
$1/$1 ${@:2}

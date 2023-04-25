#!/bin/bash

if [[ "$1" == "" || "$1" == "-h" || "$1" == "--help" ]]; then
    echo "Welcome in valgrind.sh help !"
    echo -e "\tThis script aims to ease valgrind usage."
    echo -ne "\tIt runs valgrind with the most important flags."
    echo -e "\n\"$0 <binary> <arguments>\""
    echo -e "\t<binary> : binary name (either 'asm' or 'corewar' here)"
    echo -e "\t<arguments> : arguments that are given to the binary."
    echo -e "\n\"$0 asm a b c\" ==> \"<corewar repository>/asm/asm a b c\""
    echo -e "\nSee also \"$0 --cmd\" to have more details about valgrind command line."
    exit 0
fi

if [[ "$1" == "--cmd" ]]; then
    echo "Full valgrind command :"
    echo -e "valgrind --leak-check=full --track-origins=yes -s --malloc-fill=0x42 --free-fill=0x84 --log-file=valgrind.log\n"
    echo -e "\t--leak-check=full : complete check of memory leaks for an optimal efficiency"
    echo -e "\t--track-origins=yes : tells valgrind to display where was allocated each leaked memory"
    echo -e "\t-s : display all errors"
    echo -e "\t--malloc-fill=0x42 : fills any malloc'd memory with the byte 0x42"
    echo -e "\t\t- prevents compiler behaviour (often initializes memory with 0) to make secure code"
    echo -e "\t\t- helps detecting mistakes by lokking for this byte in valgrind's log"
    echo -e "\t--free-fill=0x48 : same as above, except that it's freed memory which is filled with 0x84"
    echo -e "\t--log-file=valgrind.log : saves all the log into valgrind.log file"
    exit 0
fi

if [[ "$1" != "asm" && "$1" != "corewar" ]]; then
    echo -e "'$0' needs either 'asm' or 'corewar' as first argument !\n" >&2
    echo "Please check your command line or read the help :" >&2
    echo -e "\t\"$0 --help\" or \"$0 -h\"" >&2
    exit 1
fi

make -C $1 redebug
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --malloc-fill=0x42 --free-fill=0x84 --log-file=valgrind.log $1/$1 ${@:2}
echo "Open ./valgrind.log to see valgrind's output !"
#!/bin/bash

if [ -d "ASM_expected" ]; then
    rm -rf ./ASM_expected
fi
if [ -d "ASM_student" ]; then
    rm -rf ASM_student
fi
mkdir ASM_expected
mkdir ASM_student

make -C .. redebug
for file in $(find .. -type f -name "*.s" -or -name "*.S"); do
    basefile=$(basename $file)
    basetek=$basefile
    if [[ "${basefile:0:1}" == "_" ]]; then
        echo Skipping test - File name beginning with underscore
        continue
    fi
    echo -n "$basefile : "
    if [[ "$basetek" == *.s ]]; then
        basetek="${basetek:0:-2}"
    fi
    cd ASM_expected
    ../../corewar_binaries/asm/asm ../$file
    cd ../ASM_student
    ../../asm/asm ../$file
    cd ..
    diff "./ASM_expected/$basetek.cor" "./ASM_student/$basefile.cor"
    if (( $? == 0 )); then
        echo OK
    fi
done
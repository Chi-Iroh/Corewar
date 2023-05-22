.name "Bad zjmp"
.comment "Tries to jump somewhere that's not an instruction (illegal opcode)"

and r2, r3, r4 # All registers are zero-initialized, except the r1 (prog number)
# and sets the carry to 1 if result is 0, here r2 & r3 = 0 & 0 = 0 --> carry = 1
zjmp %3
live %0
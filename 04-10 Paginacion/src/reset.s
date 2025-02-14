.code 32
.extern _start

.global _reset_vector

.section .reset_vector
_reset_vector:
    B _start
.end

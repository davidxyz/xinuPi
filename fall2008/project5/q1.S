#include <arm.h>

.data
VAL:    .ascii "%d\r\n"                       #%d: int; %c: char; %f: float; %s: ascii; %x: hex
FMT2:   .ascii "%c\r\n"
ADDF:   .ascii "%d + %d = %d\r\n"
MULF:   .ascii "%d * %d = %d\r\n"
SUBF:   .ascii "%d - %d = %d\r\n"
DIVF:   .ascii "%d / %d = %d\r\n"
MODF:   .ascii "%d %% %d = %d\r\n"
ERRORMES:       .ascii "Error: Unknown operator %c\r\n"
ERROR2: .ascii "%d %c %d = 0\r\n"

.globl main
main:
	push {ip, lr}
loop:
	bl getchar
//convert to arm code 
#define TOTAL s7
#define MINUS s6
#define CHAR  t9
#define sp r13
//t0=R4
getInt:
        sub       sp, sp, #32
        str      ra, [sp], #28
        str      TOTAL, [sp], #24
        str      MINUS, [sp], #20

        mov      TOTAL, #0     /* s1 is total.  Initialize to 0.      */
        mov      MINUS, #1        /* s2 is minus flag.  Init to 1.       */

        bl       getchar         /* Get first character.                */
        mov      r4, '-'         /* Check for literal ASCII minus sign. */
        bne      r4, v0, gt2     /* IF there is NOT a minus, jump into  */
        mov      MINUS, #-1       /*  main loop, otherwise set flag.     */
gtlp:
        jal     getchar
gt2:    move    CHAR, v0        /* Save last character read.           */

        li      t3, EOF
        li      t2, '\n'
        li      t0, '0'
        li      t1, '9'

        beq     CHAR, t3, gtdn2 /* IF EOF, jump to gtdone2.             */
        beq     CHAR, t2, gtdn  /* IF newline, jump to gtdone.          */
        blt     CHAR, t0, gtlp  /* IF less than '0', try again.       */
        bgt     CHAR, t1, gtlp  /* IF greater than '9', try again.    */

        li      t0, '0'         /* Subtract value of ASCII '0' to     */
        sub     CHAR, CHAR, t0  /*  get actual numeral value.         */

        li      t0, 10          /* Horner's Algorithm.  Multiply      */
                                /*  total by base, add in next digit. */
        mul     TOTAL, TOTAL, t0
        add     TOTAL, TOTAL, CHAR

        b       gtlp

gtdn2:  addi    v1, zero, 1
        lw      ra, 28(sp)
        lw      TOTAL, 24(sp)
        lw      MINUS, 20(sp)
        addiu   sp, sp, 32
        jr      ra

gtdn:                               /* Multiply by minus flag. */
        mul     v0, TOTAL, MINUS
        move    v1, zero
        lw      MINUS, 20(sp)
        lw      TOTAL, 24(sp)
        lw      ra, 28(sp)
        addiu   sp, sp, 32
        jr      ra

done:
        lw ra, 28(sp)
        addiu sp, sp, 32
        li v0, 0
        jr ra

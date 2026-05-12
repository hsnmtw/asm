format ELF64 executable 3

segment readable executable

; the goal is to calculate the 32nd Fibonacci number

entry main

main:
    ; initialize the 
    mov rax, 0    ; n[0] = 0
    mov rbx, 1    ; n[1] = 1
    mov r11, 1
.loop:    
    mov r10, rax
    add r10, rbx
    mov rax, rbx
    mov rbx, r10
    inc r11
    cmp r11, 32
    je  .done
    jmp .loop
.done:
; 0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,
; 6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,
; 832040,1346269,2178309
; the number on register r10 is the one needed, but it 
; needs to be converted to ascii first to be printed

    mov rax, r10     ; Load dividend (rax)
    mov rdi, msg+24
.while:
    mov rbx, 10      ; Load divisor (10)
    xor rdx, rdx     ; Clear EDX before division
    div rbx          ; EAX = EAX / EBX, EDX = EAX % EBX    
    add rdx,48
    mov [rdi],dl
    dec rdi
    mov  qword [len], 1
    cmp rax,0
    jz .wend
    jmp .while
.wend:

mov rax, 1   ; SYS   = write
mov rdi, 1   ; FD    = stdout
mov rsi, dsp ; buf   = msg
mov rdx, dln ; count = len
syscall


; in c/c++ ==> write(int fd,const void* buf, size_t count)
; prints Hello World to standard output
mov rax, 1   ; SYS   = write
mov rdi, 1   ; FD    = stdout
mov rsi, msg ; buf   = msg
mov rdx, len ; count = len
syscall

mov rax, 1   ; SYS   = write
mov rdi, 1   ; FD    = stdout
mov rsi, nl  ; buf   = msg
mov rdx, 1   ; count = len
syscall

; in c/c++ ==> exit(int code)
mov rax, 60  ; SYS   = exit
mov rdi, 0   ; code  = 0
syscall

ret

segment readable writeable
dsp db "Fibonacci(32) = "
dln = $-dsp
nl db 10
msg rb 32
len dq 0

; #include <stdio.h>
; 
; void main() {
;     int n0 = 0;
;     int n1 = 1;
;     int n = 32;
;     int r;
;     for(int i=2;i<=n;++i) {
;         r = n0+n1;
;         n0 = n1;
;         n1 = r;
;     }
;     printf("Fibonacci(32) = %d\n", r);
;     exit(0);
; }
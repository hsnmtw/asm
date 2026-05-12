format ELF64 executable 3

segment readable executable

entry main

main:

; in c/c++ ==> write(int fd,const void* buf, size_t count)
; prints Hello World to standard output
mov rax, 1   ; SYS   = write
mov rdi, 1   ; FD    = stdout
mov rsi, msg ; buf   = msg
mov rdx, len ; count = len
syscall

; in c/c++ ==> exit(int code)
mov rax, 60  ; SYS   = exit
mov rdi, 0   ; code  = 0
syscall


segment readable
    msg db "Hello, World !",10
    len = $-msg

; ==================================================
; #include <stdio.h>
; #include <stdlib.h>
; 
; int main() {
;    printf("Hello, World !\n");
;    exit(0);
; }
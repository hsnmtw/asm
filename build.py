#!/bin/python3

import subprocess

def call(inst,hidden=False):
    if hidden:
        subprocess.call(inst,stderr=subprocess.STDOUT,stdout=subprocess.DEVNULL)
    else:
        subprocess.call(inst)


programs = [
    "Hello-World",
    "Fibonacci"
]

# subprocess.call("gcc -O3 -pedantic -Wall -Wextra -o ./output/fib-c ./c/Fibonacci.c")
for program in programs:
    call(["fasm","./contents/%s.asm" % program,"./output/%s" % program ],True)


print ("===============================")
for program in programs:
    print (">> running program : [%s]" % program)
    call (["chmod","+x","./output/%s" % program],True)
    call (["./output/%s" % program])

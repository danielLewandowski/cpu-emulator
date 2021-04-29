//
// Created by daniel on 12-04-21.
//

#ifndef UNTITLED_VM_OPERATIONS_H
#define UNTITLED_VM_OPERATIONS_H

#include "vm_registers.h"

typedef enum {
    PUSH,
    POP,
    GOTO,
    CMP,
    MOV,
    PRINT,
    ADD,
    SUB,
    MUL,
    DIV,
    STOP
} instruction_t;

typedef enum {
    JLE,
    JL,
    JE,
    JNE,
    JGE,
    JG,
} conditional_t;

#endif //UNTITLED_VM_OPERATIONS_H

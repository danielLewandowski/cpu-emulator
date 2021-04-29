//
// Created by daniel on 12-04-21.
//

#ifndef UNTITLED_VM_REGISTERS_H
#define UNTITLED_VM_REGISTERS_H

typedef enum {
    A, B, C, D, E, F, COUNT
} register_t;

struct Registers_t {
    int RIP;
    int RSP;
    int R[COUNT];
};

#endif //UNTITLED_VM_REGISTERS_H

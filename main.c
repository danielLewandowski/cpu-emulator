#include <stdio.h>
#include <stdbool.h>

#include "headers/vm_operations.h"
#include "headers/vm_registers.h"

bool running = true; //start/stop the program

//int program[] = {
//        //addition
//        MOV, A, 25,
//        ADD, A, 31,
//        //subtraction
//        MOV, B, 120,
//        SUB, B, 165,
//        //multiplication
//        MOV, C, 54,
//        MUL, C, 15,
//        //division
//        MOV, D, 60,
//        DIV, D, 2,
//        PRINT,
//        STOP
//};

//int program[] = {
//        MOV, A, 0,
//        MOV, B, 10,
//        ADD, A, 1,
//        PRINT,
//        CMP, A, 10,
//        JL, 6,
//        STOP
//};

int program[] = {
        PUSH, 5,
        PUSH, 10,
        POP, A,
        POP, B,
        PRINT,
        STOP
};

int stack[1024];
struct Registers_t regs;

bool compare(conditional_t c, int dest, int src) {
    switch (c) {
        case JLE:
            if (dest <= src)
                return true;
            else
                return false;
        case JL:
            if (dest < src)
                return true;
            else
                return false;
        case JE:
            if (dest == src)
                return true;
            else
                return false;
        case JNE:
            if (dest != src)
                return true;
            else
                return false;
        case JGE:
            if (dest >= src)
                return true;
            else
                return false;
        case JG:
            if (dest > src)
                return true;
            else
                return false;
    }
}

void eval(instruction_t inst) {
    switch (inst) {
        case PUSH: {
            //push, a
            int value = program[++regs.RIP];
            stack[regs.RSP] = value; //add a value of the instruction's argument
            regs.RSP++; //move stack pointer up

            printf("PUSH: %d\n", value);
            break;
        }
        case POP: {
            //pop, dest
            register_t reg = program[++regs.RIP]; //move inst pointer to read the register
            int value = stack[--regs.RSP]; //get top of the stack

            regs.R[reg] = value; //assign value

            printf("POP: %d to register %d\n", value, reg);
            break;
        }
        case MOV: {
            //mov, dest, src
            register_t reg = program[++regs.RIP]; //move inst pointer to read the register
            int value = program[++regs.RIP]; //move inst pointer to read the value

            regs.R[reg] = value; //assign value

            printf("MOV: %d to register %d\n", value, reg);
            break;
        }
        case PRINT: {
            printf("----------------------------\n");
            printf("A(0): %d\nB(1): %d\nC(2): %d\nD(3): %d\nE(4): %d\nF(5): %d\n",
                   regs.R[A], regs.R[B], regs.R[C], regs.R[D], regs.R[E], regs.R[F]);
            printf("----------------------------\n");
            break;
        }
        case ADD: {
            //ADD, dest, src
            register_t reg = program[++regs.RIP];

            int b = program[++regs.RIP];
            int a = regs.R[reg];
            int val = a + b;

            regs.R[reg] = val;

            printf("ADD: %d + %d = %d\nTo register: %d\n", a, b, val, reg);
            break;
        }
        case SUB: {
            //SUBSTRACT a, b, reg
            register_t reg = program[++regs.RIP];

            int b = program[++regs.RIP];
            int a = regs.R[reg];
            int val = a - b;

            regs.R[reg] = val;

            printf("SUB: %d - %d = %d\nTo register: %d\n", a, b, val, reg);
            break;
        }
        case MUL: {
            //MUL, dest, src
            register_t reg = program[++regs.RIP];

            int a = program[++regs.RIP];
            int b = regs.R[reg];
            int val = a * b;

            regs.R[reg] = val;

            printf("MUL: %d * %d = %d\nTo register: %d\n", a, b, val, reg);
            break;
        }
        case DIV: {
            //DIV, dest, src
            register_t reg = program[++regs.RIP];

            int b = program[++regs.RIP];
            int a = regs.R[reg];
            int val = a / b;

            regs.R[reg] = val;

            printf("DIV: %d / %d = %d\nTo register: %d\n", a, b, val, reg);
            break;
        }
        case CMP: {
            //CMP, dest, src
            register_t reg = program[++regs.RIP];
            int src = program[++regs.RIP];

            conditional_t condition = program[++regs.RIP];
            int line = program[++regs.RIP];

            if (compare(condition, regs.R[reg], src) == true)
                regs.RIP = --line;

            break;
        }
        case GOTO: {
            //GOTO, dest
            regs.RIP = program[++regs.RIP];

            break;
        }
        default: {
            running = false;
            break;
        };
    }
}

int main() {
    while (running) {
        eval(program[regs.RIP]); //evaluate instruction
        regs.RIP++; //increment the pointer
    }

    return 0;
}
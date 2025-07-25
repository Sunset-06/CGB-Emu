#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define MEMORY_SIZE 0x10000

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

// The registers a,f,b,c,d,s,h,l

typedef struct {
    union {
        struct {
            uint8_t f, a;
        };
        uint16_t af;
    };
    union {
        struct { 
            uint8_t c, b; 
        };
        uint16_t bc;
    };
    union {
        struct { 
            uint8_t e, d; 
        };
        uint16_t de;
    };
    union {
        struct { 
            uint8_t l, h; 
        };
        uint16_t hl;
    };

    bool ime;
    bool halted;
    bool stopped;
} Registers;

typedef struct {
    Registers regs;

    //stack pointer and program counter
    uint16_t sp;
    uint16_t pc;

    uint8_t memory[MEMORY_SIZE];

    bool ime;
    uint8_t ie;  // Interrupt Enable
    uint8_t iflag; // Interrupt Flag (IF)

    bool halted;
    bool stopped;

    uint16_t div;
    uint8_t tima, tma, tac;

    uint64_t cycles;
} CPU;

// flag functions
extern void set_Z(uint8_t result, Registers *cpu);

extern void set_N(bool sub, Registers *cpu);

extern void set_H(bool condition, Registers *cpu);
extern void set_H_add(uint8_t a, uint8_t b, Registers *cpu);
extern void set_H_sub(uint8_t a, uint8_t b, Registers *cpu);
extern void set_H_add16(uint16_t a, uint16_t b, Registers *cpu);
extern void set_H_inc(uint8_t before, Registers *cpu);
extern void set_H_dec(uint8_t before, Registers *cpu);

extern void set_C(bool condition, Registers *cpu);
extern void set_C_add(uint8_t a, uint8_t b, Registers *cpu);
extern void set_C_sub(uint8_t a, uint8_t b, Registers *cpu);
extern void set_C_add16(uint16_t a, uint16_t b, Registers *cpu);
extern void set_C_sbc(uint8_t a, uint8_t b, bool carry, Registers *cpu);

extern void clear_flags(Registers *cpu);

// memory functions
extern uint8_t read8(CPU *cpu, uint16_t addr);
extern void write8(CPU *cpu, uint16_t addr, uint8_t value);
extern uint16_t read16(CPU *cpu, uint16_t addr);
extern void write16(CPU *cpu, uint16_t addr, uint16_t value);

#endif 
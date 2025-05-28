#include "core/interrupts.h"

void _main(u32 magic) {
    idt_init();
    isr_init();
    fpu_init(); // floating point unit.
    irq_init();
    
    for (;;) {}
}

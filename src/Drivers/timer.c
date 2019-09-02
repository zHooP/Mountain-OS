#include "../all_drivers.h"


int timer_ticks = 0;


void timer_handler(struct regs *r)
{
    timer_ticks++;
}


void timer_wait(int ticks)
{
    unsigned long eticks;
    eticks = timer_ticks + ticks;
    while(timer_ticks <= eticks){
        itoa(20, 10); // dummy function call. needed for some reason
    }
}

void timer_install()
{
    irq_install_handler(0, timer_handler);
}

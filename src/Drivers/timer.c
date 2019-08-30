#include "timer.h"
#include "irq.h"

timer_ticks = 0;

void timer_handler()
{
    timer_ticks++;
}

void timer_wait(int ticks)
{
    long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}


void timer_install()
{
    irq_install_handler(0, timer_handler);
}

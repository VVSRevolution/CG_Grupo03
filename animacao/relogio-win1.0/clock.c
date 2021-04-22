#include "clock.h"

void increase_hours(Clock * clock)
{
    clock->h = (clock->h + 1) % 12;
}

void increase_minutes(Clock * clock)
{
    clock->m = (clock->m + 1) % 60;

    if (clock->m == 0)
        increase_hours(clock);
}

void increase_seconds(Clock * clock)
{
    clock->s = (clock->s + 1) % 60;

    if (clock->s == 0)
        increase_minutes(clock);
}
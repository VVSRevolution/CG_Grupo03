#ifndef _CLOCK_H
#define _CLOCK_H

// Struct que representa as horas de um relógio de parede
struct _clock
{
    // 0 <= h < 12
    // 0 <= m < 60
    // 0 <= s < 60
    unsigned int h, m, s;
};

typedef struct _clock Clock;

void increase_hours(Clock * clock);
void increase_minutes(Clock * clock);
void increase_seconds(Clock * clock);

#endif // _CLOCK_H
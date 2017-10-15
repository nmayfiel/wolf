#include "wolf.h"
#include <mach/mach_time.h>

double			seconds_per_frame(uint64_t last,
					  uint64_t current)
{
     static mach_timebase_info_data_t tb;
     uint64_t elapsed;
     uint64_t nanosecs;

     elapsed = current - last;
     if (tb.denom == 0)
	  mach_timebase_info(&tb);
     nanosecs = elapsed * tb.numer / tb.denom;
     return ((double)nanosecs * 1.0E-9);
}

void			update_clock(t_clock *clock)
{
	uint64_t current_time;

	current_time = mach_absolute_time();
	clock->last_frame_time = seconds_per_frame(clock->last_update, current_time);
	if (clock->last_frame_time < 1.0)
		clock->time += clock->last_frame_time;
	clock->last_update = current_time;
}

// timestamp_to_array.h

#ifndef TIMESTAMP_TO_ARRAY_H
#define TIMESTAMP_TO_ARRAY_H

#include <linux/types.h>  // for u64 type

extern u64 my_tracing_array[6];  // Declaration of my_tracing_array

//comment 1
//void write_times_tracing_timestamps(void);
void write_times_tracing_timestamps(int, u64);


#endif /* TIMESTAMP_TO_ARRAY_H */

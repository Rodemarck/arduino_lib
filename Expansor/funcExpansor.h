#ifndef FUNC_EXPANSOR_H
#define FUNC_EXPANSOR_H

#define bitClear(a,b) a&=~(1<<b)
#define bitSet(a,b) a|=(1<<b)
#define bitVal(a,b) !!(a & (1<< b))
#define setBit(a,b,c) {bool var_10001=bitVal(a,b);if(var_10001!=c) (c) ? bitSet(a,b); : bitClear(a,b);}
#define DELAY_PULSE 5

#endif
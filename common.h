#ifndef COMMON_H
#define COMMON_H

#define DEBUG

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

#define DEBUG_PRINT_OFF(x) do {} while (0)










#endif /* COMMON_H */

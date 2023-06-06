#ifndef STD_TYPES_H_
#define STD_TYPES_H_


typedef unsigned char		Uint8_t;
typedef signed char			Sint8_t;

typedef unsigned short int	Uint16_t;
typedef unsigned long  int	Uint32_t;

typedef signed long  int	Sint32_t;
typedef signed short int	Sint16_t;

typedef float				Float32_t;
typedef double				Float64_t;

typedef long double			Float128_t;


#ifndef NULL
#define NULL	(void*)0
#endif

typedef void (*cbf_t)(void);


#endif /*STD_TYPES_H_*/

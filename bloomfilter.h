#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__

#include <stdlib.h>

struct bloomfilter {
	unsigned int  m;
	unsigned int  k;
	unsigned char bit_vector[1];
};

void
bloomfilter_init(struct bloomfilter *bloomfilter, unsigned int m, unsigned int k);

void
bloomfilter_set(struct bloomfilter *bloomfilter, void *key, size_t len);

int
bloomfilter_get(struct bloomfilter *bloomfilter, void *key, size_t len);


#endif /* __BLOOMFILTER_H__ */

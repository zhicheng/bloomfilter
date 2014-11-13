#include "bloomfilter.h"

#include <string.h>
#include <unistd.h>

#include "murmur3.h"

#define bit_set(v,n)    ((v)[(n) >> 3] |= (0x1 << (0x7 - ((n) & 0x7))))
#define bit_get(v,n)    ((v)[(n) >> 3] &  (0x1 << (0x7 - ((n) & 0x7))))
#define bit_clr(v,n)    ((v)[(n) >> 3] &=~(0x1 << (0x7 - ((n) & 0x7))))

void
bloomfilter_init(struct bloomfilter *bloomfilter, unsigned int bit_size)
{
	memset(bloomfilter, 0, sizeof(*bloomfilter));
	bloomfilter->bit_size = bit_size;
	memset(bloomfilter->bit_array, 0, bloomfilter->bit_size >> 3);
}

void
bloomfilter_set(struct bloomfilter *bloomfilter, void *key, size_t len)
{
	uint32_t a;
	uint32_t b;

	murmur3_hash32(key, len, 0, &a);
	murmur3_hash32(key, len, 0xdeadbeef, &b);	/* FIXME */

	a %= bloomfilter->bit_size;
	b %= bloomfilter->bit_size;

	bit_set(bloomfilter->bit_array, a);
	bit_set(bloomfilter->bit_array, b);
}

int
bloomfilter_get(struct bloomfilter *bloomfilter, void *key, size_t len)
{
	uint32_t a;
	uint32_t b;

	murmur3_hash32(key, len, 0, &a);
	murmur3_hash32(key, len, 0xdeadbeef, &b);	/* FIXME */

	a %= bloomfilter->bit_size;
	b %= bloomfilter->bit_size;

	a = bit_get(bloomfilter->bit_array, a);
	b = bit_get(bloomfilter->bit_array, b);

	return (a && b);
}

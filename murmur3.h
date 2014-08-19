#ifndef __H_MURMUR3_H__
#define __H_MURMUR3_H__

#include <stdint.h>

void
murmur3_hash32(const void *key, int len, uint32_t seed, void *out);


#endif /* __H_MURMUR3_H__ */

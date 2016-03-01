#include <stdio.h>
#include <stdlib.h>
#define uint8_t unsigned char

struct rNode {
	char* name;
	uint8_t type;
	uint8_t state;
	struct rNode* primary;
	struct rNode* secondary;
};
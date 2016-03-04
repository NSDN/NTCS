#include <stdio.h>
#include <stdlib.h>
#define uint8_t unsigned char

//最高可支持复式分交道岔
//tag不可过长，建议2个字符左右
//state用于标记节点类型，路径点/道岔
//沿运行方向，前方为next，侧向为Sec，后方为prev，侧向为Sec
struct rNode {
	char* name;
	char* tag;
	uint8_t type;
	uint8_t state;
	struct rNode* prevPri;
	struct rNode* prevSec;
	struct rNode* nextPri;
	struct rNode* nextSec;
};
// stores cpu info and utilization
typedef struct _CpuUtilInfo
{
	char name[32];
	unsigned int user;
	unsigned int nice;
	unsigned int system;
	unsigned int idle;
	unsigned int iowait;
	unsigned int irq;
	unsigned int softirq;
	unsigned int stealstolen;
	unsigned int guest;
} CpuUtilInfo;
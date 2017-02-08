#define WINDOWS
#define _CRT_SECURE_NO_WARNINGS

// #define NDEBUG

#include <stdio.h>
#include <stdlib.h>

#ifdef WINDOWS
#include "unistd.h"
#else
#include <unistd.h>
#endif

#include "CpuUtilTool.h"

#define MB_SIZE (1024 * 1024)

static int staticCpuNum = 0;

static void scanCpuUtilInfo(char *buff,
    CpuUtilInfo *cpu)
    {
    sscanf(buff, "%s  %u %u %u %u %u %u %u %u %u", &cpu->name, &cpu->user, &cpu->nice, &cpu->system,
        &cpu->idle, &cpu->iowait, &cpu->irq, &cpu->softirq, &cpu->stealstolen, &cpu->guest);

#ifndef NDEBUG
    printf("%s %u %u %u %u %u %u %u %u %u\n", cpu->name, cpu->user, cpu->nice, cpu->system,
        cpu->idle, cpu->iowait, cpu->irq, cpu->softirq, cpu->stealstolen, cpu->guest);
#endif // !NDEBUG
    }

// 获取当前CPU信息
void getCpuInfo(CpuUtilInfo *total,
    CpuUtilInfo *cpus,
    int cpuNum)
    {
    FILE *fd;
    char buff[1024];
    int n;

#ifdef WINDOWS 
    errno_t err = fopen_s(&fd, "/proc/stat", "r");
#else // Linux
    fd = fopen("/proc/stat", "r");
#endif

    // scan total
    fgets(buff, sizeof(buff), fd);
    scanCpuUtilInfo(buff, total);

    // scan cpus
    for (n = 0; n < cpuNum; n++)
        {
        fgets(buff, sizeof(buff), fd);
        scanCpuUtilInfo(buff, &cpus[n]);
        }

    fclose(fd);
    }

void getTotalCpuInfo(CpuUtilInfo *total) {
    getCpuInfo(total, NULL, 0);
    }

/**
* 计算CPU利用率
*/
void calCpuUseRatio(CpuUtilInfo *old, CpuUtilInfo *newInfo)
    {
    double oldTotal, newTotal, total, idle, user, system, softirq, irq;
    float totalRatio, userRatio, systemRatio, softirqRatio, irqRatio;
    oldTotal = (double)(old->user + old->nice + old->system + old->idle + old->iowait +
        old->irq + old->softirq + old->stealstolen + old->guest);
    newTotal = (double)(newInfo->user + newInfo->nice + newInfo->system + newInfo->idle + newInfo->iowait +
        newInfo->irq + newInfo->softirq + newInfo->stealstolen + newInfo->guest);

    total = newTotal - oldTotal;
    idle = newInfo->idle - old->idle;
    user = newInfo->user - old->user;
    system = newInfo->system - old->system;
    softirq = newInfo->softirq - old->softirq;
    irq = newInfo->irq - old->irq;

    // #ifndef NDEBUG
#ifndef NDEBUG
    //CPU利用率
    totalRatio = (total - idle) / total;
    //用户空间CPU利用率
    userRatio = user / total;
    //内核空间CPU利用率
    systemRatio = system / total;
    //软中断CPU利用率
    softirqRatio = softirq / total;
    //硬中断CPU利用率
    irqRatio = irq / total;

    //printf("total:%f, idle:%f, new->idle:%u, old->idle:%u\n", total, idle, new->idle, old->idle);
    printf("总的CPU利用率为：%f(%f + %f + %f + %f)\n", totalRatio, userRatio, systemRatio, softirqRatio, irqRatio);
#endif
    }

/**
* 获取总的CPU利用率
*/
int getCpuTotalUseRatio()
    {
    CpuUtilInfo oldinfo;
    CpuUtilInfo newinfo;

    getTotalCpuInfo(&oldinfo);
    // sleep(1);
    getTotalCpuInfo(&newinfo);
    calCpuUseRatio(&oldinfo, &newinfo);

    return 0;
    }

//int getCpuDetailUseRatio()
//    {
//    CpuUtilInfo oldinfo[100];
//    CpuUtilInfo newinfo[100];
//    int i;
//    cpu_num = sysconf(_SC_NPROCESSORS_ONLN);
//    getCpuInfo(oldinfo);
//    sleep(1);
//    getCpuInfo(newinfo);
//    for (i=0; i < cpu_num; i++)
//        {
//        calCpuUseRatio(&oldinfo[i], &newinfo[i]);
//        }
//    }


//// 获取内存使用情况
//int getMemInfo(void)
//    {
//    long num_procs;
//    long page_size;
//    long num_pages;
//    long free_pages;
//    long long  mem;
//    long long  free_mem;
//    float mem_per;
//    num_procs = sysconf (_SC_NPROCESSORS_CONF);
//    printf ("CPU 个数为: %ld 个\n", num_procs);
//    page_size = sysconf (_SC_PAGESIZE);
//    printf ("系统页面的大小为: %ld K\n", page_size / 1024 );
//    num_pages = sysconf (_SC_PHYS_PAGES);
//    printf ("系统中物理页数个数: %ld 个\n", num_pages);
//    free_pages = sysconf (_SC_AVPHYS_PAGES);
//    printf ("系统中可用的页面个数为: %ld 个\n", free_pages);
//    mem = (long long) ((long long)num_pages * (long long)page_size);
//    mem /= ONE_MB;
//    free_mem = (long long)free_pages * (long long)page_size;
//    free_mem /= ONE_MB;
//    printf ("总共有 %lld MB 的物理内存, 空闲的物理内存有: %lld MB\n", mem, free_mem);
//    mem_per = (mem-free_mem)*100.0/mem;
//    printf ("内存占用率*100: %f\n", mem_per);
//    return 0;
//    }

#ifdef WINDOWS
int fork(void) { return 0; }

typedef int pid_t;
#endif

// 创建子进程
int createProcess() {

    pid_t fpid;

    if ((fpid = fork()) == -1)
        {
        exit(0);           //创建进程失败，退出程序
        }
    else if (fpid == 0) {  //子进程空间

     // char *args[]={FileMonitor, "-fp", lmonitorList[num].lm_strDirectory,  NULL};
     //if(execve(FileMonitor, args, NULL)< 0) {                        //在子进程中调用FileMonitor进程

     //   printf("execve ./wisFileMonitor -fp %s failed in the child process!/n", lmonitorList[num].lm_strDirectory);
     //    CREATE_THREAD(StartMonitorThread, (THREAD_PARAM) num);
     // }

      //if(execl("./file_creat","file_creat",argv[1],NULL)<0)
      //perror("execl error!");
        return 0;
        }
    else {                //父进程空间
     // lmonitorList[num].lm_pid = fpid;
     // lmonitorList[num].lm_bstop=false;
        return 0;
        }

    }

#ifndef WINDOWS
// Linux entry point
int main(void)
    {
    getCpuTotalUseRatio();
    //getCpuDetailUseRatio();
    //getMemInfo();
    }
#else
// Windows entry point
int main(int argc, char **argv) {}

#endif
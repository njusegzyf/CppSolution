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

// ��ȡ��ǰCPU��Ϣ
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
* ����CPU������
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
    //CPU������
    totalRatio = (total - idle) / total;
    //�û��ռ�CPU������
    userRatio = user / total;
    //�ں˿ռ�CPU������
    systemRatio = system / total;
    //���ж�CPU������
    softirqRatio = softirq / total;
    //Ӳ�ж�CPU������
    irqRatio = irq / total;

    //printf("total:%f, idle:%f, new->idle:%u, old->idle:%u\n", total, idle, new->idle, old->idle);
    printf("�ܵ�CPU������Ϊ��%f(%f + %f + %f + %f)\n", totalRatio, userRatio, systemRatio, softirqRatio, irqRatio);
#endif
    }

/**
* ��ȡ�ܵ�CPU������
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


//// ��ȡ�ڴ�ʹ�����
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
//    printf ("CPU ����Ϊ: %ld ��\n", num_procs);
//    page_size = sysconf (_SC_PAGESIZE);
//    printf ("ϵͳҳ��Ĵ�СΪ: %ld K\n", page_size / 1024 );
//    num_pages = sysconf (_SC_PHYS_PAGES);
//    printf ("ϵͳ������ҳ������: %ld ��\n", num_pages);
//    free_pages = sysconf (_SC_AVPHYS_PAGES);
//    printf ("ϵͳ�п��õ�ҳ�����Ϊ: %ld ��\n", free_pages);
//    mem = (long long) ((long long)num_pages * (long long)page_size);
//    mem /= ONE_MB;
//    free_mem = (long long)free_pages * (long long)page_size;
//    free_mem /= ONE_MB;
//    printf ("�ܹ��� %lld MB �������ڴ�, ���е������ڴ���: %lld MB\n", mem, free_mem);
//    mem_per = (mem-free_mem)*100.0/mem;
//    printf ("�ڴ�ռ����*100: %f\n", mem_per);
//    return 0;
//    }

#ifdef WINDOWS
int fork(void) { return 0; }

typedef int pid_t;
#endif

// �����ӽ���
int createProcess() {

    pid_t fpid;

    if ((fpid = fork()) == -1)
        {
        exit(0);           //��������ʧ�ܣ��˳�����
        }
    else if (fpid == 0) {  //�ӽ��̿ռ�

     // char *args[]={FileMonitor, "-fp", lmonitorList[num].lm_strDirectory,  NULL};
     //if(execve(FileMonitor, args, NULL)< 0) {                        //���ӽ����е���FileMonitor����

     //   printf("execve ./wisFileMonitor -fp %s failed in the child process!/n", lmonitorList[num].lm_strDirectory);
     //    CREATE_THREAD(StartMonitorThread, (THREAD_PARAM) num);
     // }

      //if(execl("./file_creat","file_creat",argv[1],NULL)<0)
      //perror("execl error!");
        return 0;
        }
    else {                //�����̿ռ�
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
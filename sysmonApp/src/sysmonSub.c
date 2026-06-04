#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <epicsTypes.h>
#include <epicsPrint.h>

#include <stdlib.h>      /* getloadavg */
#include <sys/sysctl.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

/* Init: einmalig beim iocInit */
static long sysmonInit(aSubRecord *prec)
{
    return 0;
}

/* Process: bei jedem SCAN-Zyklus */
static long sysmonProcess(aSubRecord *prec)
{
	/* Load Average */
    double loadavg[3] = {0.0, 0.0, 0.0};

    if (getloadavg(loadavg, 3) != 3) {
        epicsPrintf("sysmon: getloadavg() failed\n");
    }

    *(double *)prec->vala = loadavg[0];
    *(double *)prec->valb = loadavg[1];
    *(double *)prec->valc = loadavg[2];

    /* CPU-Anzahl */
    long ncpu = sysconf(_SC_NPROCESSORS_ONLN);
    *(epicsInt32 *)prec->vald = (epicsInt32)ncpu;

    /* Physischer RAM via sysctl */
    uint64_t memsize = 0;
    size_t len = sizeof(memsize);

    if (sysctlbyname("hw.memsize",
                     &memsize,
                     &len,
                     NULL,
                     0) != 0)
    {
        epicsPrintf("sysmon: sysctl hw.memsize failed\n");
    }

    *(double *)prec->vale =
        (double)memsize / (1024.0 * 1024.0 * 1024.0);

    /* Uptime */
    struct timeval boottime = {0, 0};
    len = sizeof(boottime);

    if (sysctlbyname("kern.boottime",
                     &boottime,
                     &len,
                     NULL,
                     0) != 0)
    {
        epicsPrintf("sysmon: sysctl kern.boottime failed\n");
    }

    struct timeval now;
    gettimeofday(&now, NULL);

    *(double *)prec->valf =
        (double)(now.tv_sec - boottime.tv_sec);

    return 0;
}

epicsRegisterFunction(sysmonInit);
epicsRegisterFunction(sysmonProcess);

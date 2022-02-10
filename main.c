#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#define HEADER_IMPL
#include "OpenCLWrapper.h"

int main(void)
{
    cl_platform_id *plats;
    cl_device_id *devices;
    int nplats, ndev;
    InitPlatforms(&plats, &nplats);
    InitDevice(&devices, plats[1], 1, &ndev);
    return 0;
}
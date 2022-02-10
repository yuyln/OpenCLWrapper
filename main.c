#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#define HEADER_IMPL
#include "OpenCLWrapper.h"

int main(void)
{
    int i = 0;
    int nplats, ndev;
    char *kernel;


    cl_platform_id *plats;
    cl_device_id *devices;
    cl_command_queue queue;
    cl_context context;
    cl_program program;

    ReadFile("test.txt", &kernel);
    InitPlatforms(&plats, &nplats);
    InitDevice(&devices, plats[i], i, &ndev);
    InitContext(&context, devices);
    InitQueue(&queue, &context, devices);
    InitProgram(&program, &context, 1, (const char**)&kernel);
    BuildProgram(&program, ndev, devices, NULL);
    return 0;
}
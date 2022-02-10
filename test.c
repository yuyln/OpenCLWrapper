#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
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
    cl_kernel *ks;
    Kernel *Ks;
    char **kernelnames = (char**)malloc(sizeof(char*));
    *kernelnames = "AddMatrix";
    size_t *globalWork;
    size_t *localWork;

    ReadFile("test.cl", &kernel);
    InitPlatforms(&plats, &nplats);
    InitDevice(&devices, plats[i], i, &ndev);
    InitContext(&context, devices);
    InitQueue(&queue, &context, devices);
    InitProgram(&program, &context, 1, (const char**)&kernel);
    BuildProgram(&program, ndev, devices, NULL);
    InitKernels(&ks, &program, (const char**)kernelnames, 1);
    InitKernelsStruct(&Ks, ks, (const char**)kernelnames, 1);
    int nr = 4, nc = 4;
    int nT = nr * nc;
    double *A = malloc(sizeof(double) * nT);
    double *B = malloc(sizeof(double) * nT);
    double *C = malloc(sizeof(double) * nT);

    for (int I = 0; I < nT; I++)
    {
        int j = I % nc;
        int i = (I - j) / nc;
        A[I] = i + j + 1.2;
        B[I] = i + 2.0 * j - 1.3;
    }

    cl_mem bA, bB, bC;
    CreateBuffer(&bA, (void*)A, sizeof(double) * nT, context, CL_MEM_READ_WRITE);
    WriteBuffer(&bA, (void*)A, sizeof(double) * nT, queue);

    CreateBuffer(&bB, (void*)B, sizeof(double) * nT, context, CL_MEM_READ_WRITE);
    WriteBuffer(&bB, (void*)B, sizeof(double) * nT, queue);

    CreateBuffer(&bC, (void*)C, sizeof(double) * nT, context, CL_MEM_READ_WRITE);

    InitGlobalWorkItems(1, &nT, &globalWork);
    InitGroupWorkItemsGCD(1, &nT, &localWork, devices);

    SetKernelArg(&Ks[0], &bA, sizeof(cl_mem), 0);
    SetKernelArg(&Ks[0], &bB, sizeof(cl_mem), 1);
    SetKernelArg(&Ks[0], &bC, sizeof(cl_mem), 2);
    SetKernelArg(&Ks[0], &nr, sizeof(int), 3);
    SetKernelArg(&Ks[0], &nc, sizeof(int), 4);

    EnqueueND(&queue, Ks, 1, NULL, globalWork, localWork);
    Finish(&queue);

    ReadBuffer(&bC, (void*)C, sizeof(double) * nT, queue);
    printf("A = \n");
    for (int I = 0; I < nT; I++)
    {
        int j = I % nc;
        int i = (I - j) / nc;
        printf("%f\t", A[I]);
        if ((I + 1) % nc == 0)
        {
            printf("\n");
        }
    }
    printf("\n");


    printf("B = \n");
    for (int I = 0; I < nT; I++)
    {
        int j = I % nc;
        int i = (I - j) / nc;
        printf("%f\t", B[I]);
        if ((I + 1) % nc == 0)
        {
            printf("\n");
        }
    }
    printf("\n");


    printf("C = \n");
    for (int I = 0; I < nT; I++)
    {
        int j = I % nc;
        int i = (I - j) / nc;
        printf("%f\t", C[I]);
        if ((I + 1) % nc == 0)
        {
            printf("\n");
        }
    }
    return 0;
}

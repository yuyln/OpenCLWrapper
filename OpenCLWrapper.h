#ifndef __OPENCLW
#define __OPENCLW
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HEADER_IMPL
#define PrintCLError(file, err, message) PrintCLError_(file, err, message, __LINE__, __FILE__)

#ifdef __cplusplus
extern "C"
{
#endif

    void PrintCLError_(FILE *f, int err, const char *m, int line, const char *file);

    void CreateBuffer(cl_mem *ref, void *data, size_t datasize, cl_context context, cl_mem_flags flags);
    void WriteBuffer(cl_mem *buffer, void *data, size_t datasize, cl_command_queue queue);
    void WriteBufferOff(cl_mem *buffer, void *data, size_t datasize, size_t off, cl_command_queue queue);
    void ReadBuffer(cl_mem *buffer, void *data, size_t datasize, cl_command_queue queue);
    void ReadBufferOff(cl_mem *buffer, void *data, size_t datasize, size_t off, cl_command_queue queue);

    void ReadFile(const char *path, char **out);

    long unsigned int gcd(long unsigned int a, long unsigned int b);

    void InitPlatforms(cl_platform_id **plat, int *n);
    void InitDevice(cl_device_id **devices, cl_platform_id plat, int iplat, int *n);
    void InitContext(cl_context *context);
    void InitQueue(cl_command_queue *queue);
    void InitKernels(cl_kernel *kernels, const char **names, int n);

#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef HEADER_IMPL

void PrintCLError_(FILE *f, int err, const char *m, int line, const char *file)
{
    if (err != 0)
    {
        fprintf(f, "%s:%d OPENCLWRAPPER ERROR %s:%d\n", file, line, m, err);
        exit(err);
    }
}

void CreateBuffer(cl_mem *ret, void *data, size_t datasize, cl_context context, cl_mem_flags flags)
{
    int err;
    *ret = clCreateBuffer(context, flags, datasize, data, &err);
    PrintCLError(stderr, err, "CREATING BUFFER");
}

void WriteBuffer(cl_mem *buffer, void *data, size_t datasize, cl_command_queue queue)
{
    int err = clEnqueueWriteBuffer(queue, *buffer, CL_TRUE, 0, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "WRITING BUFFER");
}

void WriteBufferOff(cl_mem *buffer, void *data, size_t datasize, size_t off, cl_command_queue queue)
{
    int err = clEnqueueWriteBuffer(queue, *buffer, CL_TRUE, off, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "WRITING BUFFER");
}

void ReadBuffer(cl_mem *buffer, void *data, size_t datasize, cl_command_queue queue)
{
    int err = clEnqueueReadBuffer(queue, *buffer, CL_TRUE, 0, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "READING BUFFER");
}

void ReadBufferOff(cl_mem *buffer, void *data, size_t datasize, size_t off, cl_command_queue queue)
{
    int err = clEnqueueReadBuffer(queue, *buffer, CL_TRUE, off, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "READING BUFFER");
}

void ReadFile(const char *path, char **out)
{
    FILE *f = fopen(path, "r");
    PrintCLError(stderr, errno, strerror(errno));
    fseek(f, 0, SEEK_SET);
    fseek(f, 0, SEEK_END);
    size_t filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    *out = malloc(filesize + 1);
    size_t readsize = fread((void *)(*out), 1, filesize, f);
    if (readsize != filesize)
    {
        PrintCLError(stderr, -1, "READSIZE AND FILESIZE ARE NOT EQUAL");
    }
    (*out)[filesize] = '\0';
}

long unsigned int gcd(long unsigned int a, long unsigned int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

void InitPlatforms(cl_platform_id **plat, int *n)
{
    int n_;
    int err = clGetPlatformIDs(0, NULL, &n_);
    PrintCLError(stderr, err, "GET PLATAFORMS");
    *plat = (cl_platform_id *)malloc(sizeof(cl_platform_id) * n_);

    err = clGetPlatformIDs(n_, *plat, NULL);

    for (int i = 0; i < n_; i++)
    {
        size_t size;
        char *platinfo;
        err = clGetPlatformInfo((*plat)[i], CL_PLATFORM_NAME, 0, NULL, &size);
        PrintCLError(stderr, err, "GET PLATFORM INFO SIZE");
        platinfo = malloc(size);
        err = clGetPlatformInfo((*plat)[i], CL_PLATFORM_NAME, size, platinfo, NULL);
        PrintCLError(stderr, err, "GET PLATFORM INFO");
        printf("PLATAFORM[%d] NAME: %s\n", i, platinfo);
        free(platinfo);
    }

    if (n != NULL)
    {
        *n = n_;
    }
}

void InitDevice(cl_device_id **devices, cl_platform_id plat, int iplat, int *n)
{
    int n_;
    int err = clGetDeviceIDs(plat, CL_DEVICE_TYPE_ALL, 0, NULL, &n_);
    PrintCLError(stderr, err, "GET NUMBER OF DEVICES");
    *devices = (cl_device_id*)malloc(sizeof(cl_device_id) * n_);
    err = clGetDeviceIDs(plat, CL_DEVICE_TYPE_ALL, n_, *devices, NULL);
    PrintCLError(stderr, err, "GET DEVICES IDS");

    for (int i = 0; i < n_; i++)
    {
        size_t size;
        char *deviceinfo;
        err = clGetDeviceInfo((*devices)[i], CL_DEVICE_NAME, 0, NULL, &size);
        PrintCLError(stderr, err, "GET DEVICE INFO SIZE");
        deviceinfo = malloc(size);
        err = clGetDeviceInfo((*devices)[i], CL_DEVICE_NAME, size, deviceinfo, NULL);
        PrintCLError(stderr, err, "GET DEVICE INFO");
        printf("PLATAFORM[%d] DEVICE [%d] NAME: %s\n", iplat, i, deviceinfo);
        free(deviceinfo);
    }
    if (n != NULL)
    {
        *n = n_;
    }
}
// void InitContext(cl_context *context);
// void InitQueue(cl_command_queue *queue);
// void InitKernels(cl_kernel *kernels, const char **names, int n);
#endif // HEADER_IMPL

#endif //__OPENCLW
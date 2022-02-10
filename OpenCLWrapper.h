#ifndef __OPENCLW
#define __OPENCLW
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
    size_t GetMaxWorkFromDevice(cl_device_id *device);
    void InitContext(cl_context *context, cl_device_id *device);
    void InitQueue(cl_command_queue *queue, cl_context *context, cl_device_id *device);
    void InitKernels(cl_kernel **kernels, cl_program *program, const char **names, int n);
    void InitProgram(cl_program *program, cl_context *context, int n, const char **names);
    void BuildProgram(cl_program *program, int ndevices, cl_device_id *devices, const char *opt);

    void InitGlobalWorkItems(int nDims, int *nTodo, size_t **WorkTodo);
    void InitGroupWorkItemsGCD(int nDims, int *nTodo, size_t **WorkTodo, cl_device_id *device);
    void InitGroupWorkItemsYGCD(int nDims, int *nTodo, size_t **WorkTodo, int YGCD);
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

    *out = (char*)malloc(filesize + 1);
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
    cl_uint n_;
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
        platinfo = (char*)malloc(size);
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
    cl_uint n_;
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
        deviceinfo = (char*)malloc(size);
        err = clGetDeviceInfo((*devices)[i], CL_DEVICE_NAME, size, deviceinfo, NULL);
        PrintCLError(stderr, err, "GET DEVICE INFO");
        printf("PLATAFORM[%d] DEVICE [%d] NAME: %s\n", iplat, i, deviceinfo);
        free(deviceinfo);


        size_t dims;
        err = clGetDeviceInfo((*devices)[i], CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, NULL, &dims);
        PrintCLError(stderr, err, "GET DEVICE MAX DIMS");
        dims = dims / sizeof(size_t);
        printf("PLATAFORM[%d] DEVICE [%d] MAX DIMS: %u\n", iplat, i, dims);


        size_t maxWork;
        err = clGetDeviceInfo((*devices)[i], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &maxWork, NULL);
        PrintCLError(stderr, err, "GET DEVICE MAX WORK GROUP SIZE");
        printf("PLATAFORM[%d] DEVICE [%d] MAX WORK GROUP SIZE: %u\n", iplat, i, maxWork);


        size_t *maxWorkPerGroup = (size_t*) malloc(sizeof(size_t) * dims);
        err = clGetDeviceInfo((*devices)[i], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * dims, maxWorkPerGroup, NULL);

        PrintCLError(stderr, err, "GET DEVICE MAX WORK DIMS");
        printf("PLATAFORM[%d] DEVICE [%d] MAX WORK PER DIM: ( ", iplat, i);
        for (int i = 0; i < dims - 1; i++)
        {
            printf("%d, ", maxWorkPerGroup[i]);
        }
        printf("%d )\n", maxWorkPerGroup[dims - 1]);
    }
    if (n != NULL)
    {
        *n = n_;
    }
}

size_t GetMaxWorkFromDevice(cl_device_id *device)
{
    size_t maxWork;
    int err = clGetDeviceInfo(*device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &maxWork, NULL);
    PrintCLError(stderr, err, "GET DEVICE MAX WORK GROUP SIZE");
    return maxWork;
}

void InitContext(cl_context *context, cl_device_id *device)
{
    int err;
    *context = clCreateContext(NULL, 1, device, NULL, NULL, &err);
    PrintCLError(stderr, err, "CREATE CONTEXT");
}

void InitQueue(cl_command_queue *queue, cl_context *context, cl_device_id *device)
{
    int err;
    *queue = clCreateCommandQueue(*context, *device, 0, &err);
    PrintCLError(stderr, err, "CREATE QUEUE");
}

void InitKernels(cl_kernel **kernels, cl_program *program, const char **names, int n)
{
    int err;
    *kernels = (cl_kernel*) malloc(sizeof(cl_kernel) * n);
    for (int i = 0; i < n; i++)
    {
        (*kernels)[i] = clCreateKernel(*program, names[i], &err);
        PrintCLError(stderr, err, "CREATE KERNEL");
    }
}

void InitProgram(cl_program *program, cl_context *context, int n, const char **names)
{
    int err;
    *program = clCreateProgramWithSource(*context, n, names, NULL, &err);
    PrintCLError(stderr, err, "CREATE PROGRAM");
}

void BuildProgram(cl_program *program, int ndevices, cl_device_id *devices, const char *opt)
{
    int err = clBuildProgram(*program, ndevices, devices, opt, NULL, NULL);

    for (int i = 0; i < ndevices; i++)
    {
        size_t length;
        err = clGetProgramBuildInfo(*program, devices[i], CL_PROGRAM_BUILD_LOG, 0, NULL, &length);
        char *buildlog = (char*)malloc(length);
        err = clGetProgramBuildInfo(*program, devices[i], CL_PROGRAM_BUILD_LOG, length, buildlog, NULL);
        printf("PROGRAM ON DEVICE[%d] BUILD LOG: %s\n", i, buildlog);
        PrintCLError(stderr, err, "GET PROGRAM BUILD LOG");
        free(buildlog);
    }
}

void InitGlobalWorkItems(int nDims, int *nTodo, size_t **WorkTodo)
{
    *WorkTodo = (size_t*)malloc(sizeof(size_t) * nDims);
    for (int i = 0; i < nDims; i++)
    {
        (*WorkTodo)[i] = nTodo[i];
    }
}

void InitGroupWorkItemsGCD(int nDims, int *nTodo, size_t **WorkTodo, cl_device_id *device)
{
    *WorkTodo = (size_t*)malloc(sizeof(size_t) * nDims);
    size_t maxW = GetMaxWorkFromDevice(device) / 2;
    for (int i = 0; i < nDims; i++)
    {
        (*WorkTodo)[i] = gcd(maxW, nTodo[i]);
    }
}

void InitGroupWorkItemsYGCD(int nDims, int *nTodo, size_t **WorkTodo, int YGCD)
{
    *WorkTodo = (size_t*)malloc(sizeof(size_t) * nDims);
    for (int i = 0; i < nDims; i++)
    {
        (*WorkTodo)[i] = gcd(YGCD, nTodo[i]);
    }
}
#endif // HEADER_IMPL

#endif //__OPENCLW
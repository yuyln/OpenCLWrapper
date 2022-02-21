#ifndef __OPENCLW
#define __OPENCLW
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define PrintCLError(file, err, message, ...) {                                                                                             \
                                            if (err != 0)                                                                                        \
                                            {                                                                                                    \
                                                fprintf(file, "%s: %d OPENCLWRAPPER ERROR %d: ", __FILE__, __LINE__, err);\
                                                int err_ = abs(err);\
                                                if (err_ >= 30)\
                                                    err_ = err_ - 10;\
                                                fprintf(file, "%s | ", errors[err_]);\
                                                fprintf(file, message, ##__VA_ARGS__);                                                                  \
                                                fprintf(file, "\n");                                                                             \
                                                exit(err);                                                                                       \
                                            }                                                                                                    \
                                          }

    //TODO: can be better?
    typedef struct
    {
        cl_kernel *kernel;
        const char *name;
    } Kernel;

    void InitKernelStruct(Kernel *K, cl_kernel *k, const char *name);
    void InitKernelsStruct(Kernel **K, cl_kernel *k, const char **name, int n);

    void InitKernelStructGround(Kernel *K, cl_kernel *k, cl_program *program, const char *name);
    void InitKernelsStructGround(Kernel **K, cl_kernel **k, cl_program *program, const char **name, int n);

    static const char *errors[60] = {
                                "CL_SUCCESS",
                                "CL_DEVICE_NOT_FOUND",
                                "CL_DEVICE_NOT_AVAILABLE",
                                "CL_COMPILER_NOT_AVAILABLE",
                                "CL_MEM_OBJECT_ALLOCATION_FAILURE",
                                "CL_OUT_OF_RESOURCES",
                                "CL_OUT_OF_HOST_MEMORY",
                                "CL_PROFILING_INFO_NOT_AVAILABLE ",
                                "CL_MEM_COPY_OVERLAP",
                                "CL_IMAGE_FORMAT_MISMATCH",
                                "CL_IMAGE_FORMAT_NOT_SUPPORTED ",
                                "CL_BUILD_PROGRAM_FAILURE ",
                                "CL_MAP_FAILURE   ",
                                "CL_MISALIGNED_SUB_BUFFER_OFFSET",
                                "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST",
                                "CL_COMPILE_PROGRAM_FAILURE",
                                "CL_LINKER_NOT_AVAILABLE",
                                "CL_LINK_PROGRAM_FAILURE",
                                "CL_DEVICE_PARTITION_FAILED",
                                "CL_KERNEL_ARG_INFO_NOT_AVAILABLE",
                                "CL_INVALID_VALUE",
                                "CL_INVALID_DEVICE_TYPE",
                                "CL_INVALID_PLATFORM",
                                "CL_INVALID_DEVICE",
                                "CL_INVALID_CONTEXT",
                                "CL_INVALID_QUEUE_PROPERTIES",
                                "CL_INVALID_COMMAND_QUEUE",
                                "CL_INVALID_HOST_PTR",
                                "CL_INVALID_MEM_OBJECT",
                                "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR",
                                "CL_INVALID_IMAGE_SIZE",
                                "CL_INVALID_SAMPLER",
                                "CL_INVALID_BINARY",
                                "CL_INVALID_BUILD_OPTIONS",
                                "CL_INVALID_PROGRAM",
                                "CL_INVALID_PROGRAM_EXECUTABLE",
                                "CL_INVALID_KERNEL_NAME",
                                "CL_INVALID_KERNEL_DEFINITION",
                                "CL_INVALID_KERNEL",
                                "CL_INVALID_ARG_INDEX",
                                "CL_INVALID_ARG_VALUE",
                                "CL_INVALID_ARG_SIZE",
                                "CL_INVALID_KERNEL_ARGS",
                                "CL_INVALID_WORK_DIMENSION",
                                "CL_INVALID_WORK_GROUP_SIZE",
                                "CL_INVALID_WORK_ITEM_SIZE",
                                "CL_INVALID_GLOBAL_OFFSET",
                                "CL_INVALID_EVENT_WAIT_LIST",
                                "CL_INVALID_EVENT",
                                "CL_INVALID_OPERATION",
                                "CL_INVALID_GL_OBJECT",
                                "CL_INVALID_BUFFER_SIZE",
                                "CL_INVALID_MIP_LEVEL",
                                "CL_INVALID_GLOBAL_WORK_SIZE",
                                "CL_INVALID_PROPERTY",
                                "CL_INVALID_IMAGE_DESCRIPTOR",
                                "CL_INVALID_COMPILER_OPTIONS",
                                "CL_INVALID_LINKER_OPTIONS",
                                "CL_INVALID_DEVICE_PARTITION_COUNT",
                            };

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
    size_t GetMaxAllocMemoryBytesDevice(cl_device_id *device);
    size_t GetMaxMemoryBytesDevice(cl_device_id *device);
    void InitContext(cl_context *context, cl_device_id *device);
    void InitQueue(cl_command_queue *queue, cl_context *context, cl_device_id *device);
    void InitKernels(cl_kernel **kernels, cl_program *program, const char **names, int n);
    void InitKernel(cl_kernel *kernel, cl_program *program, const char *name);
    void InitProgram(cl_program *program, cl_context *context, int n, const char **names);
    void BuildProgram(cl_program *program, int ndevices, cl_device_id *devices, const char *opt);
    void BuildProgramOnDevice(cl_program *program, int idevice, cl_device_id *device, const char *opt);

    void InitGlobalWorkItems1D(int nTodo, size_t *WorkTodo);
    void InitGroupWorkItemsGCD1D(int nTodo, size_t *WorkTodo, cl_device_id *device);
    void InitGroupWorkItemsYGCD1D(int nTodo, size_t *WorkTodo, int YGCD);

    void InitGlobalWorkItemsND(int nDims, int *nTodo, size_t **WorkTodo);
    void InitGroupWorkItemsGCDND(int nDims, int *nTodo, size_t **WorkTodo, cl_device_id *device);
    void InitGroupWorkItemsYGCDND(int nDims, int *nTodo, size_t **WorkTodo, int YGCD);

    void EnqueueND(cl_command_queue *queue, Kernel *kernel, cl_uint ndim, size_t *offset, 
                   size_t *globalWork, size_t *localWork);
    void EnqueueNDk(cl_command_queue *queue, cl_kernel *kernel, cl_uint ndim, size_t *offset, 
                   size_t *globalWork, size_t *localWork);

    void Finish(cl_command_queue *q);

    void SetKernelArg(Kernel *kernel, void *data, size_t datasize, cl_uint i);
    void SetKernelArgk(cl_kernel *kernel, void *data, size_t datasize, cl_uint i);

#ifdef OPENCLWRAPPER_IMPLEMTATION

void InitKernelStruct(Kernel *K, cl_kernel *k, const char *name)
{
    K->kernel = k;
    K->name = name;
}

void InitKernelsStruct(Kernel **K, cl_kernel *k, const char **name, int n)
{
    *K = (Kernel*) malloc(sizeof(Kernel) * n);
    for (int i = 0; i < n; i++)
    {
        InitKernelStruct(&(*K)[i], &k[i], name[i]);
    }
}

void InitKernelStructGround(Kernel *K, cl_kernel *k, cl_program *program, const char *name)
{
    InitKernel(k, program, name);
    K->kernel = k;
    K->name = name;
}

void InitKernelsStructGround(Kernel **K, cl_kernel **k, cl_program *program, const char **name, int n)
{
    InitKernels(k, program, name, n);
    *K = (Kernel*) malloc(sizeof(Kernel) * n);
    for (int i = 0; i < n; i++)
    {
        InitKernelStruct(&(*K)[i], &(*k)[i], name[i]);
    }
}

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
    PrintCLError(stderr, err, "CREATING BUFFER WITH DATASIZE: %zu", datasize);
}

void WriteBuffer(cl_mem *buffer, void *data, size_t datasize, cl_command_queue queue)
{
    int err = clEnqueueWriteBuffer(queue, *buffer, CL_TRUE, 0, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "WRITING BUFFER WITH DATASIZE: %zu", datasize);
}

void WriteBufferOff(cl_mem *buffer, void *data, size_t datasize, size_t off, cl_command_queue queue)
{
    int err = clEnqueueWriteBuffer(queue, *buffer, CL_TRUE, off, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "WRITING BUFFER OFFSET WITH DATASIZE: %zu", datasize);
}

void ReadBuffer(cl_mem *buffer, void *data, size_t datasize, cl_command_queue queue)
{
    int err = clEnqueueReadBuffer(queue, *buffer, CL_TRUE, 0, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "READING BUFFER WITH DATASIZE: %zu", datasize);
}

void ReadBufferOff(cl_mem *buffer, void *data, size_t datasize, size_t off, cl_command_queue queue)
{
    int err = clEnqueueReadBuffer(queue, *buffer, CL_TRUE, off, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "READING BUFFER OFFSET WITH DATASIZE: %zu", datasize);
}

void ReadFile(const char *path, char **out)
{
    FILE *f = fopen(path, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "FILE (%s) IS NULL: %s", path, strerror(errno));
    }
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
    fclose(f);
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
    #if defined(unix) || defined(__unix) || defined(__unix)
    setenv("CUDA_CACHE_DISABLE", "1", 1);
    #elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    _putenv_s("CUDA_CACHE_DISABLE", "1");
    #elif defined(__APPLE__) || defined(__MACH__)
    setenv("CUDA_CACHE_DISABLE", "1", 1);
    #endif

    cl_uint n_;
    int err = clGetPlatformIDs(0, NULL, &n_);
    PrintCLError(stderr, err, "GET PLATAFORMS");
    *plat = (cl_platform_id *)malloc(sizeof(cl_platform_id) * n_);

    err = clGetPlatformIDs(n_, *plat, NULL);

    for (cl_uint i = 0; i < n_; i++)
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

    for (cl_uint i = 0; i < n_; i++)
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
        printf("PLATAFORM[%d] DEVICE [%d] MAX DIMS: %zu\n", iplat, i, dims);


        size_t maxWork = GetMaxWorkFromDevice(&(*devices)[i]);
        // err = clGetDeviceInfo((*devices)[i], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &maxWork, NULL);
        // PrintCLError(stderr, err, "GET DEVICE MAX WORK GROUP SIZE");
        printf("PLATAFORM[%d] DEVICE [%d] MAX WORK GROUP SIZE: %zu\n", iplat, i, maxWork);


        size_t *maxWorkPerGroup = (size_t*) malloc(sizeof(size_t) * dims);
        err = clGetDeviceInfo((*devices)[i], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * dims, maxWorkPerGroup, NULL);

        PrintCLError(stderr, err, "GET DEVICE MAX WORK DIMS");
        printf("PLATAFORM[%d] DEVICE [%d] MAX WORK PER DIM: ( ", iplat, i);
        for (cl_uint i = 0; i < dims - 1; i++)
        {
            printf("%zu, ", maxWorkPerGroup[i]);
        }
        printf("%zu )\n", maxWorkPerGroup[dims - 1]);

        size_t maxMemAlloc = GetMaxAllocMemoryBytesDevice(&(*devices)[i]);
        printf("PLATAFORM[%d] DEVICE [%d] MAX ALLOC MEMORY: %.3f  kB\n", iplat, i, (double)maxMemAlloc / 1000.0);

        size_t maxMemGlob = GetMaxMemoryBytesDevice(&(*devices)[i]);
        printf("PLATAFORM[%d] DEVICE [%d] MAX GLOB MEMORY: %.3f  kB\n", iplat, i, (double)maxMemGlob / 1000.0);
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

size_t GetMaxAllocMemoryBytesDevice(cl_device_id *device)
{
    size_t maxMem;
    int err = clGetDeviceInfo(*device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(size_t), &maxMem, NULL);
    PrintCLError(stderr, err, "GET DEVICE MAX ALLOC MEM SIZE");
    return maxMem;
}

size_t GetMaxMemoryBytesDevice(cl_device_id *device)
{
    size_t maxMem;
    int err = clGetDeviceInfo(*device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(size_t), &maxMem, NULL);
    PrintCLError(stderr, err, "GET DEVICE MAX GLOBAL MEM SIZE");
    return maxMem;
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

void InitKernel(cl_kernel *kernel, cl_program *program, const char *name)
{
    int err;
    *kernel = clCreateKernel(*program, name, &err);
    PrintCLError(stderr, err, "CREATE KERNEL %s", name);
}

void InitKernels(cl_kernel **kernels, cl_program *program, const char **names, int n)
{
    *kernels = (cl_kernel*) malloc(sizeof(cl_kernel) * n);
    for (int i = 0; i < n; i++)
    {
        InitKernel(&(*kernels)[i], program, names[i]);
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

void BuildProgramOnDevice(cl_program *program, int idevice, cl_device_id *device, const char *opt)
{
    int err = clBuildProgram(*program, 1, device, opt, NULL, NULL);
    size_t length;
    err = clGetProgramBuildInfo(*program, *device, CL_PROGRAM_BUILD_LOG, 0, NULL, &length);
    char *buildlog = (char*)malloc(length);
    err = clGetProgramBuildInfo(*program, *device, CL_PROGRAM_BUILD_LOG, length, buildlog, NULL);
    printf("PROGRAM ON DEVICE[%d] BUILD LOG: %s\n", idevice, buildlog);
    PrintCLError(stderr, err, "GET PROGRAM BUILD LOG");
    free(buildlog);
}

void InitGlobalWorkItems1D(int nTodo, size_t *WorkTodo)
{
    *WorkTodo = nTodo;
}

void InitGroupWorkItemsGCD1D(int nTodo, size_t *WorkTodo, cl_device_id *device)
{
    size_t maxW = GetMaxWorkFromDevice(device) / 2;
    *WorkTodo = gcd(maxW, nTodo);
}

void InitGroupWorkItemsYGCD1D(int nTodo, size_t *WorkTodo, int YGCD)
{
    *WorkTodo = gcd(YGCD, nTodo);
}

void InitGlobalWorkItemsND(int nDims, int *nTodo, size_t **WorkTodo)
{
    *WorkTodo = (size_t*)malloc(sizeof(size_t) * nDims);
    for (int i = 0; i < nDims; i++)
    {
        (*WorkTodo)[i] = nTodo[i];
    }
}

void InitGroupWorkItemsGCDND(int nDims, int *nTodo, size_t **WorkTodo, cl_device_id *device)
{
    *WorkTodo = (size_t*)malloc(sizeof(size_t) * nDims);
    size_t maxW = GetMaxWorkFromDevice(device) / 2;
    for (int i = 0; i < nDims; i++)
    {
        (*WorkTodo)[i] = gcd(maxW, nTodo[i]);
    }
}

void InitGroupWorkItemsYGCDND(int nDims, int *nTodo, size_t **WorkTodo, int YGCD)
{
    *WorkTodo = (size_t*)malloc(sizeof(size_t) * nDims);
    for (int i = 0; i < nDims; i++)
    {
        (*WorkTodo)[i] = gcd(YGCD, nTodo[i]);
    }
}

void EnqueueND(cl_command_queue *queue, Kernel *kernel, cl_uint ndim, size_t *offset, 
                size_t *globalWork, size_t *localWork)
{
    int err = clEnqueueNDRangeKernel(*queue, *(kernel->kernel), ndim, offset, globalWork, localWork, 0, NULL, NULL);
    PrintCLError(stderr, err, "ENQUEUE ND RANGE KERNEL %s", kernel->name);
}

void EnqueueNDk(cl_command_queue *queue, cl_kernel *kernel, cl_uint ndim, size_t *offset, 
                size_t *globalWork, size_t *localWork)
{
    int err = clEnqueueNDRangeKernel(*queue, *kernel, ndim, offset, globalWork, localWork, 0, NULL, NULL);
    PrintCLError(stderr, err, "ENQUEUE ND RANGE KERNEL");
}

void Finish(cl_command_queue *q)
{
    int err = clFinish(*q);
    PrintCLError(stderr, err, "FINISH QUEUE");
}

void SetKernelArg(Kernel *kernel, void *data, size_t datasize, cl_uint i)
{
    int err = clSetKernelArg(*(kernel->kernel), i, datasize, data);
    PrintCLError(stderr, err, "ERROR SETTING ARG %d OF KERNEL %s", i, kernel->name);
}

void SetKernelArgk(cl_kernel *kernel, void *data, size_t datasize, cl_uint i)
{
    int err = clSetKernelArg(*kernel, i, datasize, data);
    PrintCLError(stderr, err, "ERROR SETTING ARG %d OF SIZE %zu", i, datasize);
}

#endif // HEADER_IMPL

#endif //__OPENCLW
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

#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef HEADER_IMPL

void PrintCLError_(FILE *f, int err, const char *m, int line, const char *file)
{
    if (err != 0)
    {
        fprintf(f, "%s:%d OPENCL ERROR %s:%d\n", file, line, m, err);
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
    PrintCLError(stderr, err, "WRITING BUFFER");

}

void ReadBufferOff(cl_mem *buffer, void *data, size_t datasize, size_t off, cl_command_queue queue)
{
    int err = clEnqueueReadBuffer(queue, *buffer, CL_TRUE, off, datasize, data, 0, NULL, NULL);
    PrintCLError(stderr, err, "WRITING BUFFER");

}

void ReadFile(const char *path, char **out)
{
    
}

#endif // HEADER_IMPL

#endif //__OPENCLW
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

kernel void AddMatrix(global const double *A, global const double *B, global double *C, const int nr, const int nc)
{
    int i = get_global_id(0);
    C[i] = A[i] + B[i];
}
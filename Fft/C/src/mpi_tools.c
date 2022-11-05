#include "mpi_tools.h"


int get_msg_id(int processnum, int maxnum, int messagenum)
{
    return processnum + maxnum*messagenum;
}


MPI_Request *alloc_msg_request(int numrequests)
{
    return (MPI_Request *) malloc(numrequests * sizeof(MPI_Request));
}


void dealloc_msg_request(MPI_Request **request)
{
    free(*request);
    *request = NULL;
}


MPI_Status *alloc_msg_status(int numstatus)
{
    return (MPI_Status *) malloc(numstatus * sizeof(MPI_Status));
}


void dealloc_msg_status(MPI_Status **status)
{
    free(*status);
    *status = NULL;
}

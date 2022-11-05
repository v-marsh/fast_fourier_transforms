#ifndef MPITOOLS
#define MPITOOLS

    #include <stdlib.h>
    #include <mpi.h>
    
    
    int get_msg_id(int processnum, int maxnum, int messagenum);


    MPI_Request *alloc_msg_request(int numrequests);


    void dealloc_msg_request(MPI_Request **request);


    MPI_Status *alloc_msg_status(int numstatus);

    
    void dealloc_msg_status(MPI_Status **status);
#endif
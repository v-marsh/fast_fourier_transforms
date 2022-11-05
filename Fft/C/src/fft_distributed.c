#include "fft_distributed.h"

void fft_distributed(struct complexarr **arr, unsigned int elementsperprocess)
{
    // Number of double precision datapoints in each process, a complex
    // number contains two double precision floats
    unsigned int doubleperprocess = elementsperprocess * 2;
    // Set variables for determining toal number of processes and process id
    int processsize, processid; 
    // Allocate variables for complex complex roots
    struct complexarr *roots;
    unsigned int n_roots = (*arr)->len / 2;
    // Set tolerance for comparing floating point numbers
    double epsilon = 1e-9;
    // Determine the log2 values for the number of processors and array length
    int processsize_pow_of_2 = check_pow_of_2((unsigned int) processsize, epsilon);
    int arr_pow_of_2 = check_pow_of_2((*arr)->len, epsilon);

    MPI_Comm_size(MPI_COMM_WORLD, &processsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &processid);

    if (processid == 0){  
        // Determine that the number of processors and array length are a 
        // power of 2  
        if (processsize_pow_of_2 == -1){
            perror("Error: number of processors not pow of 2\n");
            exit(EXIT_FAILURE);
        }
        if (arr_pow_of_2 == -1){
            perror("Error: array length not pow of 2\n");
            exit(EXIT_FAILURE);
        }
        // Calculate complex roots
        roots = _getrootsofunity(n_roots * 2, n_roots);
    }
    // Broadcast complex roots and scatter input array to all processes
    MPI_Request *arrreq, *rootreq;
    MPI_Status *arrstatus, *rootsatus;
    MPI_Iscatter((*arr)->val, doubleperprocess, MPI_DOUBLE, (*arr)->val, doubleperprocess, MPI_DOUBLE, 0, MPI_COMM_WORLD, arrreq);
    MPI_Ibcast(roots, n_roots, MPI_DOUBLE, 0, MPI_COMM_WORLD,  rootreq);
    MPI_Wait(arrreq, arrstatus);
    if (processid == 0){
        // All data is sent, realloc and truncate to remove redundant values
        (*arr)->val = realloc(*arr, elementsperprocess * sizeof(struct complexnum));
        }
    MPI_Wait(rootreq, rootsatus);
    // Compute fft
    for (int iteration = 0; iteration < arr_pow_of_2; iteration++){
        if (iteration < processsize_pow_of_2){
            // Locate complementary process
            unsigned int complement = get_complement(processid, iteration, processsize_pow_of_2);
            /* Exchange half of data with complimentary process and
            compute gentleman sande butterfly */
            struct complexnum *msgstart, *receivestart;
            if (processid < complement){
            msgstart = (*arr)->val + doubleperprocess / 2; 
            receivestart = (*arr)->val;        
            }
            else{
                msgstart = (*arr)->val;
                receivestart = (*arr)->val + doubleperprocess / 2;
            }
            int msg1id = get_msg_id(processid, processsize, 1);
            MPI_Request *msg1reqs = alloc_msg_request(2);
            MPI_Status *msg1status = alloc_msg_status(2);
            MPI_Isend((void *) msgstart, doubleperprocess / 2, MPI_DOUBLE, complement, msg1id, MPI_COMM_WORLD, msg1reqs[0]);
            MPI_Irecv((void *) receivestart, doubleperprocess / 2, MPI_DOUBLE, complement, msg1id, MPI_COMM_WORLD, msg1reqs[1]);
            MPI_Waitall(2, msg1reqs, msg1status);
            dealloc_msg_request(&msg1reqs);
            dealloc_msg_status(&msg1status);
            gentleman_sande_butterfly(*arr, roots, elementsperprocess, 1);
            // Send back same half of data
            int msg2id = get_msg_id(processid, processsize, 2);
            MPI_Request *msg2reqs = alloc_msg_request(2);
            MPI_Status *msg2status = alloc_msg_status(2);
            MPI_Isend((void *) msgstart, doubleperprocess / 2, MPI_DOUBLE, 
                complement, msg2id, MPI_COMM_WORLD, msg2reqs[0]);
            MPI_Irecv((void *) receivestart, doubleperprocess / 2, MPI_DOUBLE, 
                complement, msg2id, MPI_COMM_WORLD, msg2reqs[1]);
            MPI_Waitall(2, msg1reqs, msg1status);
        }
        /* All subsequent gentleman sande butterfly operations are local
        to each process, thus can use local gentleman sande butterfly */ 
        else{
            // NOTE: THIS DOES NOT WORK SINCE IT WILL BITREVERSE THE WORNG BITS
            fft_iterative_ordered(arr);
        }
        // NOTE: collect all output back to root node
        MPI_Gather((*arr)->val, doubleperprocess, MPI_DOUBLE, (*arr)->val, 
            doubleperprocess, MPI_DOUBLE, 0 , MPI_COMM_WORLD);

    }
    /*
    Logic for distributed fft:
    Determine the index being iteratited
    if index is strictly less than processize pow of two then the 
        complementary data is in another processor:
        Determine the processor location with the complementary data
        Fetch data half of data
        Compute gentlemans sande butterfly
        return half of final values to original processor
    if index is structly less than arr pow of two:
        compute usual gentleman sande butterfly
    else:
        compute bit reversal value for all data and send both to master
        process
    
    */

}
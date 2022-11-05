# Project Notes
## Things to investigate
* Multithreading with open MP
    * look at different scheduling and chunck sizes (range in powers of 2?)
* Multiprocessing with open MPI
* Register level parallelisation with avx
* Look at different vector sizes

## Physics to investigate
* image sharpening through deconvolution of gaussian image noise

## Notes when plotting data
* Don't plot data in time domain, plot efficiency and speedup instead
    * can also plot time data, but only if the other two have already been invesitgated
    * Consider using reciprocal time plots to increase dynamic range

## Notes on MPI
* Synchronous send does not block computation unless message exceeds the size of the send buffer. If the message size is below the buffersize then it will only block further computation untill the message has been copied onto the buffer.
* Think about granulairty, too large => synchonisation overhead, too small => communication overhead


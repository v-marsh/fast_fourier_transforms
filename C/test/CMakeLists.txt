include_directories(../)

add_executable(test_creation_destruction_rootsofunity
    test_creation_destruction_rootsofunity.c
    ../fft_iterative.h)
target_link_libraries(test_creation_destruction_rootsofunity
    fft_iterative)
add_test(NAME creation_destruction_rootsofunity
    COMMAND test_creation_destruction_rootsofunity)
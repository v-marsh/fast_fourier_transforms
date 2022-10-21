set(SRC ../src)

include_directories(${SRC})

add_executable(test_tools
    test_tools.c
    ${SRC}/tools.h)
target_link_libraries(test_tools
    tools
    m)
add_test(NAME tools
    COMMAND test_tools)

add_executable(test_allocation_destruction_complexarr
    test_allocation_destruction_complexarr.c
    ${SRC}/fft_iterative.h)
target_link_libraries(test_allocation_destruction_complexarr
    fft_iterative)
add_test(NAME allocation_destruction_compexarr
    COMMAND test_allocation_destruction_complexarr)

add_executable(test_creation_destruction_rootsofunity
    test_creation_destruction_rootsofunity.c
    ${SRC}/fft_iterative.h)
target_link_libraries(test_creation_destruction_rootsofunity
    fft_iterative)
add_test(NAME creation_destruction_rootsofunity
    COMMAND test_creation_destruction_rootsofunity)

add_executable(test_fft_iterative
    test_fft_iterative.c
    ${SRC}/fft_iterative.h)

target_link_libraries(test_fft_iterative
    fft_iterative
    tools)
add_test(NAME fft_iterative
    COMMAND test_fft_iterative)


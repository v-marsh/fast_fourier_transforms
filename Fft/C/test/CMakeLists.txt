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
    ${SRC}/fft_iterative.h
    ${SRC}/tools.h)
target_link_libraries(test_fft_iterative
    fft_iterative
    tools)
add_test(NAME compare_fft_iterative_outputs_to_correct_values
    COMMAND test_fft_iterative)

add_executable(test_fft_threaded
    test_fft_threaded.c
    ${SRC}/fft_threaded.h
    ${SRC}/tools.h)
target_link_libraries(test_fft_threaded
    fft_threaded
    tools)
add_test(NAME compare_fft_threaded_outputs_to_correct_values
    COMMAND test_fft_threaded)

add_executable(time_fft_iterative
    time_fft_iterative.c
    ${SRC}/fft_iterative.h)
target_link_libraries(time_fft_iterative
    fft_iterative
    m)
add_test(NAME fft_iterative_timed
    COMMAND time_fft_iterative)

add_executable(time_fft_threaded
    time_fft_threaded.c
    ${SRC}/fft_threaded.h)
target_link_libraries(time_fft_threaded
    fft_threaded
    m)
add_test(NAME fft_threaded_timed
    COMMAND time_fft_threaded)

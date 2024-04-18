cmake_minimum_required(VERSION 3.26)
project(memoryCapture)

set(CMAKE_CXX_STANDARD 17)

add_executable(memoryCapture main.cpp
        captureManager.h
        LSH.h
        LSH.cpp
        FP754.cpp
        FP754.h
        deltaManager.cpp
        deltaManager.h
        distanceFunction.cpp
        distanceFunction.h
        Averages.cpp
        Averages.h
)

# Set this to the root directory of your OpenSSL installation
set(OPENSSL_ROOT_DIR /path/to/openssl)

find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    # Example of adding an executable that links against OpenSSL
    add_executable(YourExecutableName main.cpp)
    target_link_libraries(YourExecutableName ${OPENSSL_LIBRARIES})
endif()

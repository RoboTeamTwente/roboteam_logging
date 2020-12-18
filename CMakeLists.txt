find_package(Qt5 COMPONENTS Core REQUIRED)
add_library(logging STATIC
        src/RTTLogWriter.cpp
        src/RTTLogReader.cpp
        )

target_link_libraries(logging
        PUBLIC roboteam_proto
        PUBLIC Qt5::Core)

target_include_directories(logging
        INTERFACE include
        PRIVATE include/logging)
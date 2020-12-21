find_package(Qt5 COMPONENTS Core REQUIRED)
add_library(logging STATIC
        src/RTTLogWriter.cpp
        src/RTTLogReader.cpp
        src/RTTLogPlayer.cpp
        )

target_link_libraries(logging
        PUBLIC roboteam_proto
        PUBLIC Qt5::Core
        PRIVATE roboteam_utils
        )

target_include_directories(logging
        INTERFACE include
        PRIVATE include/logging)


add_executable(roboteam_logger
        roboteam_logger.cpp)
target_link_libraries(roboteam_logger
        PRIVATE logging
        PRIVATE roboteam_utils
        )

add_executable(roboteam_logplayer
        roboteam_logplayer.cpp)
target_link_libraries(roboteam_logplayer
        PRIVATE logging
        PRIVATE roboteam_utils
        )

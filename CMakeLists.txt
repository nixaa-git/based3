cmake_minimum_required(VERSION 3.15)

project(based)

#add_subdirectory(dependencies/mysql-connector-cpp)

file(GLOB src
    dependencies/enet/*.c
    dependencies/proton/*.cpp
    source/*.cpp
    source/Utility/*.cpp
    source/Data/*.cpp
    source/Network/*.cpp
    source/SQL/*.cpp
    source/Manager/*.cpp
    source/Events/*.cpp
    source/Events/GenericText/*.cpp
)

include_directories(
    dependencies/
)

add_executable(${PROJECT_NAME}
    ${src}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    C_STANDARD 11
)

#find_package(mysql-concpp REQUIRED)

# for windows builds !!
target_link_libraries(${PROJECT_NAME}
    Ws2_32
    winmm
    kernel32
    #mysql::concpp
)
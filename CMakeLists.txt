cmake_minimum_required(VERSION 3.15)

project(based)

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

if (WIN32)

    set(MYSQL_DIR "C:/Program Files/MySQL/MySQL Server 9.4")

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${MYSQL_DIR}/include
    )

    target_link_directories(${PROJECT_NAME} PRIVATE
        ${MYSQL_DIR}/lib
    )

endif()

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
    libmysql.lib
)
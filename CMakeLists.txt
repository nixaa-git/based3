cmake_minimum_required(VERSION 3.15)

project(based)

if(WIN32)
    SET(ENET_PLATFORM win32.c)
else()
    SET(ENET_PLATFORM unix.c) 
endif()

file(GLOB deps

    # enet
    dependencies/enet/callbacks.c
    dependencies/enet/compress.c
    dependencies/enet/host.c
    dependencies/enet/list.c
    dependencies/enet/packet.c
    dependencies/enet/peer.c
    dependencies/enet/protocol.c
    dependencies/enet/${ENET_PLATFORM}

    # proton
    dependencies/proton/*.cpp
)

file(GLOB src
    dependencies/enet/*.c
    dependencies/proton/*.cpp
    source/*.cpp
    source/Utility/*.cpp
    source/Data/*.cpp
    source/World/*.cpp
    source/Network/*.cpp
    source/SQL/*.cpp
    source/Manager/*.cpp
    source/Events/*.cpp
    source/Events/GenericText/*.cpp
    source/Events/GameMessage/*.cpp
    source/Events/GamePacket/*.cpp
    source/Commands/*.cpp
    source/Commands/Func/*.cpp
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

if (WIN32)

    # Install MySQL Server 8.1 from https://downloads.mysql.com/archives/community/
    set(MYSQL_DIR "C:/Program Files/MySQL/MySQL Server 8.1")

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${MYSQL_DIR}/include
    )

    target_link_directories(${PROJECT_NAME} PRIVATE
        ${MYSQL_DIR}/lib
    )

    target_compile_definitions(${PROJECT_NAME} PUBLIC
        WIN32_LEAN_AND_MEAN
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Program Files/MySQL/MySQL Server 8.1/lib/libmysql.dll"
        $<TARGET_FILE_DIR:based>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Program Files/MySQL/MySQL Server 8.1/bin/libssl-3-x64.dll"
        $<TARGET_FILE_DIR:based>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Program Files/MySQL/MySQL Server 8.1/bin/libcrypto-3-x64.dll"
        $<TARGET_FILE_DIR:based>
    )

    # for windows builds !!
    target_link_libraries(${PROJECT_NAME}
        Ws2_32
        winmm
        kernel32
        libmysql.lib
    )

else()
    find_path(MYSQL_INCLUDE_DIR
        mysql/mysql.h
	PATHS /usr/include /usr/local/include
    )

    find_library(MYSQL_LIBRARY
        NAMES mysqlclient
	PATHS /usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib
    )

    message(STATUS "MySQL include directory: ${MYSQL_INCLUDE_DIR}")
    message(STATUS "MySQL lib path: ${MYSQL_LIBRARY}")

    target_include_directories(${PROJECT_NAME} PRIVATE
	    ${MYSQL_INCLUDE_DIR}
    )

    target_link_libraries(${PROJECT_NAME}
	    ${MYSQL_LIBRARY}
    )
endif()

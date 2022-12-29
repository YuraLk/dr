cmake_minimum_required (VERSION 3.8)

project(server)

if (WIN32)
    add_definitions(
        -D_CRT_SECURE_NO_WARNINGS
        -D_WINSOCK_DEPRECATED_NO_WARNINGS
        -DNO_GETIFADDRS
    )
else()
    add_definitions(
        -DSOCKLEN_T=socklen_t 
        -D_LARGEFILE_SOURCE=1 
        -D_FILE_OFFSET_BITS=64
    )
endif()


#Указываем включаемые каталоги
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/live555/BasicUsageEnvironment/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/live555/groupsock/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/live555/UsageEnvironment/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/live555/liveMedia/include
)

#Собираем список исходных файлов
file(GLOB LIVE555_SRC
    external/live555/BasicUsageEnvironment/*.cpp
    external/live555/groupsock/*.cpp 
    external/live555/groupsock/*.c
    external/live555/UsageEnvironment/*.cpp
    external/live555/liveMedia/*.hh 
    external/live555/liveMedia/*.cpp 
    external/live555/liveMedia/*.c
)

#Список файлов проекта
file(GLOB STREAM_SERVER_SRC
    ${LIVE555_SRC}
    src/*.h
    src/*.cpp
    src/*.c
)


find_package(OpenSSL REQUIRED)

add_executable(RTSPServer ${STREAM_SERVER_SRC})


if (WIN32)
 add_definitions(-DNO_GETIFADDRS)
endif(WIN32)

if (WIN32)
    target_link_libraries(RTSPServer 
        ws2_32
        OpenSSL::SSL 
	OpenSSL::Crypto
    )
else()
    target_link_libraries(RTSPServer
        OpenSSL::SSL 
	OpenSSL::Crypto
    )
endif()
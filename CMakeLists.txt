cmake_minimum_required(VERSION 3.22)
project(MimikyuPCAP C)
include(ExternalProject)

set(CMAKE_C_STANDARD 11)

include_directories(include src)

set(MIMIKYU_PCAP_HEADER     src/mimikyu/pcap.h)

add_library(MimikyuPCAP STATIC ${MIMIKYU_PCAP_HEADER}
                               src/mimikyu/pcap.c)

set_target_properties(MimikyuPCAP PROPERTIES PUBLIC_HEADER "${MIMIKYU_PCAP_HEADER}")

ExternalProject_Add(Mimikyu 
                    GIT_REPOSITORY https://github.com/MimikyuBio/Mimikyu.git
                    GIT_TAG "origin/main"
                    PREFIX ${PROJECT_SOURCE_DIR}/lib/Mimikyu
                    TMP_DIR ${PROJECT_SOURCE_DIR}/lib/Mimikyu/tmp
                    STAMP_DIR ${PROJECT_SOURCE_DIR}/lib/Mimikyu/stamp
                    SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/Mimikyu/git
                    BINARY_DIR ${PROJECT_SOURCE_DIR}/lib/Mimikyu/build
                    INSTALL_DIR ${PROJECT_SOURCE_DIR}/lib/Mimikyu/lib
                    CONFIGURE_COMMAND ${CMAKE_COMMAND}
                                      -DCMAKE_BUILD_TYPE=Debug
                                      -S ${PROJECT_SOURCE_DIR}/lib/Mimikyu/git
                                      -B ${PROJECT_SOURCE_DIR}/lib/Mimikyu/build
                                      --install-prefix  ${PROJECT_SOURCE_DIR})

add_dependencies(MimikyuPCAP Mimikyu)

install(TARGETS MimikyuPCAP ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/src/ DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
                  FILES_MATCHING PATTERN "*.h")

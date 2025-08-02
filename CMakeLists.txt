cmake_minimum_required(VERSION 3.15...4.0)

project(MarvelousVM VERSION 0.1
                    DESCRIPTION "An educational JVM like VM"
                    LANGUAGES C)

include_directories(src)


file(GLOB VM_LIB_SRC "src/*" )
add_library(vmLib STATIC ${VM_LIB_SRC})

target_link_libraries(vmLib)

add_executable(MarvelousVM main.c)

target_link_libraries(MarvelousVM vmLib)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_definitions("-DSAM_PROJECT_DIR=\"${PROJECT_SOURCE_DIR}\"")

macro(sam_initialize)
    set(SAM_IDE_GROUP "")
    set(SAM_SOURCE_GROUP "")
    if(NOT CMAKE_TOOLCHAIN_FILE)
        if (MSVC)
            include(${PROJECT_SOURCE_DIR}/cmake/platform/windows.cmake)
        elseif (APPLE)
            include(${PROJECT_SOURCE_DIR}/cmake/platform/osx.cmake)
        elseif (MINGW)
            include(${PROJECT_SOURCE_DIR}/cmake/platform/mingw.cmake)
        else ()
            include(${PROJECT_SOURCE_DIR}/cmake/platform/linux.cmake)
        endif ()
    else()
        if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
            include(${PROJECT_SOURCE_DIR}/cmake/platform/android.cmake)
        endif()
    endif ()
endmacro()

macro(sam_set_ide_group name)
    set(SAM_IDE_GROUP ${name})
endmacro()

macro(sam_push_source_group name)
    set(SAM_SOURCE_GROUP "${SAM_SOURCE_GROUP}${name}\\")
endmacro()

macro(sam_pop_source_group)
    string(REGEX REPLACE "[^\\]+\\\\$" "" SAM_SOURCE_GROUP ${SAM_SOURCE_GROUP})
endmacro()

macro(sam_auto_group_source dir source)
    file(GLOB file_list "${dir}/*")
    foreach(file ${file_list})
        if(IS_DIRECTORY ${file})
            get_filename_component(dir_name ${file} NAME)
            sam_push_source_group(${dir_name})
            sam_auto_group_source(${file} ${source})
            sam_pop_source_group()
        else()
            if(SAM_SOURCE_GROUP)
                string(REGEX REPLACE "\\\\$" "" group ${SAM_SOURCE_GROUP})
                source_group(${group} FILES ${file})
            else()
                source_group("" FILES ${file})
            endif()
            set(${source} ${${source}} ${file})
        endif()
    endforeach()
endmacro()

macro(sam_add_module name source)
    add_library(${name} SHARED ${${source}})
    set_target_properties(${name} PROPERTIES FOLDER "${SAM_IDE_GROUP}")
    set_target_properties(${name} PROPERTIES PREFIX "")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build")
    target_link_libraries(${name} ${ARGN})
endmacro()

macro(sam_add_console_example name source)
    add_executable(${name} ${${source}})
    set_target_properties(${name} PROPERTIES FOLDER "${SAM_IDE_GROUP}")
    set_target_properties(${name} PROPERTIES PREFIX "")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build")
    target_link_libraries(${name} ${ARGN})
endmacro()

macro(sam_add_window_example name source)
    add_executable(${name} WIN32 ${${source}})
    set_target_properties(${name} PROPERTIES FOLDER "${SAM_IDE_GROUP}")
    set_target_properties(${name} PROPERTIES PREFIX "")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build")
    target_link_libraries(${name} ${ARGN})
endmacro()
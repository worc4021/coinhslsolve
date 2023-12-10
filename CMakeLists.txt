set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
cmake_minimum_required(VERSION 3.21)
project(coinhsl-linsolve LANGUAGES C CXX Fortran)

option(BUILD_TESTS "Build tests" ON)
set( "/build" CACHE STRING "Path to local install for libraries with pkgconfig directory")


# Set up pkg-config for custom installed packages
set(ENV{PKG_CONFIG_PATH} "${LOCAL_INSTALL_PREFIX}/lib/pkgconfig")
link_directories(${LOCAL_INSTALL_PREFIX}/lib)
# -----------------------------

find_package(PkgConfig REQUIRED)
pkg_search_module(COINHSL REQUIRED IMPORTED_TARGET coinhsl)

include(FortranCInterface)

# if you are working with C and Fortran
FortranCInterface_VERIFY()

# if you are working with C++ and Fortran
FortranCInterface_VERIFY(CXX)

FortranCInterface_HEADER(${CMAKE_CURRENT_SOURCE_DIR}/include/FCMangle.h
                         MACRO_NAMESPACE "FC_"
                         SYMBOL_NAMESPACE "FC_"
                         SYMBOLS 
                            ma27id 
                            ma27ad
                            ma27bd
                            ma27cd)

include(GNUInstallDirs)

add_library(${PROJECT_NAME} INTERFACE)

include(GNUInstallDirs)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(
    ${PROJECT_NAME}
    INTERFACE 
        cxx_std_20
)

install(
    TARGETS ${PROJECT_NAME} 
    EXPORT ${PROJECT_NAME}_Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include 
    DESTINATION include
)

install(
    EXPORT "${PROJECT_NAME}_Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    DESTINATION  ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
)


set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERFACE_LINK_LIBRARIES PkgConfig::COINHSL
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE ON
)

if (BUILD_TESTS)
    find_package(GTest CONFIG REQUIRED)
    include(CTest)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(test)
endif()
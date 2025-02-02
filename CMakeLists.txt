cmake_minimum_required(VERSION 3.15...3.26)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)


find_package(Python 3.9 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

if(NOT DEFINED MPI4PY_PREFIX)
  execute_process(
      COMMAND ${Python_EXECUTABLE} -m mpi4py --prefix
      OUTPUT_VARIABLE MPI4PY_PREFIX
      RESULT_VARIABLE MPI4PY_RESULT
      OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(NOT MPI4PY_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to find mpi4py!")
  endif()
  message(STATUS "Found mpi4py: ${MPI4PY_PREFIX}")
else()
  message(STATUS "Using user-defined mpi4py prefix: ${MPI4PY_PREFIX}")
endif()
set(MPI4PY_INCLUDE_DIR ${MPI4PY_PREFIX}/include)




pybind11_add_module(_core MODULE src/main.cpp)

target_include_directories(_core PRIVATE ${MPI4PY_INCLUDE_DIR})

install(TARGETS _core DESTINATION ${SKBUILD_PROJECT_NAME})

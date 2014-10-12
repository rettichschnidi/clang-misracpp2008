set(CLANG_MISRACPP2008_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CLANG_MISRACPP2008_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

#Enable target doxygen-misracpp2008 to build the doxygen documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOC_OUTPUT_PATH ${CMAKE_BINARY_DIR}/docs)

  configure_file(${CLANG_MISRACPP2008_SOURCE_DIR}/doc/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

  add_custom_target(doxygen-misracpp2008
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating clang-misracpp2008 doxygen documentation." VERBATIM)

  if(LLVM_ENABLE_DOXYGEN)
    add_dependencies(doxygen doxygen-misracpp2008)
  endif()
endif()

#Glob all sources files.
aux_source_directory(src/rules SRC_RULE_LIST)
aux_source_directory(src/ SRC_MAIN_LIST)

#Add our include directories
include_directories(
  src/
  src/rules/
  )

#When building with clang, warn about faulty Doxygen comments.
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdocumentation")
endif()

# Turn warnings into errors
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
else()
  message(FATAL_ERROR "Unknown (and therefore untested) compiler!")
endif()

#Register the source code files to the LLVM build system
set(SRC_LIST
  ${SRC_RULE_LIST}
  ${SRC_MAIN_LIST}
  )
add_llvm_loadable_module(misracpp2008 ${SRC_LIST})

#Add our tests directory
add_subdirectory(test)

cmake_minimum_required(VERSION 3.1)

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

add_llvm_loadable_module(misracpp2008
  src/misracpp2008.cpp
  src/misracpp2008.h
  src/RuleHeadlineTexts.cpp
  src/RuleHeadlineTexts.h
  src/rules/BannedFunctionUsageChecker.h
  src/rules/Rule_2_10_1.cpp
  src/rules/Rule_2_10_2.cpp
  src/rules/Rule_2_13_3.cpp
  src/rules/Rule_2_13_4.cpp
  src/rules/Rule_2_13_5.cpp
  src/rules/Rule_3_1_2.cpp
  src/rules/Rule_3_1_3.cpp
  src/rules/Rule_3_3_1.cpp
  src/rules/Rule_3_3_2.cpp
  src/rules/Rule_3_9_2.cpp
  src/rules/Rule_4_10_2.cpp
  src/rules/Rule_4_5_1.cpp
  src/rules/Rule_4_5_2.cpp
  src/rules/Rule_4_5_3.cpp
  src/rules/Rule_5_0_5.cpp
  src/rules/Rule_5_14_1.cpp
  src/rules/Rule_5_18_1.cpp
  src/rules/Rule_5_8_1.cpp
  src/rules/Rule_6_2_1.cpp
  src/rules/Rule_6_2_2.cpp
  src/rules/Rule_6_2_3.cpp
  src/rules/Rule_6_3_1.cpp
  src/rules/Rule_6_4_1.cpp
  src/rules/Rule_6_4_2.cpp
  src/rules/Rule_9_5_1.cpp
  src/rules/Rule_10_3_2.cpp
  src/rules/Rule_10_3_3.cpp
  src/rules/Rule_11_0_1.cpp
  src/rules/Rule_12_8_2.cpp
  src/rules/Rule_15_5_1.cpp
  src/rules/Rule_16_3_1.cpp
  src/rules/Rule_16_3_2.cpp
  src/rules/Rule_17_0_1.cpp
  src/rules/Rule_17_0_5.cpp
  src/rules/Rule_18_0_1.cpp
  src/rules/Rule_18_0_2.cpp
  src/rules/Rule_18_0_3.cpp
  src/rules/Rule_18_0_4.cpp
  src/rules/Rule_18_0_5.cpp
  src/rules/Rule_18_2_1.cpp
  src/rules/Rule_18_4_1.cpp
  src/rules/Rule_18_7_1.cpp
  src/rules/Rule_19_3_1.cpp
  src/rules/Rule_27_0_1.cpp
)
#Add our include directories
target_include_directories(misracpp2008 PRIVATE src/ src/rules/)

#Add our tests directory
add_subdirectory(test)

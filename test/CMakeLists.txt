# Script shamelessly stolen from the clang/test folder.
# Test runner infrastructure for clang-misracpp2008. This configures the Clang
# test trees for use by Lit, and delegates to LLVM's lit test handlers.

if(CMAKE_CFG_INTDIR STREQUAL ".")
  set(LLVM_BUILD_MODE ".")
else()
  set(LLVM_BUILD_MODE "%(build_mode)s")
endif()

string(REPLACE ${CMAKE_CFG_INTDIR} ${LLVM_BUILD_MODE} CLANG_MISRACPP2008_TOOLS_DIR ${LLVM_RUNTIME_OUTPUT_INTDIR})

configure_lit_site_cfg(
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.in
  ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
  )

option(CLANG_MISRACPP2008_TEST_USE_VG "Run Clang tests under Valgrind" OFF)
if(CLANG_MISRACPP2008_TEST_USE_VG)
  set(CLANG_MISRACPP2008_TEST_EXTRA_ARGS ${CLANG_MISRACPP2008_TEST_EXTRA_ARGS} "--vg")
endif()

list(APPEND CLANG_MISRACPP2008_TEST_DEPS
  clang clang-headers FileCheck
  misracpp2008
  )
set(CLANG_MISRACPP2008_TEST_PARAMS
  clang_site_config=${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
  )

add_lit_testsuite(check-misracpp2008 "Running the clang-misracpp2008 tests"
  ${CMAKE_CURRENT_BINARY_DIR}
  PARAMS ${CLANG_MISRACPP2008_TEST_PARAMS}
  DEPENDS ${CLANG_MISRACPP2008_TEST_DEPS}
  ARGS ${CLANG_MISRACPP2008_TEST_EXTRA_ARGS}
  )
set_target_properties(check-misracpp2008 PROPERTIES FOLDER "Clang MISRA C++ 2008 tests")

#Add dummy library to get Qt Creator to show the tests.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
file(GLOB_RECURSE SRC_TEST_LIST "*.cpp")
add_library(clangtest STATIC ${SRC_TEST_LIST})

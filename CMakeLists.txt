set(CLANG_MISRACPP2008_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CLANG_MISRACPP2008_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

#Glob all sources files.
aux_source_directory(src/rules SRC_RULE_LIST)
aux_source_directory(src/ SRC_MAIN_LIST)

include_directories(
    src/
    src/rules/
)

set(SRC_LIST
  ${SRC_RULE_LIST}
  ${SRC_MAIN_LIST})

add_llvm_loadable_module(misracpp2008 ${SRC_LIST})

add_subdirectory(test)

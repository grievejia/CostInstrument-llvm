set(TOOL_BIN_PATH ${CMAKE_BINARY_DIR}/tool/llvm-instr)
set(TOOL_LIB_PATH ${CMAKE_BINARY_DIR}/lib/Runtime)
configure_file(clang-instr.py.in 
  ${CMAKE_CURRENT_BINARY_DIR}/clang-instr.py
  @ONLY)

set(TOOL_BIN_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(TOOL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib)
configure_file(clang-instr.py.in 
  ${CMAKE_CURRENT_BINARY_DIR}/clang-instr.install.py
  @ONLY)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/clang-instr.install.py
    DESTINATION bin
    RENAME clang-instr)

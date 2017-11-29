set (llvmInstrSourceCode
  llvm-instr.cpp
)

add_executable (llvm-instr ${llvmInstrSourceCode})
target_link_libraries (llvm-instr InstrumentStatic)

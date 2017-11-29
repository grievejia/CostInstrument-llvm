set (llvmInstrSourceCode
  LLVMUtil.cpp
  llvm-instr.cpp
)

add_executable (llvm-instr ${llvmInstrSourceCode})
target_link_libraries (llvm-instr InstrumentStatic LLVMBinaryFormat LLVMIRReader LLVMBitWriter)

install(TARGETS llvm-instr
  RUNTIME DESTINATION bin)

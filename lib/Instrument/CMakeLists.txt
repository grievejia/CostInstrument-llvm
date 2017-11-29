set (InstrumentSourceCodes
  DynamicHooks.cpp
  InstrumentPass.cpp
  NameBlacklist.cpp
)
add_library(InstrumentObj OBJECT ${InstrumentSourceCodes})
set_property(TARGET ${InstrumentObj} PROPERTY POSITION_INDEPENDENT_CODE 1)

# The shared library is for testing purpose only
add_library(InstrumentShared SHARED $<TARGET_OBJECTS:InstrumentObj>)
target_link_libraries(InstrumentShared LLVM)

add_library(InstrumentStatic STATIC $<TARGET_OBJECTS:InstrumentObj>)
target_link_libraries(InstrumentStatic LLVMCore LLVMAnalysis)

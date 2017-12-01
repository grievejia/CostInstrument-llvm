set (InstrumentSourceCodes
  DynamicHooks.cpp
  InstrumentPass.cpp
  NameBlacklist.cpp
)
add_library(InstrumentObj OBJECT ${InstrumentSourceCodes})

# The shared library is for testing purpose only
# set_property(TARGET ${InstrumentObj} PROPERTY POSITION_INDEPENDENT_CODE 1)
# add_library(InstrumentShared SHARED $<TARGET_OBJECTS:InstrumentObj>)
# target_link_libraries(InstrumentShared LLVM)

add_library(InstrumentStatic STATIC $<TARGET_OBJECTS:InstrumentObj>)
target_link_libraries(InstrumentStatic LLVMCore LLVMAnalysis LLVMPasses)

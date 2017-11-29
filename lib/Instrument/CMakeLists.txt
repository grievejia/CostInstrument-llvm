set (InstrumentSourceCodes
  DynamicHooks.cpp
  InstrumentPass.cpp
)
add_library(InstrumentObj OBJECT ${InstrumentSourceCodes})
set_property(TARGET ${InstrumentObj} PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(InstrumentShared SHARED $<TARGET_OBJECTS:InstrumentObj>)
add_library(InstrumentStatic STATIC $<TARGET_OBJECTS:InstrumentObj>)
target_link_libraries(InstrumentStatic LLVMCore)
target_link_libraries(InstrumentShared LLVM)

set (RuntimeSourceCodes
  Hooks.c
)

add_library (CostInstrRuntime STATIC ${RuntimeSourceCodes})

install(TARGETS CostInstrRuntime
    ARCHIVE DESTINATION lib)

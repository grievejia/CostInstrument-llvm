#pragma once

#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

namespace llvm {
class Function;
class Module;
class AnalysisUsage;
class TargetLibraryInfo;
} // namespace llvm

namespace costinstr {

class DynamicHooks;

class InstrumentPass : public llvm::ModulePass {

  bool instrumentFunction(llvm::Function&, const DynamicHooks&);

public:
  static char ID;

  InstrumentPass();

  bool runOnModule(llvm::Module&) override;
  void getAnalysisUsage(llvm::AnalysisUsage&) const override;
};

} // namespace costinstr

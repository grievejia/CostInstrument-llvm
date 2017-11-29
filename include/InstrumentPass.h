#pragma once

#include "NameBlacklist.h"
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>

namespace llvm {
class Function;
class Module;
class AnalysisUsage;
class TargetLibraryInfo;
} // namespace llvm

namespace costinstr {

class DynamicHooks;

class InstrumentPass : public llvm::ModulePass {

  NameBlacklist blacklist;

  bool instrumentFunction(llvm::Function&, const DynamicHooks&);

public:
  static char ID;

  InstrumentPass();
  InstrumentPass(NameBlacklist);

  bool runOnModule(llvm::Module&) override;
  void getAnalysisUsage(llvm::AnalysisUsage&) const override;
};

} // namespace costinstr

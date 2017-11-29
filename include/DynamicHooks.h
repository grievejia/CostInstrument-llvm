#pragma once

namespace llvm {
class Function;
class Module;
class Type;
} // namespace llvm

namespace costinstr {
class DynamicHooks {
  llvm::Function* costIncHook;
  llvm::Function* costShutdownHook;
  llvm::Function* atExit;

public:
  DynamicHooks(llvm::Module&);

  llvm::Function* getCostIncHook() const;
  llvm::Function* getCostShutdownHook() const;
  llvm::Function* getAtExit() const;
  bool isHook(const llvm::Function&) const;
};

} // namespace costinstr

#include "InstrumentPass.h"
#include "DynamicHooks.h"
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>

using namespace llvm;

namespace costinstr {

namespace {

void instrumentFunctionEntry(Function& func, const DynamicHooks& hooks) {
  auto& entryBlock = func.getEntryBlock();
  auto entryInst = &*entryBlock.getFirstInsertionPt();
  auto incInst = CallInst::Create(hooks.getCostIncHook(), "", entryInst);

  if (func.getName() == "main") {
    CallInst::Create(hooks.getAtExit(), {hooks.getCostShutdownHook()}, "",
                     incInst);
  }
}

void instrumentLoopHeader(LoopInfo& loopInfo, const DynamicHooks& hooks) {
  for (auto loop : loopInfo.getLoopsInPreorder()) {
    auto headerBlock = loop->getHeader();
    auto headerEntry = &*headerBlock->getFirstInsertionPt();
    CallInst::Create(hooks.getCostIncHook(), "", headerEntry);
  }
}

} // namespace

InstrumentPass::InstrumentPass() : InstrumentPass(NameBlacklist()) {}
InstrumentPass::InstrumentPass(NameBlacklist blacklist)
    : ModulePass(ID), blacklist(blacklist) {}

void InstrumentPass::getAnalysisUsage(AnalysisUsage& usage) const {
  usage.addRequired<LoopInfoWrapperPass>();
}

bool InstrumentPass::instrumentFunction(Function& func,
                                        const DynamicHooks& hooks) {
  if (func.isDeclaration())
    return false;
  if (hooks.isHook(func))
    return false;
  if (blacklist.isBlacklisted(func.getName()))
    return false;

  instrumentFunctionEntry(func, hooks);

  auto& loopInfoPass = getAnalysis<LoopInfoWrapperPass>(func);
  instrumentLoopHeader(loopInfoPass.getLoopInfo(), hooks);

  return true;
}

bool InstrumentPass::runOnModule(Module& module) {
  DynamicHooks hooks(module);

  bool ret = false;
  for (auto& f : module) {
    ret |= instrumentFunction(f, hooks);
  }
  return ret;
}

char InstrumentPass::ID = 0;
} // namespace costinstr

static RegisterPass<costinstr::InstrumentPass> X("costinstr",
                                                 "Cost instrumentation pass",
                                                 false /* Only looks at CFG */,
                                                 false /* Analysis Pass */);

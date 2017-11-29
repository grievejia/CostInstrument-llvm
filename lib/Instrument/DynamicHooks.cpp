#include "DynamicHooks.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

using namespace llvm;

namespace {

Type* getVoidType(const Module& m) {
  return Type::getVoidTy(m.getContext());
}

Type* getCharType(const Module& m) {
  return Type::getInt8Ty(m.getContext());
}

Type* getIntType(const Module& m) {
  return Type::getIntNTy(m.getContext(), sizeof(int) * 8);
}

Type* getCharPtrType(const Module& m) {
  return PointerType::getUnqual(getCharType(m));
}

Type* getCharPtrPtrType(const Module& m) {
  return PointerType::getUnqual(getCharPtrType(m));
}

Function* createFunctionWithArgType(const StringRef& name,
                                    ArrayRef<Type*> argTypes, Module& module) {
  auto funType =
      FunctionType::get(getVoidType(module), std::move(argTypes), false);
  return Function::Create(funType, GlobalValue::ExternalLinkage, name, &module);
}

Function* createFunctionWithArgRetType(const StringRef& name,
                                       ArrayRef<Type*> argTypes, Type* retType,
                                       Module& module) {
  auto funType = FunctionType::get(retType, std::move(argTypes), false);
  return Function::Create(funType, GlobalValue::ExternalLinkage, name, &module);
}

} // namespace

namespace costinstr {

DynamicHooks::DynamicHooks(Module& module) {
  costIncHook = createFunctionWithArgType("cost_inc", {}, module);
  costShutdownHook = createFunctionWithArgType("exit_print_hook", {}, module);
  atExit = createFunctionWithArgRetType("atexit", {costShutdownHook->getType()},
                                        getIntType(module), module);
}

Function* DynamicHooks::getCostIncHook() const {
  return costIncHook;
}

Function* DynamicHooks::getCostShutdownHook() const {
  return costShutdownHook;
}

Function* DynamicHooks::getAtExit() const {
  return atExit;
}

bool DynamicHooks::isHook(const Function& f) const {
  return &f == costIncHook || &f == costShutdownHook;
}

} // namespace costinstr

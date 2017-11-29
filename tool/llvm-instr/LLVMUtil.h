#pragma once

#include <llvm/ADT/StringRef.h>
#include <llvm/IR/Module.h>

#include <memory>

std::unique_ptr<llvm::Module> readModuleFromFile(llvm::LLVMContext& context,
                                                 llvm::StringRef fileName);

void writeModuleToText(const llvm::Module&, llvm::StringRef fileName);
void writeModuleToBitCode(const llvm::Module&, llvm::StringRef fileName);
void writeModuleToFile(const llvm::Module&, llvm::StringRef fileName,
                       bool isText);

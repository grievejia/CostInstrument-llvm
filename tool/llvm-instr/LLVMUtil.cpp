#include "LLVMUtil.h"
#include <llvm/Bitcode/BitcodeWriterPass.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ToolOutputFile.h>

using namespace llvm;

std::unique_ptr<Module> readModuleFromFile(LLVMContext& context,
                                           StringRef fileName) {
  SMDiagnostic err;
  return parseIRFile(fileName, err, context);
}

void writeModuleToText(const llvm::Module& module, StringRef fileName) {
  std::error_code ec;
  tool_output_file out(fileName, ec, sys::fs::F_None);
  if (ec) {
    errs() << ec.message() << "\n";
    std::exit(-3);
  }

  module.print(out.os(), nullptr);

  out.keep();
}

void writeModuleToBitCode(const Module& module, StringRef fileName) {
  std::error_code ec;
  tool_output_file out(fileName, ec, sys::fs::F_None);
  if (ec) {
    errs() << ec.message() << "\n";
    std::exit(-3);
  }

  createBitcodeWriterPass(out.os())->runOnModule(const_cast<Module&>(module));

  out.keep();
}

void writeModuleToFile(const Module& module, StringRef fileName, bool isText) {
  if (isText)
    writeModuleToText(module, fileName);
  else
    writeModuleToBitCode(module, fileName);
}

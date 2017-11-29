#include "InstrumentPass.h"
#include "LLVMUtil.h"
#include "thirdparty/ProgramOptions.hxx"
#include <llvm/ADT/SmallVector.h>
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/Analysis/TargetLibraryInfo.h>
#include <llvm/IR/LegacyPassManager.h>
#include <string>

using namespace llvm;
using namespace costinstr;

void runPasses(Module& module, NameBlacklist blacklist) {
  PassRegistry& Registry = *PassRegistry::getPassRegistry();
  initializeCore(Registry);

  legacy::PassManager passes;
  passes.add(
      new TargetLibraryInfoWrapperPass(Triple(module.getTargetTriple())));
  passes.add(new LoopInfoWrapperPass());
  passes.add(new InstrumentPass(std::move(blacklist)));
  passes.run(module);
}

int main(int argc, char** argv) {
  po::parser parser;
  parser["help"]
      .abbreviation('h')
      .description("print this help screen")
      .callback([&] { std::cout << parser << '\n'; });
  auto&& outputFile = parser["output"]
                          .abbreviation('o')
                          .description("output file name. Default to stdout")
                          .type(po::string)
                          .fallback("-");
  auto&& blacklistOption =
      parser["blacklist"]
          .abbreviation('b')
          .description("Avoid instrumenting any functions whose name matches "
                       "the specified patterns. Patterns are separated by "
                       "commas.")
          .type(po::string);
  auto&& textOption = parser["text"].abbreviation('S').description(
      "serialize to .ll instead of .bc");
  auto&& inputFileOption = parser[""].description("input file name");

  if (!parser(argc, argv)) {
    std::cerr << "Cli option parsing error:" << parser << '\n';
    return 1;
  }

  auto inputFiles = inputFileOption.to_vector<po::string>();
  if (inputFiles.empty()) {
    std::cerr << "[ERROR] Missing input file\n";
    return 1;
  } else if (inputFiles.size() > 1) {
    std::cerr << "[ERROR] Only one input file is accepted\n";
    return 1;
  }

  auto inputFileName = inputFiles[0];
  auto outputFileName = outputFile.get().string;
  auto blacklistPatternString =
      blacklistOption.was_set() ? blacklistOption.get().string : "";
  SmallVector<StringRef, 4> blacklistVector;
  StringRef(blacklistPatternString).split(blacklistVector, -1, false);
  NameBlacklist blacklist(blacklistVector);
  auto isText = textOption.was_set();

  LLVMContext context;
  auto module = readModuleFromFile(context, inputFileName);
  runPasses(*module, std::move(blacklist));
  writeModuleToFile(*module, outputFileName, isText);
}

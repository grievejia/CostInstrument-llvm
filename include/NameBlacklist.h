#pragma once

#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <regex>
#include <vector>

namespace costinstr {

class NameBlacklist {
  using StringList = std::vector<std::string>;
  using RegexList = std::vector<std::regex>;
  RegexList patterns;

public:
  NameBlacklist() = default;
  NameBlacklist(StringList);
  NameBlacklist(const llvm::SmallVectorImpl<llvm::StringRef>&);

  bool isBlacklisted(const std::string&) const;
  bool isBlacklisted(llvm::StringRef) const;
};

} // namespace costinstr

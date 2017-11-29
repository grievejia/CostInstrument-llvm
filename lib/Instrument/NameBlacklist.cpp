#include "NameBlacklist.h"
#include <algorithm>

using namespace llvm;

namespace costinstr {

NameBlacklist::NameBlacklist(StringList strs) {
  for (auto const& str : strs) {
    patterns.emplace_back(str);
  }
}
NameBlacklist::NameBlacklist(const SmallVectorImpl<StringRef>& strRefs) {
  for (auto const& strRef : strRefs) {
    patterns.emplace_back(strRef.str());
  }
}

bool NameBlacklist::isBlacklisted(const std::string& name) const {
  return isBlacklisted(llvm::StringRef(name));
}

bool NameBlacklist::isBlacklisted(llvm::StringRef name) const {
  return std::any_of(patterns.begin(), patterns.end(), [name](auto& pattern) {
    return std::regex_match(name.str(), pattern,
                            std::regex_constants::match_continuous);
  });
}
} // namespace costinstr

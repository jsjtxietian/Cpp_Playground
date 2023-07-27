#include <format>
#include <source_location>
#include <iostream>

template <typename... Args>
struct SrcProxy {
  template<typename T>
  consteval SrcProxy(const T& formatter, std::source_location sl = std::source_location::current())
      : formatter{std::format_string<Args...>{formatter}}, sl{sl} {}
  std::format_string<Args...> formatter;
  std::source_location sl;
};

template <typename... Args>
void LogDebug(SrcProxy<std::type_identity_t<Args>...> proxy, Args&&... args) {
  std::cout << std::format("line: {} {} ", proxy.sl.line(), proxy.sl.file_name());
  std::cout << std::format(proxy.formatter, std::forward<Args>(args)...);
}

int main() {
  LogDebug("{}", "Hello!");
}
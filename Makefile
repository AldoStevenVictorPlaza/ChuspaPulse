.PHONY: all build clean test

all: build

build:
	@mkdir -p src/core
	@printf '#ifndef CORE_VERSION_HPP\n#define CORE_VERSION_HPP\n\n#include <string>\n\nnamespace pulso {\n    const std::string APP_VERSION = "0.1.0";\n}\n\n#endif\n' > src/core/version.hpp
	@cmake -B build -S .
	@cmake --build build
clean:
	@rm -rf build

test: build
	@ctest --test-dir build --output-on-failure
.PHONY: all build clean test

all: build

build:
	@python3 -c "import os; os.makedirs('src/core', exist_ok=True); open('src/core/version.hpp', 'a').close()"
	@if [ ! -s src/core/version.hpp ]; then echo '#ifndef CORE_VERSION_HPP\n#define CORE_VERSION_HPP\n\n#include <string>\n\nnamespace pulso {\n    const std::string APP_VERSION = "0.1.0";\n}\n\n#endif' > src/core/version.hpp; fi
	@cmake -B build -S .
	@cmake --build build

clean:
	@rm -rf build

test: build
	@ctest --test-dir build --output-on-failure
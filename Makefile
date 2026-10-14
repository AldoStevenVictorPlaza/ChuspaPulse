.PHONY: all build clean test

all: build

build:
	@mkdir -p src/core
	@if [ ! -f src/core/version.hpp ]; then \
		echo '#ifndef CORE_VERSION_HPP' > src/core/version.hpp; \
		echo '#define CORE_VERSION_HPP' >> src/core/version.hpp; \
		echo '#include <string>' >> src/core/version.hpp; \
		echo 'namespace pulso { const std::string APP_VERSION = "0.1.0"; }' >> src/core/version.hpp; \
		echo '#endif' >> src/core/version.hpp; \
	fi
	@cmake -B build -S .
	@cmake --build build

clean:
	@rm -rf build

test: build
	@ctest --test-dir build --output-on-failure
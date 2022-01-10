.DEFAULT_GOAL := debug

debug:
	cd cmake-build-debug && cmake .. && cmake --build .

install:
	git submodule init
	git submodule update
	mkdir cmake-build-debug
	cd cmake-build-debug && cmake .. && cmake --build .

modules:
	git submodule add https://github.com/Falldot/Corsac_STL.git ./packages/Corsac_STL
	git submodule add https://github.com/Falldot/Corsac_ECS.git ./packages/Corsac_ECS
	git submodule add https://github.com/Lirik-Keltran/Corsac-Test.git ./packages/Corsac_Test
	git submodule add https://github.com/Lirik-Keltran/Corsac-Benchmark.git ./packages/Corsac_Benchmark

update:
	git submodule update --remote --merge

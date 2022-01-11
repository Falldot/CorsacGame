.DEFAULT_GOAL := debug

debug:
	cd cmake-build-debug && cmake .. -G "MinGW Makefiles" && cmake --build . & Game.exe

install:
	git submodule init
	git submodule update
	mkdir cmake-build-debug
	cd cmake-build-debug && cmake . -G "MinGW Makefiles". && cmake --build .

modules:
	git submodule add https://github.com/Falldot/Corsac_STL.git ./packages/Corsac_STL
	git submodule add https://github.com/Falldot/Corsac_ECS.git ./packages/Corsac_ECS
	git submodule add https://github.com/Lirik-Keltran/Corsac-Test.git ./packages/Corsac_Test
	git submodule add https://github.com/Lirik-Keltran/Corsac-Benchmark.git ./packages/Corsac_Benchmark
	git submodule add https://github.com/libsdl-org/SDL.git ./packages/SDL

update:
	git submodule update --remote --merge

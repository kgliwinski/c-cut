# CUT - cpu usage tracker

Directory structure:
```bash
├── c-cut_logs.txt
├── CMakeLists.txt
├── include
│   ├── color.h
│   ├── cpuAnalyzer.h
│   ├── cutThreads.h
│   ├── logMacro.h
│   ├── logQueue.h
│   ├── msTimer.h
│   ├── sigtermHandler.h
│   ├── statStruct.h
│   ├── statStructQueue.h
│   └── watchdogTimer.h
├── LICENSE
├── main.c
├── README.md
├── source
│   ├── cpuAnalyzer.c
│   ├── logQueue.c
│   ├── msTimer.c
│   ├── statStruct.c
│   ├── statStructQueue.c
│   ├── threads
│   │   ├── analyzerThread.c
│   │   ├── loggerThread.c
│   │   ├── printerThread.c
│   │   ├── readerThread.c
│   │   └── watchdogThread.c
│   └── watchdogTimer.c
└── tests
    ├── cpuAnalyzerTest.c
    ├── logQueueTest.c
    ├── msTimerTest.c
    ├── readerTest.c
    └── statStructQueueTest.c
```

## Building and executing c-cut

CMake required (at least version 3.14.2)

From main project directory `/c-cut` run:
```bash
mkdir build && cdbuild
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./c-cut
```

To terminate the program type the `Ctrl+c` for the SIGINT signal

### Building with specified compilator

Add `-DCMAKE_CXX_COMPILER=/usr/bin/clang` flag to `cmake ..` command

## Using ctest

To run automatic tests stored in the `/tests` directory run `ctest` after building the program with `make`

## Valgrind tests

For (semi) automatic valgrind test run 
```bash
timeout -s INT 15s valgrind --leak-check=full ./c-cut
```
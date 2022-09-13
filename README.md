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
    └── readerTest.c
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

Manual tests give this kind of result locally:
```bash
~/c-cut/build$ timeout -s INT 15s valgrind --leak-check=full ./c-cut
==18535== Memcheck, a memory error detector
==18535== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==18535== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==18535== Command: ./c-cut
==18535== 
CPU      |CPU 0    |CPU 1    |CPU 2    |CPU 3    |CPU 4    |CPU 5    |CPU 6    |CPU 7    |
   11.00%|   11.92%|    8.95%|    6.73%|    7.84%|    6.55%|   13.49%|   15.43%|   13.73%|User signal 2
Program exit
==18535== 
==18535== HEAP SUMMARY:
==18535==     in use at exit: 0 bytes in 0 blocks
==18535==   total heap usage: 379 allocs, 379 frees, 246,669 bytes allocated
==18535== 
==18535== All heap blocks were freed -- no leaks are possible
==18535== 
==18535== For lists of detected and suppressed errors, rerun with: -s
==18535== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
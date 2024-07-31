To compile the program
    1.1 cd build
    1.2 run the command 
        cmake .. 
        make 
    1.3 the binary(shell) is generated in bin folder
    1.4 Output of all test cases can be found in output.txt


    ******************************************************************************
     Sample run
    ******************************************************************************

vivek@vivek:~/matic/shell$ cd build
vivek@vivek:~/matic/shell/build$ cmake ..
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/vivek/matic/shell/build

vivek@vivek:~/matic/shell/build$ make
Scanning dependencies of target shell
[ 33%] Building CXX object src/CMakeFiles/shell.dir/main.cpp.o
[ 66%] Building CXX object src/CMakeFiles/shell.dir/Shell.cpp.o
[100%] Linking CXX executable ../../bin/shell
[100%] Built target shell

vivek@vivek:~/matic/shell/build$ ../bin/shell 
[2024-04-20 21:34:14] [INFO] Starting shell...
$
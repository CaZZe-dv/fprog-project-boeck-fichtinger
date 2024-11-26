#!/bin/bash

# Set up paths for your project
SOURCE_DIR="."
EXECUTABLE_MAIN="main_program"
EXECUTABLE_TEST="test_program"

# Compile the main program in the current folder
echo "Compiling main program..."
g++ -std=c++17 "$SOURCE_DIR"/main.cpp -o "$SOURCE_DIR"/"$EXECUTABLE_MAIN"

# Check if compilation of main program was successful
if [ $? -ne 0 ]; then
    echo "Main program compilation failed."
    exit 1
fi

# List files in the current directory to check if the main executable was created
echo "Listing files in the current directory after main compilation..."
ls -l "$SOURCE_DIR"

# Compile the test program in the current folder
echo "Compiling test program..."
g++ -std=c++17 "$SOURCE_DIR"/test.cpp -o "$SOURCE_DIR"/"$EXECUTABLE_TEST"

# Check if compilation of test program was successful
if [ $? -ne 0 ]; then
    echo "Test program compilation failed."
    exit 1
fi

# List files in the current directory to check if the test executable was created
echo "Listing files in the current directory after test compilation..."
ls -l "$SOURCE_DIR"

# Run the compiled main program
echo "Running the main program..."
"./$EXECUTABLE_MAIN"

# Check if the main program ran successfully
if [ $? -ne 0 ]; then
    echo "Main program execution failed."
    exit 1
fi

# Run the compiled test program
echo "Running the test program..."
"./$EXECUTABLE_TEST"

# Check if the test program ran successfully
if [ $? -ne 0 ]; then
    echo "Test program execution failed."
    exit 1
fi

echo "Test run completed successfully."

if [ ! -d "build" ]; then
    echo "Creating a build directory..."
    mkdir build
fi

cd build

echo "Running CMake..."
cmake ..

if [ $? -ne 0 ]; then
    echo "CMake runtime error. Finish."
    exit 1
fi

echo "Build project..."
cmake --build .

if [ $? -eq 0 ]; then
    echo "Project successfuly builded!"
else
    echo "Building error."
    exit 1
fi
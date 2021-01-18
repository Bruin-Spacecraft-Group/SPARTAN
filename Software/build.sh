FILE=./_build/main/spartan
if [ -f "$FILE" ]; then
    rm -rf $FILE
fi
cmake -B _build
cd _build
cmake --build .
./main/spartan

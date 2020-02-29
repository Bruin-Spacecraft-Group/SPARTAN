FILE=./_build/main/flight_software
if [ -f "$FILE" ]; then
    rm -rf $FILE
fi
cmake -B _build
cd _build
cmake --build .
./main/flight_software

#!/usr/bin/sh
flags='-Wall -Wextra -fsanitize=undefined -g3'
name="$1"
echo "\033[1;32mINFO:\033[0m WorkDir: \033[35m$(pwd)\033[0m"
if [ $# -eq 0 ]; then
    echo "\033[1;31mERR:\033[0m Please Enter File!"
elif [ ! -e "$name.cpp" ]; then
    echo "\033[1;31mERR:\033[0m No that File \033[35m$name.cpp\033[0m"
else
    if [ ! -e ".$name.bak" ] || [ -n "$(diff -q ".$name.bak" "$name.cpp")" ]; then
        echo "\033[1;32mINFO:\033[0m Compile & Run \033[35m$name.cpp\033[0m"
        g++ $flags "$name.cpp" -o "$name.run"
        if [ $? -eq 0 ]; then 
            cp "$name.cpp" ".$name.bak"
            echo "================= begin =================" && time -p ./"$name.run"
        fi
    else
        echo "\033[1;32mINFO: \033[0;35m$name.cpp\033[0m is up to date"
        echo "================= begin =================" && time -p ./"$name.run"
    fi    
fi

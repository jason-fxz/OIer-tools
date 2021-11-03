#!/usr/bin/bash
logs () {
    builtin echo -e $* >&2
}
info () {
    logs "\033[1;32mINFO:\033[0m $1"
}
err() {
    logs "\033[1;31mERR:\033[0m $1"
}
warn() {
    logs "\033[1;33mWARN:\033[0m $1"
}
run_code() {
    logs "================= begin ================="
    time -p "./$1"
}

debug_flags='-Wall -Wextra -Wshadow -fsanitize=undefined -g3'
O2_flags='-Wall -Wextra -O2'
O3_flags='-Wall -Wextra -O3'
Ofast_flags='-Wall -Wextra -Ofast'
flags=""
name="$1"
info "WorkDir: \033[35m$(pwd)\033[0m"
case $2 in
    debug|Debug|DEBUG|D|d|"")
        info "With debug flags '$debug_flags'"
        flags="$debug_flags"
        ;;
    O2|o2)
        info "With O2 flags '$O2_flags'"
        flags="$O2_flags"
        ;;
    O3|o3)
        info "With O3 flags '$O3_flags'"
        flags="$O3_flags"
        ;;
    Ofast|Of|ofast)
        info "With Ofast flags '$Ofast_flags'"
        flags="$Ofast_flags"
        ;;
    empty|e|E)
        info "With no flags"
        flags=""
        ;;
    *)
        warn "No that flags! Run without flags."
        ;;
esac

if [ $# -eq 0 ]; then
    err "Please Enter File!"
elif [ ! -e "$name.cpp" ]; then
    err "No that File \033[35m'$name.cpp'\033[0m"
else
    cp "$name.cpp" ".$name.cpp.tmp"
    echo -e "\n// $flags" >> ".$name.cpp.tmp"
    if [ ! -e ".$name.cpp.bak" ] || [ -n "$(diff -q ".$name.cpp.bak" ".$name.cpp.tmp")" ]; then
        info "Compile & Run \033[35m'$name.cpp'\033[0m"
        g++ $flags "$name.cpp" -o "$name.run"
        if [ $? -eq 0 ]; then 
            cp ".$name.cpp.tmp" ".$name.cpp.bak"
            run_code "$name.run"
        fi
    else
        info "\033[35m'$name.cpp'\033[0m is up to date"
        run_code "$name.run"
    fi    
fi

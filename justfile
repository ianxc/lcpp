#!/usr/bin/env just --justfile

set positional-arguments

default:
    @just build-inc
    @just test a

# Build the project
build *args:
    @just conf
    @cmake --build build {{args}}

alias b := build

build-inc *args:
    @cmake --build build {{args}}

alias i := build-inc

conf:
    @mkdir -p build
    @cmake -B build -S .

clean:
    @cmake --build build -t clean

clean-all:
    rm -r build

add p_num p_name:
    #!/usr/bin/env bash
    set -e # exit on error
    set -C # noclobber

    P_NUM="{{p_num}}"
    P_NAME="{{p_name}}"

    if [[ "${P_NAME: -1}" == "/" ]]; then
        echo "<problem-name> should not end with /"
        exit 1
    fi

    P_NAME_FMT=$(echo "$P_NAME" | tr ' ' '-')
    P_ID="${P_NUM}-${P_NAME_FMT}"

    P_SRC_DIR="src/${P_ID}"
    P_TEST_DIR="test/${P_ID}"

    mkdir -p P_SRC_DIR
    mkdir -p P_TEST_DIR

    T_SRC_DIR="src/0-Template"
    T_TEST_DIR="test/0-Template"

    cp -an "${T_SRC_DIR}"/ "${P_SRC_DIR}"
    cp -an "${T_TEST_DIR}"/ "${P_TEST_DIR}"

# Run a specific executable with fzf selector if no target is provided
run target="__def__" *args:
    #!/usr/bin/env bash
    if [ "{{target}}" = "__def__" ]; then
        TARGET=$(ls -1 build/bin | fzf --height 40% --reverse --prompt="Select run target: ")
        if [ -n "$TARGET" ]; then
            build/bin/$TARGET {{args}}
        fi
    else
        build/bin/{{target}} {{args}}
    fi

# Run a specific test with fzf selector if no target is provided
test target="__def__" *args:
    #!/usr/bin/env bash
    if [ "{{target}}" = "__def__" ]; then
        # Get all test names
        TEST_LIST=$(ctest --test-dir build -N | grep "Test #" | sed 's/.*: //')

        # Generate test options including all possible test group patterns
        {
            # Full test names
            echo "$TEST_LIST"

            # Generate all possible prefixes for grouping (up to 10 levels deep)
            echo "$TEST_LIST" | while read -r line; do
                # Start with the full line
                current="$line"

                # Generate all possible prefixes by removing parts from the end
                for ((i=1; i<=10; i++)); do
                    # If we've already reduced to the first segment, stop
                    if [[ ! "$current" == *.* ]]; then
                        break
                    fi

                    # Remove the last segment
                    current="${current%.*}"
                    echo "$current"
                done
            done
        } | sort | uniq | fzf --height 40% --reverse --prompt="Select test pattern: " > /tmp/test_selection

        TARGET=$(cat /tmp/test_selection)
        if [ -n "$TARGET" ]; then
            echo "Running tests matching pattern: $TARGET"
            ctest --test-dir build -R "$TARGET" -V
        fi
        rm -f /tmp/test_selection
    elif [ "{{target}}" = "." ]; then
        ctest --test-dir build "{{args}}" -V
    else
        ctest --test-dir build -R {{target}} "{{args}}" -V
    fi

alias t := test

test-all:
    @just test .

alias tt := test-all

list-tests:
    @ctest --test-dir build -N | grep "Test #" | sed 's/.*: //'

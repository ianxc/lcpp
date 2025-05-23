#!/usr/bin/env just --justfile

set ignore-comments
set positional-arguments

# export CTEST_PARALLEL_LEVEL := env_var_or_default("CTEST_PARALLEL_LEVEL", "10")

default:
    @just build-inc
    # @just test-all

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

add p_num p_name: && conf
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
    # P_TEST_DIR="test/${P_ID}"

    T_SRC_DIR="src/0-Template"
    # T_TEST_DIR="test/0-Template"

    mkdir -p "${P_SRC_DIR}"
    # mkdir -p "${P_TEST_DIR}"

    echo "Added ${P_ID}"
    cp -an "${T_SRC_DIR}"/* "${P_SRC_DIR}"/
    # cp -an "${T_TEST_DIR}"/* "${P_TEST_DIR}"/

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
    DEFAULT_FLAGS="--output-on-failure"
    # DEFAULT_FLAGS="-V"
    if [ "{{target}}" = "__def__" ]; then
        # Get all test names
        TEST_LIST=$(ctest --test-dir build -N | grep -E "Test +#" | sed 's/.*: //')

        # Generate test options including all possible test group patterns
        {
            # Full test names
            echo "$TEST_LIST"

            # Generate all possible prefixes for grouping (up to 5 levels deep)
            echo "$TEST_LIST" | while read -r line; do
                # Start with the full line
                current="$line"

                # Generate all possible prefixes by removing parts from the end
                for ((i=1; i<=5; i++)); do
                    # If we've already reduced to the first segment, stop
                    if [[ ! "$current" == *.* ]]; then
                        break
                    fi

                    # Remove the last segment
                    current="${current%.*}"
                    echo "$current"
                done
            done
        } \
        | sort -V -u \
        | fzf --reverse --height 40% --no-sort --prompt="Select test pattern: " > /tmp/test_selection

        TARGET=$(cat /tmp/test_selection)
        if [ -n "$TARGET" ]; then
            echo "Running tests matching pattern: $TARGET"
            ctest --test-dir build -R "$TARGET" "$DEFAULT_FLAGS"
        fi
        rm -f /tmp/test_selection
    elif [ "{{target}}" = "." ]; then
        export CTEST_PARALLEL_LEVEL=10
        ctest --test-dir build "{{args}}" "$DEFAULT_FLAGS"
    else
        ctest --test-dir build -R {{target}} "{{args}}" "$DEFAULT_FLAGS"
    fi

alias t := test

test-all:
    @just test .

alias tt := test-all

list-tests:
    @ctest --test-dir build -N | grep "Test #" | sed 's/.*: //'

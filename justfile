#!/usr/bin/env just --justfile

# Build the project
build *args:
    @cmake --build build {{args}}

# Run a specific executable with fzf selector if no target is provided
run target="__def__" *args:
    #!/usr/bin/env zsh
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
    else
        ctest --test-dir build -R {{target}} "{{args}}" -V
    fi

# List available tests
tests:
    @ctest --test-dir build -N | grep "Test #" | sed 's/.*: //'

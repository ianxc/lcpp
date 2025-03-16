#!/usr/bin/env just --justfile

# Run a specific executable with fzf selector if no target is provided
run *ARGS:
    #!/usr/bin/env zsh
    if [ -z "{{ARGS}}" ]; then
        TARGET=$(ls -1 build/bin | fzf --height 40% --reverse --prompt="Select executable: ")
        if [ -n "$TARGET" ]; then
            build/bin/$TARGET
        fi
    else
        build/bin/{{ARGS}}
    fi

# Run a specific test with fzf selector if no target is provided
test *ARGS:
    #!/usr/bin/env zsh
    if [ -z "{{ARGS}}" ]; then
        TARGET=$(ctest --test-dir build -N | grep "Test #" | sed 's/.*: //' | fzf --height 40% --reverse --prompt="Select test: ")
        if [ -n "$TARGET" ]; then
            ctest --test-dir build -R "$TARGET" -V
        fi
    else
        ctest --test-dir build -R "{{ARGS}}" -V
    fi

# List available tests
tests:
    @ctest --test-dir build -N | grep "Test #" | sed 's/.*: //'

# Build the project
build:
    @cmake --build build

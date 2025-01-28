# yosh.i 2.1
Designed on macOS Sequoia 15.2

This shell project originated as a collaboration between myself and a 42 student. I’m now rewriting it to improve its design and maintainability.

Much of the original code was difficult to reuse, partly due to the strict project constraints at 42, such as 25-line functions and 80-character line limits. ChatGPT has helped rewrite sections of the original code, especially the parts authored by the other student, which were undoubtedly complex given the rules.

```make libs``` to make library libdanc
``` make ``` to make project
```make clean``` clean executables and object files from project

## Current Features
 - Executes external programs.
 - Handles single and double quotes effectively.
 - Supports environment variable expansion.
 - Includes built-in commands for unset and export.
 - Maintains its own copy of the environment variable list.

## Future Features
 - Pipes
 - Redirections
 - Configuration for Colours

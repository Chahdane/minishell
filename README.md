#  Minishell $>

This is a 42 project that aims to create a minimized version of Bash. This shell integrates a set of built-ins like echo and export can run any number of commands in a pipeline. 

# Features

 - Expansion of environment variables and return statuses of commands
 - The Handling the interrupt and quit signals is quite similar to Bash
 - Works with heredocs anywhere in the pipeline
 - Redirection of output to files in overwrite and append modes
 - Redirection of input to commands from files
 
 # Usage
 
 After you clone the repo, run the following in your terminal:

    cd minishell && make && ./minishell

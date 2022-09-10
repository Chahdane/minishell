#  Minishell $>

This is a 42 project that aims to create a minimized version of Bash. This shell integrates a set of built-ins like echo and export can run any number of commands in a pipeline. 

# Features

 - Expansion of environment variables and return statuses of commands
 - The Handling the interrupt and quit signals is quite similar to Bash
 - Works with heredocs anywhere in the pipeline
 - Redirection of output to files in overwrite and append modes
 - Redirection of input to commands from files
 
 # Usage
 
 In your MacOs machine, run the following in your terminal:

    git clone git@github.com:otmanewahdani/minishell.git && cd minishell && make && ./minishell

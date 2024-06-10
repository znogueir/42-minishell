# 42-minishell
#### A 42 School project
<br>

Goal(s) : 
- create a dumbed down version of bash posix in C.
<br>

Features :
- command execution
- command history
- redirections and pipes
- heredocs
- env variables
- quotes handling (' & ") with their respective effects on $vars
- builtins :
  - echo, with -n option
  - cd, handles ~, - and relative paths
  - export, supports =, +=, separates empty vars in env & export
  - unset
  - env
  - pwd
  - exit
- signal handling for ctrl-C & ctrl-\
- ctrl-D exits
- wildcards (bonus)
<br>

Concept(s) learned :
- processes (child & parent relation)
- how a posix shell works
- signals and signal propagation
- advanced strings parsing
- error handling
- memory management

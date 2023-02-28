## Tests to check

```
./pipex infile "/ls" "/cat" outfile
./pipex infile "" "wc -l" outfile 
./pipex infile "ls" "" outfile
./pipex inpufile "cd .." "ls" output 
```

protect mallocs carefully: ft_strjoin ft_strdup ft_calloc dup2

manage libft dependencies

keep name of main.c

limit cmd size (64 for exemple)

lancer toutes les commandes en parrallele

distiguer le waitpid de la derniere commande pour l'EXITCODE

pas besoin d' un tableau de fd_pipe (2 ou 4 suffisent)

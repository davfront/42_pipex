## Tests

- [x] `./pipex infile "/ls" "/cat" outfile`

- [x] `./pipex infile "" "wc -l" outfile `

- [x] `./pipex infile "ls" "" outfile`

- [ ] `./pipex inpufile "cd .." "ls" output `

## Fixes

- [x] protect mallocs carefully: ft_strjoin ft_split ft_calloc dup2

- [x] manage libft dependencies

- [x] keep name of main.c

- [x] limit cmd size (64 for exemple)

- [x] lancer toutes les commandes en parrallele

- [x] distiguer le waitpid de la derniere commande pour l'EXITCODE


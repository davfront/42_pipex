# NOTES

## Consignes

```
./pipex file1 "cmd1" "cmd2" file2
```

equivalent to:

```
< file1 cmd1 | cmd2 > file2
```


## Commands for tests

```
# pipex
./pipex tests/prenoms.txt "grep al" "wc -l" tests/result.txt
```

```
#pipe
< tests/prenoms.txt grep al | wc -l > tests/result.txt

```
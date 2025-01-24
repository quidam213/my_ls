# my_ls
Minimal recode of ls executable in C

### Flags

-l : list files informations.
```bash
> ./my_ls -l
-rw-r--r-- 1 dam dam     306 Jan 24 09:31 Makefile
-rw-r--r-- 1 dam dam     129 Jan 24 16:27 README.md
-rwxr-xr-x 1 dam dam   22976 Jan 24 16:28 my_ls
drwxr-xr-x 1 dam dam      52 Jan 24 08:43 src
```

-a : include hidden files.
```bash
> ./my_ls -a
. .. .git .gitignore .vscode Makefile README.md my_ls src
```

-r : reverse the output.
```bash
> ./my_ls -r
src my_ls README.md Makefile
```

-t : sort by time.
```bash
> ./my_ls -t
README.md my_ls Makefile src
```

You can also combine multiples flags.
```
> ./my_ls -la
> ./my_ls -l -a -t
```

You can also specify the path.
```
> ./my_ls -l ..
> ./my_ls -a -r ~ .. /home
```


### How to use it ?
Clone the repository or download it.

Use the Makefile to build the binary
```bash
> make          # build the lib
> make re       # rebuild if it exists
> make clean    # clean the tmp file
> make fclean   # clean all, also the lib
```

Then you can use it !
```bash
> ./my_ls
Makefile README.md my_ls src
```

### Author
dam, github : quidam213

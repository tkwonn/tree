# tree

This program supports several options from the [GNU tree utility](https://linux.die.net/man/1/tree). It recursively lists the contents of a specified directory in a tree-like format.  
The following options are available. To execute, run `make`.

```bsh
❯ ./tree --help
Usage: tree [-adpugstcrU] [--help] [directory ...]

------- Listing options -------
  -a    All files are listed.
  -d    List directories only.

------- File options -------
  -p    Print the protection for each file.
  -u    Print file owner or UID number.
  -g    Print file group owner or GID number.
  -s    Print the size in bytes of each file.

------- Sorting options -------
  -t    Sort files by last modification time.
  -c    Sort files by last status change time.
  -r    Sort in reverse order.
  -U    Leave files unsorted.

------- Miscellaneous options -------
  --help    Print this help message.
```

## Demo

[![asciicast](https://asciinema.org/a/4NXUfSTGgVhEAULL0s0thOAiA.svg)](https://asciinema.org/a/4NXUfSTGgVhEAULL0s0thOAiA)

## Example Output

```bash
❯ ./tree
.
├── Makefile
├── README.md
├── include
│   ├── errors.h
│   ├── options.h
│   ├── print.h
│   └── tree.h
├── src
│   ├── errors.c
│   ├── options.c
│   ├── print.c
│   └── tree.c
└── tree

3 directories, 11 files

❯ ./tree -pugs
[drwxr-xr-x tk        staff         256]  .
├── [-rw-r--r-- tk        staff         312]  Makefile
├── [-rw-r--r-- tk        staff        1607]  README.md
├── [drwxr-xr-x tk        staff         192]  include
│   ├── [-rw-r--r-- tk        staff        1004]  errors.h
│   ├── [-rw-r--r-- tk        staff         568]  options.h
│   ├── [-rw-r--r-- tk        staff        1131]  print.h
│   └── [-rw-r--r-- tk        staff         581]  tree.h
├── [drwxr-xr-x tk        staff         192]  src
│   ├── [-rw-r--r-- tk        staff        1692]  errors.c
│   ├── [-rw-r--r-- tk        staff        2155]  options.c
│   ├── [-rw-r--r-- tk        staff        3968]  print.c
│   └── [-rw-r--r-- tk        staff        5186]  tree.c
└── [-rwxr-xr-x tk        staff       52248]  tree

3 directories, 11 files
```
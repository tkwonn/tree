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
❯ ./tree /test
/test
├── a.txt
├── b.txt
├── c.txt
├── hard_link
└── soft_link -> b.txt

1 directories, 5 files

❯ ./tree -pugs /test
[drwxr-xr-x tk        wheel         224]  /test
├── [-rw-r--r-- tk        wheel           0]  a.txt
├── [-rw-r--r-- tk        wheel           0]  b.txt
├── [-rw-r--r-- tk        wheel           0]  c.txt
├── [-rw-r--r-- tk        wheel           0]  hard_link
└── [lrwxr-xr-x tk        wheel           5]  soft_link -> b.txt

1 directories, 5 files
```
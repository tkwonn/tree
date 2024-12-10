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


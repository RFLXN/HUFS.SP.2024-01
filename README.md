# System Programming - Final Assignment
**in HUFS 2024-01 semester**

# Introduction
**CLI-based dummy file generator.**

using like this:    

1. empty directory before
![before](https://raw.githubusercontent.com/RFLXN/HUFS.SP.2024-01/main/dimg/before.png)    

2. run command
```shell
./dummygen -n 12 -p test_ -s .txt -f -c
```

3. dummy files generated after
![after](https://raw.githubusercontent.com/RFLXN/HUFS.SP.2024-01/main/dimg/after.png)

## Usage
```shell
./dummygen -n <number> [options]
```

### options
| name            | shorten | description                            | value  |
|-----------------|---------|----------------------------------------|--------|
| --num           | -n      | number of files to generate [REQUIRED] | number |
| --prefix        | -p      | prefix of file name [OPTIONAL]         | string |
| --suffix        | -s      | suffix of file name [OPTIONAL]         | string |
| --force         | -f      | force overwrite [OPTIONAL]             | none   |
| --with-contents | -c      | generate with contents [OPTIONAL]      | none   |

If given `--with-contents` (`-c`) options, generated file contains like random contents like this:    
![with-contents](https://raw.githubusercontent.com/RFLXN/HUFS.SP.2024-01/main/dimg/content.png)


### Environment Variables
| name         | description                           | value  | default |
|--------------|---------------------------------------|--------|---------|
| PROCESS_NUMS | number of worker processes [OPTIONAL] | number | 10      |


# Structure
* main.c: main function file.
* constant.h: header file for constant values.
* args.h: header file for argument parsing function.
* env.h: header file for environment variable parsing function.
* file_access.h: header file for file existence checking function.
* file_create.h: header file for file creation function.
* file_name.h: header file for file name generation function.
* random_string.h: header file for random string generation function.
* Makefile: makefile for build. run `make` to build `dummygen` executable file.

# Assignment Achievement
* Has comment?: YES for all files.
* FILE R/W: YES
  * file_create.h::create_file()
* System or File Information: YES
  * file_access.h::is_file_exist() - File Information.
  * random_string.h::random_string() - System Information (time).
* Process Fork / Exec: YES
  * main.c::main()::Line 61 - Fork child process for multiprocessing.
  * main.c::main()::Line 84, 148 - Fork child process and run `execl()` for force file remove. (/bin/rm)
* IPC / SystemV IPC: NO
* Makefile: YES and it works. (at least on my environment. See below section: "Test Environment".)
* Implementation Explain Video: YES. See below section: "Explain Video."

# Explain Video
[![video - youtube]()]()

# Test Environment
All build and test runs are running on Apple Macbook Pro M1, MacOS Sonoma (14.4.1)

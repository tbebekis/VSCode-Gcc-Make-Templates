# VSCode C/C++ developement on Windows and Linux with gcc and make

Back in 2019 I wrote a similar text, [VSCode: C/C++ development with gcc and make Windows and Linux](https://teonotebook.wordpress.com/2019/03/27/c-c-development-with-gcc-and-vscode-windows-and-linux/) about using [VSCode](https://code.visualstudio.com/) in developing C and C++ applications, on Windows and Linux, with [gcc](https://en.wikipedia.org/wiki/GNU_Compiler_Collection), [make](https://en.wikipedia.org/wiki/Make_(software)) and a [makefile](https://en.wikipedia.org/wiki/Make_(software)#Makefile).

This text faces the exact same problem and I think I did a better job this time.

## VSCode preparation

There are some useful links in VSCode, about C/C++ development, to consider.

- [C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp)
- [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)
 
The following VSCode extensions must be installed. 

- [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
- [VS Code Makefile Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools)

## MSYS2

To use gcc in Windows the [msys2](https://www.msys2.org/) installation is required.

As their page says "*MSYS2 is a collection of tools and libraries providing you with an easy-to-use environment for building, installing and running native Windows software.*"

msys2 installation is easy. There is an "Installation" section in msys page with easy to follow instructions on how to install gcc and everything else needed to do C/C++ developemnt with gcc in Windows. 

The following entries are required in the `PATH` System Evniroment Variable.

```
C:\msys64\usr\bin
C:\msys64\ucrt64\bin
C:\msys64\mingw64\share
```

## C and Cpp template projects
Clone the repository from [github](https://github.com/tbebekis/VSCode-Gcc-Make-Templates). It contains two projects in two folders:

- C
- Cpp

Open any of these folders with VSCode and examine the content.

There is a number of `JSON` files, in the `.vscode` folder, that affect the behavior of VSCode.

### c_cpp_properties.json

The `c_cpp_properties.json` file stores stores **IntelliSense** configuration settings, which is very important. 

More information about configuring Intellisense for a C/Cpp project can be found at the following links:

- [Configure C/C++ IntelliSense](https://code.visualstudio.com/docs/cpp/configure-intellisense)
- [c_cpp_properties.json reference](https://code.visualstudio.com/docs/cpp/c-cpp-properties-schema-reference)

### tasks.json

The `tasks.json` is where tasks are configured. It contains the following tasks:

- Debug
- Release
- Clean

These tasks call the `make` application when are executed. Use `Ctrl + Shift + B` to see a drop-down and select a task to execute.

All these tasks use the `make` application in both, Windows and Linux.

### launch.json

The `launch.json` is used to **run** the application in debug and release mode. It contains two configurations:

- Debug
- Release

These configurations call the corresponding tasks from the `tasks.json`. They contain sections for Windows and Linux.

## The makefile

The same `makefile` is used in both, Windows and Linux, since both projects, C and Cpp, use the `gcc` tool-chain.

Most of the code in the `makefile` is comments, helping the reader to understand what is going on.

The developer can place source files **in any sub-folder** under the project root folder. It is **not** mandatory to place the code under the `src` folder.

This `makefile` uses a recursive call to the `wildcard` [make function](https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html) in order to collect `.c`, `.cpp`, `.h` and `.hpp` files found under the project root folder. It is taken from [stackoverflow](https://stackoverflow.com/a/18258352).

The following is the `makefile` of the `C` project.

```
# Project tree.
# Source or include files can be in any folder, sub-folder, nested or not.
# The bin and obj sub-folders are created if not already exist.
#
# + project
#	+ bin
#	+ obj
#   + src          NOTE: you may use a folder named src, but it's not mandatory
#	makefile

# CAUTION: Commands SHOULD start with a tab character

# NOTE: use @echo $(VAR_NAME) for debugging a make file
# Display:
#	@echo $(VAR_NAME)
 
RM := rm -f   
Target := $(notdir $(CURDIR))  	  # application executable file name

# NOTE: use the following when in Windows and not using Cygwin, MSYS2 or MINGW
# SEE: https://stackoverflow.com/questions/714100/os-detecting-makefile
#ifeq ($(OS), Windows_NT)     
#  RM := del  
#  Target := $(notdir $(CURDIR).exe)   # application executable file name
#endif 

# paths  
# gets the full path, e.g. /cygdrive/c/_Dev/CSharp/Research/Research.Makefile/Test
FullPath := $(CURDIR)

# folders
RootFolder   := $(shell basename $(FullPath))
SourceFolder := .
BinFolder    := bin
ObjFolder    := obj
OutFolders   := $(ObjFolder)
OutFolders   += $(BinFolder)

# create needed folders
$(shell mkdir -p $(OutFolders))
 
# GetFiles(FolderList, FilePatternList) 
# gets the files found in a specified list of folders and any sub-folders, 
# matching to a list of file patterns, e.g. *.c *.h
#
# The first parameter ($1) is a list of directories, 
# and the second ($2) is a list of the patterns to match.
#
# Example
# sources := $(call GetFile, $(SourceFolder), *.c *.h) 
#
# FROM: https://stackoverflow.com/a/18258352
# CAUTION: do NOT make it :=
GetFiles = $(foreach d,$(wildcard $(1:=/*)),$(call GetFiles,$d,$2) $(filter $(subst *,%,$2),$d))
 
 # gets all *.c files in SourceFolder and its subfolders, e.g. src/a/aa/file1.c src/a/file0.c src/main.c
SourceFilePaths  := $(call GetFiles, $(SourceFolder), *.c) 	
SourceFolders    := $(sort $(dir $(SourceFilePaths))) 
SourceFileNames  := $(notdir $(SourceFilePaths)) 
ObjectFilePaths  := $(SourceFileNames:%=$(ObjFolder)/%.o) 
IncludeFilePaths := $(call GetFiles, $(SourceFolder), *.h) 
IncludeFolders   := $(sort $(dir $(IncludeFilePaths))) 
 
# Add a prefix to IncludeFolders. So Folder1 would become -IFolder1. GCC understands this -I flag
IncludeFlags := $(addprefix -I,$(IncludeFolders)) 

CFLAGS := ${IncludeFlags} -Wall		# SEE: https://medium.com/@promisevector/c-programming-mastering-flags-in-gcc-32809491f340 

# -M causes Error: file format not recognized; treating as linker script
#CFLAGS += -M						# SEE: https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html

ifdef DEBUG
	CFLAGS += -g	
endif 

VPATH = $(SourceFolders)

# link
$(BinFolder)/$(Target): $(ObjectFilePaths) 
	$(CC) $(ObjectFilePaths) -o $@ $(LDFLAGS)

# compile
$(ObjFolder)/%.c.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# clean target, calling "make Clean" cleans the project
CleanFilePathList := $(ObjectFilePaths)
CleanFilePathList += $(BinFolder)/$(Target)

.PHONY: Clean
Clean:
	$(shell $(RM) $(CleanFilePathList))

.PHONY: Display
Display:
	@echo SourceFilePaths: $(SourceFilePaths)
	@echo IncludeFilePaths: $(IncludeFilePaths) 	
```

## Tested On

- Windows 11 - gcc (Rev3, Built by MSYS2 project) 14.1.0
- Linux Mint 21 Cinnamon - gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0



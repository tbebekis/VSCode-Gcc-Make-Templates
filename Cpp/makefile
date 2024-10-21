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
SourceFilePaths  := $(call GetFiles, $(SourceFolder), *.cpp) 	
SourceFolders    := $(sort $(dir $(SourceFilePaths))) 
SourceFileNames  := $(notdir $(SourceFilePaths)) 
ObjectFilePaths  := $(SourceFileNames:%=$(ObjFolder)/%.o) 
IncludeFilePaths := $(call GetFiles, $(SourceFolder), *.hpp) 
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
	$(CXX) $(ObjectFilePaths) -o $@ $(LDFLAGS)

# compile
$(ObjFolder)/%.cpp.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

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

 	
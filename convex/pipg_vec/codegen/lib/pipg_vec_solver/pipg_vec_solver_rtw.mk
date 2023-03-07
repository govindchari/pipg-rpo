###########################################################################
## Makefile generated for component 'pipg_vec_solver'. 
## 
## Makefile     : pipg_vec_solver_rtw.mk
## Generated on : Tue Mar 07 11:23:44 2023
## Final product: ./pipg_vec_solver.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = pipg_vec_solver
MAKEFILE                  = pipg_vec_solver_rtw.mk
MATLAB_ROOT               = /usr/local/MATLAB/R2022b
MATLAB_BIN                = /usr/local/MATLAB/R2022b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
START_DIR                 = /home/govind/Desktop/git/pipg-rpo/convex/pipg_vec
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
C_STANDARD_OPTS           = -fwrapv
CPP_STANDARD_OPTS         = -fwrapv
MODELLIB                  = pipg_vec_solver.a

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU gcc/g++ | gmake (64-bit Linux)
# Supported Version(s):    
# ToolchainInfo Version:   2022b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS         = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX     = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS     = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC = gcc

# Linker: GNU Linker
LD = g++

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/glnxa64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_STANDARD_OPTS) -fPIC \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -fPIC \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPP_LDFLAGS          =
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,--no-undefined
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,--no-undefined



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./pipg_vec_solver.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/pipg_vec_solver -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=pipg_vec_solver

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/pipg_vec_solver/coder_posix_time.c $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_data.c $(START_DIR)/codegen/lib/pipg_vec_solver/rt_nonfinite.c $(START_DIR)/codegen/lib/pipg_vec_solver/rtGetNaN.c $(START_DIR)/codegen/lib/pipg_vec_solver/rtGetInf.c $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_initialize.c $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_terminate.c $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver.c $(START_DIR)/codegen/lib/pipg_vec_solver/tic.c $(START_DIR)/codegen/lib/pipg_vec_solver/timeKeeper.c $(START_DIR)/codegen/lib/pipg_vec_solver/diag.c $(START_DIR)/codegen/lib/pipg_vec_solver/minOrMax.c $(START_DIR)/codegen/lib/pipg_vec_solver/mtimes.c $(START_DIR)/codegen/lib/pipg_vec_solver/colon.c $(START_DIR)/codegen/lib/pipg_vec_solver/toc.c $(START_DIR)/codegen/lib/pipg_vec_solver/CoderTimeAPI.c $(START_DIR)/codegen/lib/pipg_vec_solver/introsort.c $(START_DIR)/codegen/lib/pipg_vec_solver/insertionsort.c $(START_DIR)/codegen/lib/pipg_vec_solver/heapsort.c $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_emxutil.c $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_emxAPI.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = coder_posix_time.o pipg_vec_solver_data.o rt_nonfinite.o rtGetNaN.o rtGetInf.o pipg_vec_solver_initialize.o pipg_vec_solver_terminate.o pipg_vec_solver.o tic.o timeKeeper.o diag.o minOrMax.o mtimes.o colon.o toc.o CoderTimeAPI.o introsort.o insertionsort.o heapsort.o pipg_vec_solver_emxutil.o pipg_vec_solver_emxAPI.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS =  -lm

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/pipg_vec_solver/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/pipg_vec_solver/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coder_posix_time.o : $(START_DIR)/codegen/lib/pipg_vec_solver/coder_posix_time.c
	$(CC) $(CFLAGS) -o "$@" "$<"


pipg_vec_solver_data.o : $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/codegen/lib/pipg_vec_solver/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/codegen/lib/pipg_vec_solver/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/codegen/lib/pipg_vec_solver/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


pipg_vec_solver_initialize.o : $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


pipg_vec_solver_terminate.o : $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


pipg_vec_solver.o : $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver.c
	$(CC) $(CFLAGS) -o "$@" "$<"


tic.o : $(START_DIR)/codegen/lib/pipg_vec_solver/tic.c
	$(CC) $(CFLAGS) -o "$@" "$<"


timeKeeper.o : $(START_DIR)/codegen/lib/pipg_vec_solver/timeKeeper.c
	$(CC) $(CFLAGS) -o "$@" "$<"


diag.o : $(START_DIR)/codegen/lib/pipg_vec_solver/diag.c
	$(CC) $(CFLAGS) -o "$@" "$<"


minOrMax.o : $(START_DIR)/codegen/lib/pipg_vec_solver/minOrMax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mtimes.o : $(START_DIR)/codegen/lib/pipg_vec_solver/mtimes.c
	$(CC) $(CFLAGS) -o "$@" "$<"


colon.o : $(START_DIR)/codegen/lib/pipg_vec_solver/colon.c
	$(CC) $(CFLAGS) -o "$@" "$<"


toc.o : $(START_DIR)/codegen/lib/pipg_vec_solver/toc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


CoderTimeAPI.o : $(START_DIR)/codegen/lib/pipg_vec_solver/CoderTimeAPI.c
	$(CC) $(CFLAGS) -o "$@" "$<"


introsort.o : $(START_DIR)/codegen/lib/pipg_vec_solver/introsort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


insertionsort.o : $(START_DIR)/codegen/lib/pipg_vec_solver/insertionsort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


heapsort.o : $(START_DIR)/codegen/lib/pipg_vec_solver/heapsort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


pipg_vec_solver_emxutil.o : $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_emxutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


pipg_vec_solver_emxAPI.o : $(START_DIR)/codegen/lib/pipg_vec_solver/pipg_vec_solver_emxAPI.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."



#=============================================================================#
# toolchain configuration
#=============================================================================#

TOOLCHAIN = arm-none-eabi

CC                      = $(TOOLCHAIN)-gcc
AS                      = $(TOOLCHAIN)-gcc -x assembler-with-cpp
OBJCOPY					= $(TOOLCHAIN)-objcopy
OBJDUMP 				= $(TOOLCHAIN)-objdump
SIZE 					= $(TOOLCHAIN)-size

MKDIR = mkdir -p
RM = rm -f

#=============================================================================#
# project configuration
#=============================================================================#

# project name
PROJECT = MotorDriver

# core type
CORE = cortex-m3

# linker script
LD_SCRIPT = Linker.ld

# C definitions
C_DEFS = -DSTM32F10X_CL

# ASM definitions
AS_DEFS =

# output folder (absolute or relative path, leave empty for in-tree compilation)
OUT_DIR = bin
COMPILE_DIR = $(OUT_DIR)/compile

# include directories (absolute or relative paths to additional folders with
# headers, current folder is always included)
INC_DIRS  = Inc
INC_DIRS += Drivers/system
INC_DIRS += Drivers/led
INC_DIRS += Drivers/motor
INC_DIRS += Drivers/button
INC_DIRS += Drivers/encoder

# additional directories with source files (absolute or relative paths to
# folders with source files, current folder is always included)
SRCS_DIRS  = Src
SRCS_DIRS += Drivers/system
SRCS_DIRS += Drivers/led
SRCS_DIRS += Drivers/motor
SRCS_DIRS += Drivers/button
SRCS_DIRS += Drivers/encoder

#=============================================================================#
# paths formatting
#=============================================================================#

# Set VPATH to search for sources in SRCS_DIRS
VPATH = $(SRCS_DIRS)

INC_DIRS_F = -I. $(patsubst %, -I%, $(INC_DIRS))

OUT_DIR_F = $(strip $(OUT_DIR))/
COMPILE_DIR_F = $(strip $(COMPILE_DIR))/

# contents of output directory
GENERATED = $(wildcard $(patsubst %, $(COMPILE_DIR_F)*.%, d lst o))
GENERATED += $(wildcard $(patsubst %, $(OUT_DIR_F)*.%, bin dmp elf lss map))

C_EXT = c
C_SRCS = $(wildcard $(patsubst %, %/*.$(C_EXT), . $(SRCS_DIRS)))
C_OBJS = $(addprefix $(COMPILE_DIR_F), $(notdir $(C_SRCS:.$(C_EXT)=.o)))

AS_EXT = s
AS_SRCS = $(wildcard $(patsubst %, %/*.$(AS_EXT), . $(SRCS_DIRS)))
AS_OBJS = $(addprefix $(COMPILE_DIR_F), $(notdir $(AS_SRCS:.$(AS_EXT)=.o)))

OBJS = $(AS_OBJS) $(C_OBJS)
DEPS = $(OBJS:.o=.d)

ELF = $(OUT_DIR_F)$(PROJECT).elf
BIN = $(OUT_DIR_F)$(PROJECT).bin
LSS = $(OUT_DIR_F)$(PROJECT).lss

#=============================================================================#
# various compilation flags
#=============================================================================#

# optimization flags ("-O0" - no optimization, "-O1" - optimize, "-O2" -
# optimize even more, "-Os" - optimize for size or "-O3" - optimize yet more) 
OPTIMIZATION = -Os -ffunction-sections

# define warning options here
C_WARNINGS = -Wall -Wstrict-prototypes -Wextra -Wno-implicit-fallthrough -pedantic

# C language standard ("c89" / "iso9899:1990", "iso9899:199409",
# "c99" / "iso9899:1999", "gnu89" - default, "gnu99")
C_STD = c11

# core flags
CORE_FLAGS = -mcpu=$(CORE) -mthumb -mfloat-abi=soft

# flags for C compiler
C_FLAGS = -std=$(C_STD) -g -ggdb3 -fverbose-asm -Wa,-ahlms=$(COMPILE_DIR_F)$(notdir $(<:.$(C_EXT)=.lst))

# flags for assembler
AS_FLAGS = -g -ggdb3 -Wa,-amhls=$(COMPILE_DIR_F)$(notdir $(<:.$(AS_EXT)=.lst))

# flags for linker
LD_FLAGS = -T$(LD_SCRIPT) -g -Wl,-Map=$(OUT_DIR_F)$(PROJECT).map,--cref,--no-warn-mismatch -Wl,--gc-sections -Wl,--undefined=uxTopUsedPriority
LD_FLAGS += -nostartfiles -specs=nosys.specs -specs=nano.specs

# format final flags for tools, request dependancies for C++, C and asm
C_FLAGS_F = $(CORE_FLAGS) $(OPTIMIZATION) $(C_WARNINGS) $(C_FLAGS) $(C_DEFS) -MD -MP -MF $(COMPILE_DIR_F)$(@F:.o=.d) $(INC_DIRS_F)
AS_FLAGS_F = $(CORE_FLAGS) $(AS_FLAGS) $(AS_DEFS) -MD -MP -MF $(COMPILE_DIR_F)$(@F:.o=.d) $(INC_DIRS_F)$
LD_FLAGS_F = $(CORE_FLAGS) $(LD_FLAGS)

#=============================================================================#
# make all
#=============================================================================#

all : $(OUT_DIR) $(COMPILE_DIR) $(ELF) $(LSS) $(BIN) print_size

# make object files dependent on Makefile
$(OBJS) : Makefile
# make .elf file dependent on linker script
$(ELF) : $(LD_SCRIPT)

#-----------------------------------------------------------------------------#
# linking - objects -> elf
#-----------------------------------------------------------------------------#

$(ELF) : $(OBJS)
	@echo 'Linking target: $(ELF)'
	$(CC) $(LD_FLAGS_F) $(OBJS) -o $@
	@echo ' '

#-----------------------------------------------------------------------------#
# compiling - C source -> objects
#-----------------------------------------------------------------------------#

$(COMPILE_DIR_F)%.o : %.$(C_EXT)
	@echo 'Compiling file: $<'
	$(CC) -c $(C_FLAGS_F) $< -o $@
	@echo ' '

#-----------------------------------------------------------------------------#
# assembling - ASM source -> objects
#-----------------------------------------------------------------------------#

$(COMPILE_DIR_F)%.o : %.$(AS_EXT)
	@echo 'Assembling file: $<'
	$(AS) -c $(AS_FLAGS_F) $< -o $@
	@echo ' '

#-----------------------------------------------------------------------------#
# memory images - elf -> bin
#-----------------------------------------------------------------------------#

$(BIN) : $(ELF)
	@echo 'Creating binary image: $(BIN)'
	$(OBJCOPY) -O binary $< $@
	@echo ' '

#-----------------------------------------------------------------------------#
# extended listing - elf -> lss
#-----------------------------------------------------------------------------#

$(LSS) : $(ELF)
	@echo 'Creating extended listing: $(LSS)'
	$(OBJDUMP) -S $< > $@
	@echo ' '

#-----------------------------------------------------------------------------#
# create the desired output directory
#-----------------------------------------------------------------------------#

$(OUT_DIR) :
	@echo 'Creating output directory: $(OUT_DIR)'
	$(MKDIR) $(OUT_DIR)
	@echo ' '

$(COMPILE_DIR) :
	@echo 'Creating compile directory: $(COMPILED_DIR)'
	$(MKDIR) $(COMPILE_DIR)
	@echo ' '

#-----------------------------------------------------------------------------#
# print the size of the objects and the .elf file
#-----------------------------------------------------------------------------#

print_size : $(ELF)
	@echo 'Size of modules:'
	$(SIZE) -B -t --common $(OBJS)
	@echo ' '
	@echo 'Size of target .elf file:'
	$(SIZE) -B $(ELF)
	@echo ' '

#-----------------------------------------------------------------------------#
# make clean
#-----------------------------------------------------------------------------#

clean:
ifneq ($(strip $(GENERATED) $(wildcard $(COMPILE_DIR)) $(wildcard $(OUT_DIR))), )
ifneq ($(strip $(GENERATED)), )
	@echo 'Removing all generated output files'
	$(RM) $(GENERATED)
endif
ifneq ($(wildcard $(COMPILE_DIR)), )
	@echo 'Removing compile directory'
	$(RM) -r $(COMPILE_DIR)
endif
ifneq ($(wildcard $(OUT_DIR)), )
	@echo 'Removing output directory'
	$(RM) -r $(OUT_DIR)
endif
else
	@echo 'Nothing to remove...'
endif

#=============================================================================#
# global exports
#=============================================================================#

.PHONY: all clean dependents

.SECONDARY:

# include dependancy files
-include $(DEPS)


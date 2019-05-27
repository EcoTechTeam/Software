#================================================================#
# AVR makefile
#
#================================================================#

TOOLCHAIN = avr

CC = $(TOOLCHAIN)-gcc
OBJCOPY = $(TOOLCHAIN)-objcopy
OBJDUMP = $(TOOLCHAIN)-objdump
SIZE = $(TOOLCHAIN)-size

RM = rm -f

PROJECT = MotorController

# Includes directories
INC_DIRS = Inc
INC_DIRS += Drivers/bus
INC_DIRS += Drivers/button
INC_DIRS += Drivers/led 
INC_DIRS += Drivers/timer
INC_DIRS += Drivers/watchdog
INC_DIRS += Libraries/message
INC_DIRS_F = -I. $(patsubst %, -I%, $(INC_DIRS))

# Sources directories
SRCS_DIRS = Src
SRCS_DIRS += Drivers/bus
SRCS_DIRS += Drivers/button
SRCS_DIRS += Drivers/led
SRCS_DIRS += Drivers/timer
SRCS_DIRS += Drivers/watchdog
SRCS_DIRS += Libraries/message
SRCS_DIRS_F = $(strip $(SRCS_DIRS))

# Extension of C files
C_EXT = c
C_SRCS = $(wildcard $(patsubst %, %/*.$(C_EXT), . $(SRCS_DIRS)))

# Output directories: OUT_DIR for output and OUT_DIR/C_DIR for objects
OUT_DIR = bin
OUT_DIR_F = $(strip $(OUT_DIR))/
C_DIR = compile
C_DIR_F = $(strip $(C_DIR))/

# Build flags
CORE = atmega8
CORE_FLAGS = -mmcu=$(CORE)

OPTIMIZATION = -O0 -ffunction-sections
C_WARNINGS = -Wall -Wextra -pedantic
C_STD = c11
C_FLAGS = -std=$(C_STD) -g 
C_FLAGS_F = $(CORE_FLAGS) $(OPTIMIZATION) $(C_WARNINGS) $(C_FLAGS) -MD -MP -MF $(OUT_DIR_F)$(C_DIR_F)$(@F:.o=.d) $(INC_DIRS_F)

LD_FLAGS = -g -Wl,-Map=$(OUT_DIR_F)$(PROJECT).map,--cref,--no-warn-mismatch
LD_FLAGS += -Wl,--gc-sections
LD_FLAGS_F = $(LD_FLAGS) $(CORE_FLAGS)

# Objects
C_OBJS = $(addprefix $(OUT_DIR_F)$(C_DIR_F), $(notdir $(C_SRCS:.$(C_EXT)=.o)))
OBJS = $(C_OBJS)
DEPS = $(OBJS:.o=.d)

ELF = $(OUT_DIR_F)$(PROJECT).elf
HEX = $(OUT_DIR_F)$(PROJECT).hex
LSS = $(OUT_DIR_F)$(PROJECT).lss

GENERATED = $(wildcard $(patsubst %, $(OUT_DIR_F)$(C_DIR_F)*.%, d lst o))
GENERATED += $(wildcard $(patsubst %, $(OUT_DIR_F)*.%, bin dmp elf lss map))

# Set search path to sources directories
VPATH = $(SRCS_DIRS)

#=============================================================================#
# make all
#=============================================================================#

all : make_output_dir $(ELF) $(HEX) print_size 

# make object files dependent on Makefile
$(OBJS) : Makefile

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

$(OUT_DIR_F)$(C_DIR_F)%.o : %.$(C_EXT)
	@echo $(OBJS)
	@echo $(C_SRCS)
	@echo 'Compiling file: $<'
	$(CC) -c $(C_FLAGS_F) $< -o $@
	@echo ' '

#-----------------------------------------------------------------------------#
# memory images - elf -> bin
#-----------------------------------------------------------------------------#

$(HEX) : $(ELF)
	@echo ' '
	@echo 'Creating binary image: $(HEX)'
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
	@echo ' '

#-----------------------------------------------------------------------------#
# print the size of the .elf file
#-----------------------------------------------------------------------------#

print_size : $(ELF)
	@echo ' '
	@echo 'Size of target .elf file:'
	$(SIZE) -B $(ELF)
	@echo ' '

#-----------------------------------------------------------------------------#
# create the desired output directory
#-----------------------------------------------------------------------------#

make_output_dir:
	$(shell mkdir $(OUT_DIR_F) 2>/dev/null)
	$(shell mkdir $(OUT_DIR_F)$(C_DIR_F) 2>/dev/null)


#=============================================================================#
# make clean
#=============================================================================#

clean:
ifeq ($(strip $(OUT_DIR_F)$(C_DIR_F)), )
	@echo 'Removing all generated output files'
else
	@echo 'Removing all generated output files from output directory: $(OUT_DIR_F)'
endif
ifneq ($(strip $(GENERATED)), )
	$(RM) $(GENERATED)
	$(RM) -r $(OUT_DIR_F)$(C_DIR)
	$(RM) -r $(OUT_DIR)
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

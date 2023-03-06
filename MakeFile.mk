##########------------------------------------------------------##########
##########              Project-specific Details                ##########
##########    Check these every time you start a new project    ##########
##########------------------------------------------------------##########
## The name of your project (without the .c or .cpp)
# TARGET = blinkLED
## Or name it automatically after the enclosing directory
TARGET = $(lastword $(subst /, ,$(CURDIR)))

########-------------------------------------------------------------##########
########                   Directroy Paths!                   		 ##########
########         			 										 ##########
########         A directory for common include files a.			 ##########
########         If you move either the current folder or the 		 ##########
########         Library folder, you'll need to change 				 ##########
########         this path to match.								 ##########
########		 use foreach  to get all .c,.cpp ,.h files 			 ##########
########		from directories for example use this format 		 ##########
########															 ##########
######## 		dirs := a b c d 									 ##########
########   		files := $(foreach dir,$(dirs),$(wildcard $(dir)/*)) ##########
########-------------------------------------------------------------##########
# Doxygen configuration Directory paths
DOXYFILE= $(wildcard *.conf)

# Build path
BUILD_DIR = build

# startup Directory path
STARTUP_DIR =./.start_up

# libraries Directory paths
LIB_DIR =

# asm Directory paths
ASM_DIR =
# source Directory paths

#EXT_SRC_DIR =/opt/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src
EXT_SRC_DIR =./.driver/STM32F10x_StdPeriph_Driver/src
# header Directory paths
EXT_INC_DIR=./.driver/CMSIS/Core\
./.driver/CMSIS/Device/STM32F10x \
./.driver/STM32F10x_StdPeriph_Driver/inc

#EXT_INC_DIR=/opt/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/CoreSupport \
/arm-opt/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x \
/arm-opt/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/inc

##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:                                     ##########
##########             We want a .bin file .hex file            ##########
##########        Compile source files into .elf                ##########
##########        Convert .elf file into .hex                   ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########

##########------------------------------------------------------##########
##########                 Programmer Defaults                  ##########
##########          Set up once, then forget about it           ##########
##########        (Can override.  See bottom of file.)          ##########
##########------------------------------------------------------##########
# st-link:
PROGRAMMER_PATH = /arm-opt/stlink-1.7.0/build/Release/bin
PROGRAMMER_INFO =$(PROGRAMMER_PATH)/st-info
PROGRAMMER =$(PROGRAMMER_PATH)/st-flash
PROGRAMMER_ARGS = 	
##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:                                     ##########
##########             include all asm (.s) files   			##########
##########        	   from asm source directories 				##########
########## 			   predefined pathes      					##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
ASM_SOURCES = $(wildcard $(STARTUP_DIR)/startup_stm32f10x_md.s)
##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:                                     ##########
##########             include all .c files   					##########
##########        	   from C source directories 				##########
########## 			   predefined pathes      					##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
C_SOURCES =  $(wildcard *.c) 
C_SOURCES += $(foreach dir,$(EXT_SRC_DIR),$(wildcard $(dir)/*.c)) 
C_SOURCES += $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.c))
##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:                                     ##########
##########             include all .cpp files   				##########
##########        	   from C source directories 				##########
########## 			   predefined pathes      					##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
CX_SOURCES =  $(wildcard *.cpp) 
CX_SOURCES += $(foreach dir,$(EXT_SRC_DIR),$(wildcard $(dir)/*.cpp))
CX_SOURCES += $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.cpp))
##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:                                     ##########
##########             include all .h files as compiler flags 	##########
##########        	   from header directories 				    ##########
########## 			   predefined pathes 			      		##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
# asm includes
AS_INCLUDES = 
# C includes
CC_INCLUDES = $(foreach dir,$(EXT_INC_DIR),-I$(dir))
CC_INCLUDES +=$(foreach dir,$(INC_DIR),-I$(dir))
CC_INCLUDES +=-I.
##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary: Compiler setup                      ##########
##########        We want to set the gcc/g++ paths              ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
PREFIX = arm-none-eabi-
GCC_PATH=C:/arm-opt/gcc-arm-none-eabi-10.3-2021.10/bin
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
CX = $(GCC_PATH)/$(PREFIX)g++
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
CX = $(GCC_PATH)/$(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex			
BIN = $(CP) -O binary -S    
##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary: Compiler flags setup                ##########
##########    We want to configure the CCFLAGS,CXFLAGS,ASFLAGS  ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
CPU =-mcpu=cortex-m3
# fpu
# NONE for Cortex-M0/M0+/M3
FPU=
# for Cortex-M4/M7
#FPU=-mfpu=fpv4-sp-d16
# float-abi
# for Cortex-M0/M0+/M3
FLOAT-ABI=-mfloat-abi=soft
# for Cortex-M4/M7
#FLOAT-ABI= -mfloat-abi=hard
# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
# macros for gcc
# AS defines
AS_DEFS = -g
# C defines
CC_DEFS =  \
-DSTM32F10X_MD \
-DUSE_STDPERIPH_DRIVER \
-mlittle-endian  -mthumb-interwork \
-Wno-misleading-indentation \
-Wno-unused-variable \
-Wno-maybe-uninitialized \
#-DHSE_VALUE=8000000 \
-DHSE_STARTUP_TIMEOUT=100 \
-DLSE_STARTUP_TIMEOUT=5000 \
-DLSE_VALUE=32768 \
-DHSI_VALUE=8000000 \
-DLSI_VALUE=40000 \
-DVDD_VALUE=3300 \
-DPREFETCH_ENABLE=1 \
#-DUSE_HAL_DRIVER

CC_OPT=-O0 -ffunction-sections -fdata-sections -fstack-usage -Wall -specs=nano.specs 
CX_OPT=$(CC_OPT) -fno-rtti -fno-exceptions -fno-threadsafe-statics  
#-T$(LDSCRIPT)

DEBUG=1

# compile gcc/g++ flags
ASFLAGS =  $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(CC_OPT) 
CCFLAGS =  $(MCU) $(CC_DEFS) $(CC_INCLUDES) $(CC_OPT) 
CXFLAGS =  $(MCU) $(CC_DEFS) $(CC_INCLUDES) $(CX_OPT) 

ifeq ($(DEBUG), 1)
CCFLAGS += -g3 -gdwarf-2
CXFLAGS += -g3 -gdwarf-2
endif
#CFLAGS += -MMD -MP -MF "$(@:%.o=%.d)"
##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary: linker flags setup                  ##########
##########    We want to configure the linker flags (LDFLAGS)   ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
# link script
LDSCRIPT = $(STARTUP_DIR)/stm32_flash.ld
# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary: build the application               ##########
##########        We want a .elf file .bin file .hex file        ##########
##########        Compile source files into .elf                ##########
##########        Convert .elf file into .bin .hex               ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CX_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CX_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c  Makefile | $(BUILD_DIR)
#	@echo "Building Code"	$(SZ) $@
	$(CC) -c $(CCFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR) 
#	@echo "Building Code"	$(SZ) $@
	$(CX) -c $(CXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo "Building asm"
	$(AS) -c $(CCFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@echo "linking ...."
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
#	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo " generate hex..."
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo " generate bin..."
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		
	@echo "Building Code ...."
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)


# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex size

# Optionally show how big the resulting program is 
size:  #$(BUILD_DIR)/$(TARGET).elf
	   $(SZ) $(BUILD_DIR)/$(TARGET).elf


## These targets don't have files named after them
.PHONY: all  clean erase reset flash program
#size flash clean


##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:clean /build the application         ##########
##########        We want to remove all temporary files         ##########
##########        such as: .elf .o .lst .map files   			##########
##########        from the /build folader and the whole App     ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########
clean:
	@echo " Cleaning..."; 
	rm -fR $(BUILD_DIR)
#	rd /s $(BUILD_DIR)
		
clean_all:
	rm -f $(BUILD_DIR)/*.elf $(BUILDDIR)/*~
	rm -f $(BUILD_DIR)/*.obj $(BUILDDIR)/*.o 
	rm -f $(BUILD_DIR)/*.lst $(BUILDDIR)/*.lss    
	rm -f $(BUILD_DIR)/*.hex $(BUILDDIR)/*.d  

##########------------------------------------------------------##########
##########          Programmer-specific details                 ##########
##########   Flashing code to STM32 using OpenOCD st-link       ##########
##########------------------------------------------------------##########
openocd_inteface = intreface/stlink.cfg
openocd_target	 = target/stm32f1x.cfg
openocd: clean all
	openocd -f  $(openocd_inteface) -f $(openocd_target) -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"
##########------------------------------------------------------##########
##########              Programmer-specific details             ##########
##########           Flashing code to STM32 using st-link       ##########
##########------------------------------------------------------##########

## An alias
program: clean all erase flash reset 

flash: 
	   $(PROGRAMMER) write $(BUILD_DIR)/$(TARGET).bin 0x08000000

flash_write:
	   $(PROGRAMMER) write $(BUILD_DIR)/$(TARGET).hex 0x08000000

flash_read:
	   $(PROGRAMMER) read

erase:  
	$(PROGRAMMER) erase  
reset:  
	$(PROGRAMMER) reset  
	 
info:
	st-info --probe

##########------------------------------------------------------##########
##########                 Test pathes by  shell                ##########
##########          Set up once, then forget about it           ##########
##########        (Can override.  See bottom of file.)          ##########
##########------------------------------------------------------##########
src_dir: 
	@echo "Source Dir:" $(SRC_DIR)
c_src_file:	
	@echo "Source files:" $(C_SOURCES)
cx_src_file:	
	@echo "Source files:" $(CX_SOURCES)
inc_dir :	
	@echo "header Dir:"$(INC_DIR)
inc_file:	
	@echo "header files"$(HEADERS)
asm_dir:
	@echo "asm Dir:"$(ASM_DIR)
asm:	
	@echo "asm file:"$(ASM_SOURCES)
dir:
	@echo "header Dir:"$(INC_DIR)
	@echo "Source Dir:"$(SRC_DIR)
	@echo "asm Dir:"$(ASM_DIR)

obj:
	@echo "object files:"   $(OBJECTS)

tgt:
	@echo "TARGET files:"   $(TARGET)
arch:
	@echo "MCU:"  $(MCU)

cflg:
	@echo "cflg:"  $(CFLAGS)

cxflg:
	@echo "cxflg:"  $(CXFLAGS)

aflg:
	@echo "aflg:"  $(ASFLAGS)

ldflg:
	@echo "aflg:"  $(LDFLAGS)

debug:
	@echo
	@echo "C Source files:"     $(C_SOURCES)
	@echo "Cpp Source files:"   $(CX_SOURCES)
	@echo "header files:"   	$(HEADERS)
	@echo "object files:"   	$(OBJECTS)
	@echo "TARGET files:"   $(TARGET)
	@echo "MCU:"  $(MCU)
	@echo	

##########------------------------------------------------------##########
##########              doxygen-specific details                ##########
##########           									        ##########
##########------------------------------------------------------##########
doc: 
	doxygen $(DOXYFILE)

clean_doc:
	@echo " Cleaning html documents..."; 
	rm -r *html



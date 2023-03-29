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

# gcc Directory path based on the OS
OS=Win
GCC_Win_DIR=C:/arm-tool
GCC_linux_DIR= /opt

ifeq ($(OS),Win)
    GCC_DIR=$(GCC_Win_DIR)
else
    GCC_DIR=$(GCC_linux_DIR)
endif


# libraries Directory paths
LIB_DIR =
# asm Directory paths
ASM_DIR =
# source Directory paths
SRC_DIR =$(STARTUP_DIR)/src ./basic \
./init ./lcd ./keypad \
./system ./TIM ./uart \
./mpu6050 ./i2c
#./basic ./advanced ./lcd ./keypad ./sstem

EXT_SRC_DIR =
# header Directory paths
INC_DIR =$(STARTUP_DIR)/inc ./basic \
./init ./lcd ./keypad \
./system ./TIM ./uart \
./mpu6050 ./i2c
#./basic ./advanced ./lcd ./keypad ./system 

EXT_INC_DIR=
##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:                                     ##########
##########             We want a .bin file .hex file            ##########
##########        Compile source files into .elf                ##########
##########        Convert .elf file into .hex                   ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########

#include ./Makefile-linux.mk
include ./Makefile.mk

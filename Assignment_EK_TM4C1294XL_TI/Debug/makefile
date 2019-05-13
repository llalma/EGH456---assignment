################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := 

# All of the sources participating in the build are defined here
-include sources.mk
-include .config/xconfig_pwmled/package/cfg/subdir.mk
-include .config/xconfig_pwmled/package/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Assignment_EK_TM4C1294XL_TI.out

# Tool invocations
Assignment_EK_TM4C1294XL_TI.out: 
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	Assignment_EK_TM4C1294XL_TI.map 512 0 Assignment_EK_TM4C1294XL_TI.out /lib /include Assignment_EK_TM4C1294XL_TI_linkInfo.xml  "Assignment_EK_TM4C1294XL_TI.out"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_FILES)$(GEN_OPTS)$(OBJS)$(GEN_MISC_FILES)$(GEN_CMDS)$(GEN_MISC_DIRS) Assignment_EK_TM4C1294XL_TI.out
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
LTC4624JF.obj: ../LTC4624JF.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmsp --abi=eabi -Ooff --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/CascoLogix/workspace_v6_1/LaunchPad_MSP430G2553_LTC4624JF_LED_Driver" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="LTC4624JF.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmsp --abi=eabi -Ooff --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/CascoLogix/workspace_v6_1/LaunchPad_MSP430G2553_LTC4624JF_LED_Driver" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.c" \
"../Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.c" \
"../Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.c" 

COMPILED_SRCS += \
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.src" \
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.src" \
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.src" 

C_DEPS += \
"./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.d" \
"./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.d" \
"./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.d" 

OBJS += \
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.o" \
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.o" \
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.o" 


# Each subdirectory must supply rules for building sources it contributes
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.src":"../Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.c" "Libraries/iLLD/TC27D/Tricore/Cpu/CStart/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/hwi12/AURIX-v1.10.10-workspace/first12/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.o":"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.src" "Libraries/iLLD/TC27D/Tricore/Cpu/CStart/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.src":"../Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.c" "Libraries/iLLD/TC27D/Tricore/Cpu/CStart/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/hwi12/AURIX-v1.10.10-workspace/first12/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.o":"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.src" "Libraries/iLLD/TC27D/Tricore/Cpu/CStart/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.src":"../Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.c" "Libraries/iLLD/TC27D/Tricore/Cpu/CStart/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/hwi12/AURIX-v1.10.10-workspace/first12/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.o":"Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.src" "Libraries/iLLD/TC27D/Tricore/Cpu/CStart/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Cpu-2f-CStart

clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Cpu-2f-CStart:
	-$(RM) ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.d ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.o ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart0.src ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.d ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.o ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart1.src ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.d ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.o ./Libraries/iLLD/TC27D/Tricore/Cpu/CStart/IfxCpu_CStart2.src

.PHONY: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Cpu-2f-CStart


################################################################################
# 自動生成ファイルです。 編集しないでください!
################################################################################

# これらのツール呼び出しからの入力および出力をビルド変数へ追加します
C_SRCS += \
../NEON.c \
../RTX_Conf_CM.c \
../gic.c \
../mmu_VE_A9_MP.c \
../pl310.c \
../system_VE_A9_MP.c 

C_DEPS += \
./NEON.d \
./RTX_Conf_CM.d \
./gic.d \
./mmu_VE_A9_MP.d \
./pl310.d \
./system_VE_A9_MP.d 

OBJS += \
./NEON.o \
./RTX_Conf_CM.o \
./gic.o \
./mmu_VE_A9_MP.o \
./pl310.o \
./system_VE_A9_MP.o 


# サブディレクトリーはすべて、それ自身がコントリビュートするソースをビルドするためのルールを提供しなければなりません
%.o: ../%.c
	@echo 'ビルドするファイル: $<'
	@echo '呼び出し中: ARM C Compiler 5'
	armcc --cpu=Cortex-A9 --thumb --apcs=/interwork -D__MICROLIB -D__FPU_PRESENT -I"C:\Users\ryutan01\Documents\DS-5 Workshop NEON\CMSIS_RTOS_RTX\RTOS\RTX\SRC" -I"C:\Users\ryutan01\Documents\DS-5 Workshop NEON\CMSIS_RTOS_RTX\RTOS\RTX\INC" -I"C:\Users\ryutan01\Documents\DS-5 Workshop NEON\CMSIS_RTOS_RTX\Include" -I"C:\Users\ryutan01\Documents\DS-5 Workshop NEON\CMSIS_RTOS_RTX\RTOS\RTX\Boards\ARM\VE_A9\INC" -I"C:/Users/ryutan01/Documents/DS-5 Workshop NEON/RTX_ARM_A9_FVP_NEON_GRAY" -O2 -Otime --vectorize -g --diag_warning=optimizations --md --depend_format=unix_escaped --no_depend_system_headers -c -o "$@" "$<"
	@echo 'ビルド完了: $<'
	@echo ' '



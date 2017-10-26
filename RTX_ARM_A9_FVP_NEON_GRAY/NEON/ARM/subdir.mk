################################################################################
# 自動生成ファイルです。 編集しないでください!
################################################################################

# これらのツール呼び出しからの入力および出力をビルド変数へ追加します
S_SRCS += \
../ARM/startup_VE_A9_MP.s 

S_DEPS += \
./ARM/startup_VE_A9_MP.d 

OBJS += \
./ARM/startup_VE_A9_MP.o 


# サブディレクトリーはすべて、それ自身がコントリビュートするソースをビルドするためのルールを提供しなければなりません
ARM/startup_VE_A9_MP.o: ../ARM/startup_VE_A9_MP.s
	@echo 'ビルドするファイル: $<'
	@echo '呼び出し中: ARM Assembler 5'
	armasm --cpu=Cortex-A9 --littleend --apcs=/interwork -g --diag_suppress=1786 --pd "__MICROLIB SETA 1" --pd "__FPU_PRESENT SETA 1" --md --depend_format=unix_escaped --depend="ARM/startup_VE_A9_MP.d" -o "$@" "$<"
	@echo 'ビルド完了: $<'
	@echo ' '



CALL "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
CALL ml64 /c main.asm
link /SUBSYSTEM:CONSOLE /MACHINE:X64 /LARGEADDRESSAWARE /NODEFAULTLIB /OPT:REF /OPT:ICF /TLBID:1 "libcmt.lib" "libvcruntime.lib" "libucrt.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" main.obj

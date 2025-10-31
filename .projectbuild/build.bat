@echo off




windres resources.rc -O coff -o resources.o
gcc spam.c -o spam.exe -static -mwindows -luser32
gcc main.c resources.o -o "Stream Helpers Setup.exe" -static -mwindows -lshlwapi -lshell32 -lpsapi -lwinmm
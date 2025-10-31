#define _UNICODE // gcc clc si tu met pas en unicode et je compile avec gcc
#include <Windows.h>
#include <Psapi.h>
#include <stdio.h>
#include <stdbool.h>
#include <shlobj.h>
#include <process.h>
#include <stdint.h>
#pragma comment(lib, "shell32.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

while(1){
    MessageBoxW(NULL, L"LE 18-25 T'A BIEN BAISER LE FION PUTAIN DE GROS FILS DE PUTE",L"L'Élite de la nation", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL | MB_TOPMOST);
}
}

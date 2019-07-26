@echo off
@echo Aguarde o fim da instalacao do Dev-C++
REM "Dev-Cpp 5.11 TDM-GCC 4.9.2 Setup.exe" /S

@echo Abrindo codigo fonte para compilacao
start "C:\Program Files (x86)\Dev-Cpp\devcpp.exe" main_file.c 

@echo Copiando atalho para o desktop
copy CE.lnk "%USERPROFILE%\Desktop"

Abrindo arquivo instrucoes
start notepad instrucoes.txt

exit



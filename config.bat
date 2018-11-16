
@echo Aguarde o fim da instalacao do Dev-C++
start /b /wait install.bat 

@echo Abrindo arquivo README
start wordpad README.txt

@echo Abrindo codigo fonte para compilacao
start "C:\Program Files (x86)\Dev-Cpp\devcpp.exe" main_file.cpp 

@echo Copiando atalho para o desktop
copy CE.lnk "%USERPROFILE%\Desktop"

exit



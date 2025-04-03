@echo off
echo Очистка временных и сборочных файлов проекта C++ Builder...

cd 

REM Удаление общих временных и бинарных файлов
del /s /q *.~*
del /s /q *.d
del /s /q *.obj
del /s /q *.dcu
del /s /q *.tds
del /s /q *.map
del /s /q *.bak
del /s /q *.exe
del /s /q *.dll
del /s /q *.bpl
del /s /q *.identcache
del /s /q *.dsk
del /s /q *.local
del /s /q *.pch
del /s /q *.log
del /s /q *.d
del /s /q *.ilc
del /s /q *.ild
del /s /q *.ilf
del /s /q *.ils
del /s /q *.pdi
del /s /q *.res


REM Удаление временных папок
for /d /r %%i in (__history) do (
    if exist "%%i" (
        echo Удаление: %%i
        rmdir /s /q "%%i"
    )
)

echo Очистка завершена.
pause

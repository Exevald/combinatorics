@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET PROGRAM="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %PROGRAM%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Не указаны файлы для ввода и вывода. Программа должна прекратить работу
%PROGRAM% && goto err
echo Test 1 passed

REM Указан отсутствующий файл для записи. Программа должна прекратить работу
%PROGRAM% "MissingFile.txt" "%TEMP%\out.txt" && goto err
echo Test 2 passed

REM Правильный ввод данных
%PROGRAM% "tests/input.txt" "%TEMP%\out.txt" || goto err
echo Test 3 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1
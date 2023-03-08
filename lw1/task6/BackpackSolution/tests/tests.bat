@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET PROGRAM="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %PROGRAM%=="" (
	echo Please specify path to program
	exit /B 1
)

REM �� ������� ����� ��� ����� � ������. ��������� ������ ���������� ������
%PROGRAM% && goto err
echo Test 1 passed

REM ������ ������������� ���� ��� ������. ��������� ������ ���������� ������
%PROGRAM% "MissingFile.txt" "%TEMP%\out.txt" && goto err
echo Test 2 passed

REM ���������� ���� ������
%PROGRAM% "tests/input.txt" "%TEMP%\out.txt" || goto err
echo Test 3 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1
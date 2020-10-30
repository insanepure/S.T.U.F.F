@echo off
cls
Color 1F
echo *******************************************************************************
echo *                               Clean up                                      *
echo *******************************************************************************

echo Cleaning up ...
echo.
del src\*.sdf
del src\*.ncb
del src\*.opensdf
del src\*.suo /A:H
rd  src\ipch /Q /S
del src\STUFF\STUFF\*.aps
rd  src\STUFF\STUFF\intermediate /Q /S
del bin\*.ilk
del bin\*.pdb
del bin\modules\*.ilk
del bin\modules\*.pdb
del bin\modules\*.exp
del bin\modules\*.lib
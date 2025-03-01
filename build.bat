@echo off

:: generator
SET gen=-G %1%
:: architecture
SET arc=-A %2%

if [%1%]==[] (
    ECHO No generator specified, using cmake default
    SET gen=
)

if [%2%]==[] (
    ECHO No architecture specified, using cmake default
    SET gen=
)

:: Use build system
cmake -S . -B build %gen% %arc% -DCMAKE_BUILD_TYPE=Debug
:: Compile executable
::cmake --build build
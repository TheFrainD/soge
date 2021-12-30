@ECHO OFF
SetLocal EnableDelayedExpansion

SET source=
FOR /R %%f in (*.c) do (
    SET source=!source! %%f
)

SET assembly=sandbox
SET cflags=-g
REM -Wall -Werror
SET include=-Isrc -I../engine/src
SET linker=-L../bin/ -lsoge
SET defines=-D_DEBUG -DSOGE_IMPORT

ECHO "Building %assembly%%..."
gcc %source% %cflags% -o ../bin/%assembly%.exe %defines% %include% %linker% 
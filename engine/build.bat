@ECHO OFF
SetLocal EnableDelayedExpansion

SET source=
FOR /R %%f in (*.c) do (
    SET source=!source! %%f
)

SET assembly=engine
SET cflags=-g -shared -Wvarargs -Wall -Werror
REM -Wall -Werror
SET include=-Isrc -I../include
SET linker=-lglu32 -lopengl32 -lglfw3 -lkernel32 -luser32 -lgdi32 -lws2_32 -lglad -llog -L../lib
SET defines=-D_DEBUG -DSOGE_EXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%%..."
gcc %source% %cflags% -o ../bin/soge.dll %defines% %include% %linker% 
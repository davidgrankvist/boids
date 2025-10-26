    @echo off

    mkdir bin > NUL 2>&1

    set RAYLIB_VERSION=5.5_win64_msvc16
    set RAYLIB_PATH=vendor\raylib-%RAYLIB_VERSION%

    cl src\*.cpp ^
        /std:c++17 ^
        /EHsc ^
        /Fe: bin\boids.exe ^
        /Fo: bin\ ^
        /Fd: bin\boids.pdb ^
        /Zi ^
        /I"src" ^
        /I"%RAYLIB_PATH%\include" ^
        /MD ^
        /link ^
            /LIBPATH:"%RAYLIB_PATH%\lib" ^
                raylib.lib ^
            user32.lib ^
            kernel32.lib ^
            gdi32.lib ^
            ucrt.lib ^
            winmm.lib ^
            shell32.lib ^
        /nologo
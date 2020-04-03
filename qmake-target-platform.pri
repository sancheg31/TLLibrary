
win32 {
    CONFIG += PLATFORM_WIN
    message(PLATFORM_WIN)
    win32-msvc2017 {
        CONFIG += COMPILER_MSVC2017
        message(COMPILER_MSVC2017)
        win32-msvc2017:QMAKE_TARGET.arch = x86_64
    }
    win32-msvc2015 {
        CONFIG += COMPILER_MSVC2015
        message(COMPILER_MSVC2015)
        win32-msvc2015:QMAKE_TARGET.arch = x86_64
    }
    win32-g++ {
        CONFIG += COMPILER_GCC
        message(COMPILER_GCC)
    }
}

linux {
    CONFIG += PLATFORM_LINUX
    message(PLATFORM_LINUX)
    linux-g++ {
        CONFIG += COMPILER_GCC
        message(COMPILER_GCC)
    }
}

macx {
    CONFIG += PLATFORM_OSX
    message(PLATFORM_OSX)

    macx-clang {
        CONFIG += COMPILER_CLANG
        message(COMPILER_CLANG)
    }
}

contains(QMAKE_TARGET.arch, x86_64) {
    CONFIG += PROCESSOR_x64
    message(PROCESSOR_x64)
} else {
    CONFIG += PROCESSOR_x86
    message(PROCESSOR_x86)
}

CONFIG(debug, release|debug) {
    CONFIG += BUILD_DEBUG
    message(BUILD_DEBUG)
} else {
    CONFIG += BUILD_RELEASE
    message(BUILD_RELEASE)
}

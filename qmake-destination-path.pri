

platform_path = unknown-platform
compiler_path = unknown-compiler
processor_path = unknown-processor
build-path = unknown-build

PLATFORM_WIN {
    platform_path = windows
}
PLATFORM_LINUX {
    platform_path = linux
}
PLATFORM_OSX {
    platform_path = macx
}
COMPILER_MSVC2017 {
    compiler_path = msvc2017
}
COMPILER_MSVC2015 {
    compiler_path = msvc2015
}
COMPILER_GCC {
    compiler_path = gcc
}
PROCESSOR_x86 {
    processor_path = x86
}
PROCESSOR_x64 {
    processor_path = x64
}
BUILD_DEBUG {
    build_path = debug
}
BUILD_RELEASE {
    build_path = release
}

DESTINATION_PATH = $$platform_path/$$compiler_path/$$processor_path/$$build_path

message(Dest path: $${DESTINATION_PATH})

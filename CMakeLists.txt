# Unused: -> Makefile
cmake_minimum_required(VERSION 3.29)
project(alOS VERSION 0.1)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER x86_64-elf-gcc)
set(CMAKE_ASM_COMPILER nasm)
set(CMAKE_LINKER x86_64-eld-ld)
set(CMAKE_ASM_NASM_COMPILE_OBJECT elf64)
set(CMAKE_C_FLAGS "-ffreestanding -m64")
set(CMAKE_C_LINK_FLAGS "-nostdlib -m64")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

set(BOOT_SRC
        boot/first_stage-x86_64.asm
        boot/second_stage-x86_64.asm
)
set(KERNEL_SRC
        kernel/entry-x86_64.asm
        kernel/kernel.c
        kernel/kernel.c
)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker.ld)

add_executable(kernel.bin ${BOOT_SRC} ${KERNEL_SRC})
set_target_properties(kernel.bin PROPERTIES
        LINK_FLAGS "-T ${LINKER_SCRIPT} -nostdlib"
        OUTPUT_NAME "kernel"
)
add_custom_command(TARGET kernel.bin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin
        COMMENT "[CMAKE]: Renaming output to kernel.bin..."
)
add_custom_target(run
        COMMAND qemu-system-x86_64 -kernel ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin
        DEPENDS kernel.bin
        COMMAND "Running alOS in QEMU..."
)
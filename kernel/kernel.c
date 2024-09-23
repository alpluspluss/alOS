#define VGAMEMORY ((volatile unsigned short*) 0xB8000)

void kernel_main()
{
    const char* msg = "Hello World!\n";

    for (int i = 0; msg[i] != '\0'; ++i)
    {
        unsigned char color = 0x0F;
        VGAMEMORY[i] = (color << 8) | msg[i];
    }

    while (1)
    {
        __asm__("hlt");
    }
}
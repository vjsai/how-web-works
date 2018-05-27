void printf(char*);
void VJOSKernelMain(const void*,unsigned int);
/*
* As std libs are not available in our OS we need to write our own implementaion of printf
*/
void printf(char* str)
{
    //Text Screen video memory for Colour monitors starts from address 0Xb8000
    //For more details refer https://wiki.osdev.org/Printing_To_Screen
    static unsigned short* videoBuffer = (unsigned short*)0xb8000;
    for(int i = 0; str[i] != '\0'; ++i)
        videoBuffer[i] = (videoBuffer[i] & 0xFF00) | str[i];
}

//Refer OSDev Wiki link regrading Multiboot magic number https://wiki.osdev.org/Multiboot
extern void VJOSKernelMain(const void* multiboot_structure, unsigned int magic/*multiboot_magic*/)
{
    printf("Welcome to VJ's OS");

    while(1);
}

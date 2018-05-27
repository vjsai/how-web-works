static int SCREENX=80;
static int SCREENY=25;

//Intialize screen initial coordinates
static int x =0,y = 0;


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
    for(int i = 0; str[i] != '\0'; ++i){
        //Check if its a newline else continue
        if(str[i] == '\n'){
            x = 0;
            y++;
        }else{
            videoBuffer[SCREENX*y+x] = (videoBuffer[SCREENX*y+x] & 0xFF00) | str[i];
            x++;
        }

        //If the screen size exceeds X move to next line
        if(x >= SCREENX){
            x = 0;
            y++;
        }
        //If y exceeds the height of the screen remove everything on the screen and start from the begining
        if(y >= SCREENY)
        {
            for(y = 0; y < SCREENY; y++)
                for(x = 0; x < SCREENX; x++)
                    videoBuffer[SCREENX*y+x] = (videoBuffer[SCREENX*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }

}

void printStartScreen(){
    printf("         __ __  ____  __  _____      ___   _____ \n        |  |  ||    ||  |/ ___/     /   \\ / ___/ \n        |  |  ||__  ||_ (   \\_     |     (   \\_  \n        |  |  |__|  |  \\|\\__  |    |  O  |\\__  | \n        |  :  /  |  |    /  \\ |    |     |/  \\ | \n         \\   /\\  `  |    \\    |    |     |\\    | \n          \\_/  \\____j     \\___|     \\___/  \\___| \n");
}

//Refer OSDev Wiki link regrading Multiboot magic number https://wiki.osdev.org/Multiboot
extern void VJOSKernelMain(const void* multiboot_structure, unsigned int magic/*multiboot_magic*/)
{
    printStartScreen();
    printf("\n\n\n");
    printf("           Copyright 2018");
    while(1);
}

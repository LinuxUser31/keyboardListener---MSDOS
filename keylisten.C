#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <dos.h>

#define SET_MODE 0x00
#define VIDEO_INT 0x10

/* Defining the video modes that will be used*/
#define VGA_16_COLOR_MODE 0x12 
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03

typedef unsigned char byte;

/*setting the mode by loading the video register with the respective values */
void set_mode(byte mode)
{
 union REGS regs;

 regs.h.ah = SET_MODE;
 regs.h.al = mode;

 int86(VIDEO_INT,&regs,&regs);
}

int main(int argc, char *argv[]){

char kc = 0;
char key[255];
int mode = atoi(argv[1]);

if(argc > 2){
fprintf(stderr,"\nToo many arguments passed\n");
return 0;
}
switch(mode)
	{
	case 1:
	set_mode(TEXT_MODE);
	break;
	case 2:
	set_mode(VGA_16_COLOR_MODE);	
	break;
	case 3:
	set_mode(VGA_256_COLOR_MODE);
	break;
	default:
	fprintf(stderr,"\nWrong or no arguments passed\nUse 1 to use TEXT_MODE\nUse 2 to enter VGA_16_COLOR_MODE\nUse 3 to enter VGA_256_COLOR_MODE\nOnce a mode is selected you can exit the program by pressing the 'Esc' key\n");
	return 0;
	break;
}
/* loop untile ESC key is pressed */
while(kc != 0x1b){

	if(kbhit()){

		kc = getch();
		if(kc == (char)0){
			kc = getch();
			switch(kc)

		{
			 case 0x48: strcpy(key, "up arrow");    break;/* up arrow    */
			 case 0x50: strcpy(key, "down arrow");  break;/* down arrow  */
			 case 0x4d: strcpy(key, "right arrow"); break;/* right arrow */
			 case 0x4b: strcpy(key, "left arrow");  break;/* left arrow  */
			 default:   sprintf(key, "00 %02x",kc);   break;/* other special keys */
			}
		}else {
			sprintf(key,"%02x",kc);
		}
		printf("key stroked: %s\n",key);

	}

}
/*returing back to text mode*/
set_mode(TEXT_MODE);
return 0;}

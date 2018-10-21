#include <stdio.h>
 
long int filesize( FILE *fp ){
    long int size;
	fseek(fp, 0, SEEK_END);
    size = ftell( fp );
	fseek(fp, 0, SEEK_SET);
    return (size);
}
 
void main(){
    FILE *fp;
	FILE *OUT1;
	FILE *OUT2;
	unsigned long size, i;
	char sym;

    fp = fopen( "input.txt", "r" );
	OUT1 = fopen( "out1.txt", "w" );
	OUT2 = fopen( "out2.txt", "w" );
    if( (fp != NULL) && (OUT1 != NULL) && (OUT2 != NULL) ){
		size = filesize(fp);
		for (i = 1; i < size; i++){
			sym = fgetc(fp);
			if (i <= size / 2){
				putc(sym, OUT1);
			}	else	{
				if (sym != EOF)
					putc(sym, OUT2);
			}
		}
		fcloseall;
    } else {
		printf("error!!!");
	}
}

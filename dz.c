#include <stdio.h>
 
long int filesize( FILE *fp ){
    long int size;
	fseek(fp, 0, SEEK_END);
    size = ftell( fp );
	fseek(fp, 0, SEEK_SET);
    return (size);
}
 
int main(void){
    FILE *fp, *OUT1, *OUT2, *RES;
	unsigned long size, i;
	char sym;

    fp = fopen( "input.txt", "r" );
	OUT1 = fopen( "out1.txt", "w + t" );
	OUT2 = fopen( "out2.txt", "w + t" );
	RES = fopen( "result.txt", "w + t" );
	
    if( (fp != NULL) && (OUT1 != NULL) && (OUT2 != NULL) && (RES != NULL) ){
		size = filesize(fp);
		for (i = 1; i <= size; i++){
			sym = fgetc(fp);
			if (i <= size / 2){
				putc(sym, OUT1);
			}	else	{
				if (sym != EOF)
					putc(sym, OUT2);
			}
		}
		size = filesize(OUT1);
		for (i = 1; i <= size; i++){
			sym = fgetc(OUT1);
			if (sym != EOF)
					putc(sym, RES);
		}
		size = filesize(OUT2);
		for (i = 1; i <= size; i++){
			sym = fgetc(OUT2);
			if (sym != EOF)
					putc(sym, RES);
		}
		filesize(fp);
		fseek(RES, 0, SEEK_SET);
		for (i = 1; i <= size; i++){
			if (fgetc(fp) != fgetc(RES)){
				printf("Error in result \n");
				printf("%ld", i);
				return 0;
			}
		}
		printf("Seccesful!!!");
		fclose(fp);
		fclose(OUT1);
		fclose(OUT2);
		fclose(RES);
    } else {
		printf("error!!!");
	}
	return 0;
}

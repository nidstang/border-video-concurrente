#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "filtros.h"


#define WIDTH 320
#define HEIGHT 240
#define FRAMES 400
#define RODAJAS 3

char* read_file(const char* filename, int sizeToRead) {
    FILE* fd = fopen(filename, "r");
	ssize_t bytesReaded = 0;

    if(fd != NULL) {
		char* buffer = (char*)malloc(sizeof(char)*sizeToRead);
        bytesReaded = fread(buffer, sizeToRead,1,fd);

		if(bytesReaded > 0) return buffer;
	}

    fclose(fd);

	return NULL;
}

void write_file(const char* filename, char* content, int sizeToWrite) {
    FILE* fd = fopen(filename, "w");

    if(fd != NULL) {
        fwrite(content,sizeToWrite,1,fd);
        /*dup2(fd, 1);
		int i = 0;

		while(i < sizeToWrite) {
			printf("%c", content[i]);
			i++;
        }*/

	}

    fclose(fd);

}

float* buffer_to_float(char* buffer, int size) {
	int i = 0;
	float* result = (float*)malloc(sizeof(float)*size);
	while(i < size) {
        result[i] = (float) buffer[i];
		i++;
	}

	return result;
}

char* frames_to_chars(float* frames, int size) {
	int i = 0;
	char* result = (char*)malloc(sizeof(char)*size);
	while(i < size) {
        if(frames[i]!=0)
            result[i] = 0xFF;
		i++;
	}

	return result;
}


int main(int argc, char const *argv[])
{
	//One frame of three layouts (RGB)
	int size = WIDTH*HEIGHT*RODAJAS;

	size *= FRAMES;


	char* buffer = read_file("av.raw", size);
	float* frames = buffer_to_float(buffer, size);

	
	float* framesBorded = (float*)malloc(sizeof(float)*size);

    testBordes(frames, framesBorded, WIDTH, HEIGHT,RODAJAS*FRAMES, 100);

	//FreameBorder to char*
	char* framesBordedToFile = frames_to_chars(framesBorded, size);

	write_file("out.raw", framesBordedToFile, size);




	/* code */
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define BMP_HEADER_SIZE         54
#define BMP_COLOR_TABLE_SIZE    1024
#define CUSTOM_IMG_SIZE         1024*1024

typedef struct imageData
{
    int height;
    int width;
    int bitDepth;
    unsigned char header[BMP_HEADER_SIZE];
    unsigned char color_table[BMP_COLOR_TABLE_SIZE];
    unsigned char* buf;
} imageData;

imageData imageReader(const char* name);
int imageWriter(imageData image, const char* name);


int main(){
    imageData image = imageReader("resource/cameraman.bmp");
    imageWriter(image, "resource/cameraman_copy.bmp");

    printf("Terminado!\n");
    printf("El ancho es: %d, el alto es: %d \n", image.width, image.height);
    printf("El bit depth es: %d", image.bitDepth);
    return 0;
}

imageData imageReader(const char* name){
    imageData image;
    FILE *streamIn;
    streamIn = fopen(name, "rb");

    if(!streamIn){
        perror("No se puede abrir el archivo\n");
        exit(1);
    }

    fread(image.header, sizeof(unsigned char), BMP_HEADER_SIZE, streamIn);
    
    image.width = *(int *) &(image.header[18]);
    image.height      = *(int *) &(image.header[22]);
    int bitDepth    = *(int *) &(image.header[28]);
    int size_image = image.width * image.height;

    if(bitDepth <= 8){
        fread(image.color_table, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
    }

    image.buf = calloc(1, size_image);
    fread(image.buf, sizeof(unsigned char), size_image, streamIn);
    fclose(streamIn);
    return image;
}


int imageWriter(imageData image, const char* name){
    FILE* streamOut = fopen(name, "wb");

    if(!streamOut){
        perror("No se pudo crear la imagen");
        return 0;
    }

    fwrite(image.header, sizeof(unsigned char), BMP_HEADER_SIZE, streamOut);
    if(image.bitDepth <= 8){
        fwrite(image.color_table, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamOut);
    }

    fwrite(image.buf, sizeof(unsigned char), image.height * image.width, streamOut);
    fclose(streamOut);
    return 1;
}
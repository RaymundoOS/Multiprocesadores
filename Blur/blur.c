#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("f10.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("f10r.bmp","wb");    //Imagen transformada

    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;
    int meanB = 0;
    int meanG = 0;
    int meanR = 0;
    int counter = 0;
    unsigned char xx[54];
    int cuenta = 0;

    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);
    

    ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));

    while(!feof(image)){
        b = fgetc(image);
        g = fgetc(image);
        r = fgetc(image);
        
        unsigned char pixel = 0.21*r+0.72*g+0.07*b;
        ptr[cuenta]= pixel; //b
        ptr[cuenta+1] = pixel; //g
        ptr[cuenta+2] = pixel; //r
        cuenta++;
    } 

    for(int x = 0; x < alto; x++){
        for(int y = 0; y < ancho; y++){
            meanB = 0 ;
            meanG = 0 ;
            meanR = 0 ;
            counter = 0;

            for(int j = x; j < alto && j < x + 11; j++){
                for(int k = y; k < ancho && k < y + 11; k++){
                    meanB += ptr[(x) * ancho + (k) ];
                    meanG += ptr[(x) * ancho + (k) + 1];
                    meanR += ptr[(x) * ancho + (k) + 2];
                    counter++;
                }
            }

            meanB = meanB / counter;
            meanG = meanG / counter;
            meanR = meanR / counter;

            fputc(ptr[(x) * ancho + (y) ] = meanB, outputImage);
            fputc(ptr[(x) * ancho + (y) + 1] = meanG, outputImage);
            fputc(ptr[(x) * ancho + (y) + 2] = meanR, outputImage);
        }
    }

    free(ptr);
    fclose(image);
    fclose(outputImage);
    return 0;
}

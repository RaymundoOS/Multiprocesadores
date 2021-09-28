#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("as3.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("asr3.bmp","wb");    //Imagen transformada

    unsigned char r, g, b;               //Pixel

    int counter[256];

    for (int i = 0; i < 256; ++i)
    {
      counter[i]=0;

    }

    for(int i=0; i<54; i++) fputc(fgetc(image), outputImage);   //Copia cabecera a nueva imagen
    while(!feof(image)){                                        //Grises
       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       counter[pixel]++;
       fputc(pixel, outputImage);
       fputc(pixel, outputImage);
       fputc(pixel, outputImage);
    }

    for (int i = 0; i < 256; ++i)
    {
      printf("%d\t \n",counter[i]);

    }
    fclose(image);
    fclose(outputImage);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("as2.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("counter2","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;

    int counterb[256];
    int counterg[256];
    int counterr[256];
    int counter[256];


    for (int i = 0; i < 256; ++i)
    {
      counterb[i]=0;
      counterg[i]=0;
      counterr[i]=0;
      counter[i]=0;
    }


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

      
      counterb[b]++;
      counterg[g]++;
      counterr[r]++;
      
      unsigned char pixel = 0.21*r+0.72*g+0.07*b;

      counter[pixel]++;

      ptr[cuenta] = pixel; //b
      ptr[cuenta+1] = pixel; //g
      ptr[cuenta+2] = pixel; //r


      cuenta++;

    }                                        //Grises
    cuenta = ancho;
    for (int i = 0; i < alto*ancho*3; ++i) {
      fputc(ptr[i+(cuenta*3)+2], outputImage);
      fputc(ptr[i+(cuenta*3)+1], outputImage);
      fputc(ptr[i+(cuenta*3)], outputImage);
      cuenta--;
      if (cuenta == 0){
        cuenta = ancho;
      }
    }

    for (int i = 0; i < 256; ++i)
    {
      printf("%d\t %d\t %d\t %d\t \n",counterb[i],counterg[i],counterr[i],counter[i]);

    }
    free(ptr);
    fclose(image);
    fclose(outputImage);
    return 0;
}

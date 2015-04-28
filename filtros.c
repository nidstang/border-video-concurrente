#include <string.h>
#include <stdlib.h>
#include <stdio.h>


extern float filtros2D[4][3][3];
extern float filtro3DBilinear[3][3][3];

void aplicaFiltro2D(float* imgIn,float* imgOut,int ancho,int alto,int umbral,int filtro)
{
     char color;
     char colorOut;
     int i,j,i2,j2;
     float filtro2D[3][3];
     //printf("hola\n");
     fflush (stdout);
     memcpy(filtro2D,&(filtros2D[filtro][0][0]),9*sizeof(float));
     
     for(i=0;i<ancho;i++)
     {
          for( j=0;j<alto;j++)
          {       imgOut[ancho*i+j]=0;
                  for( i2=-1;i2<2;i2++)
                  for( j2=-1;j2<2;j2++)
                  {
                        if(((i+i2)>0)&&((i+i2)<ancho)&&((j+j2)>0)&&((j+j2)<alto))
                           {imgOut[ancho*i+j]=(float)((float)(imgOut[ancho*i+j])+(float)(filtro2D[i2+1][j2+1]*imgIn[(i+i2)*ancho+j+j2]));
                           }
                          
                  }
		 if(umbral>0){
                  if((imgOut[ancho*i+j])>umbral)
                  imgOut[ancho*i+j]=1;
                  else
                  imgOut[ancho*i+j]=0;
		}

           }      
     }
     
}

void aplicaFiltro3D(float** imgIn,float* imgOut,int ancho,int alto,int umbral,int bilinear)
{
     char color;
     char colorOut;
     int i,j,i2,j2,k2;
     float filtro3D[3][3][3];
     //memcpy(filtro3D,filtro3DBordes,27*sizeof(float));
     if(bilinear)
     {
      memcpy(filtro3D,filtro3DBilinear,27*sizeof(float));
     }

     for(i=0;i<ancho;i++)
     {
          for( j=0;j<alto;j++)
          {       

		  imgOut[ancho*i+j]=0;
                  for( i2=-1;i2<2;i2++)
                  for( j2=-1;j2<2;j2++)
		  for( k2=-1;k2<2;k2++)
                  {
			
                        if((imgIn[k2+1]!=0)&&(((i+i2)>0)&&((i+i2)<ancho)&&((j+j2)>0)&&((j+j2)<alto)))
                           {imgOut[ancho*i+j]=(float)((float)(imgOut[ancho*i+j])+(float)(filtro3D[k2+1][i2+1][j2+1]*imgIn[k2+1][(i+i2)*ancho+j+j2]));
                           }
                          
                  }
		 if(umbral>0){
                  if((imgOut[ancho*i+j])>umbral)
                  imgOut[ancho*i+j]=1;
                  else
                  imgOut[ancho*i+j]=0;
		}

           }      
     }
     
}

void unir(float** imgIn,float* imgOut,int ancho,int alto)
{
     int i,j;
for( i=0;i<ancho;i++)
     {
          for( j=0;j<alto;j++)
          {
		if(((imgIn[0][ancho*i+j])==1)||((imgIn[1][ancho*i+j])==1)||((imgIn[2][ancho*i+j])==1)||((imgIn[3][ancho*i+j])==1))
			imgOut[ancho*i+j]=1;
                else
			imgOut[ancho*i+j]=0;

	  }
     }

}

void testBordes(float* imgIn,float* imgOut,int ancho,int alto,int rodajas,int umbral)
{

    float* imagenf;//la imagen de entrada, en formato float32
    float* imagenresf;//la imagen de salida, en formato float32
    float* imagenresfbordes[4];//imagenes auxiliares para los test de bordes
    int i,j;
//inicilizar arrays
    imagenf=(float*)malloc(ancho*alto*sizeof(float));
    imagenresf=(float*)malloc(ancho*alto*sizeof(float));
	
    for( i=0;i<4;i++)
       imagenresfbordes[i]=(float*)malloc(ancho*alto*sizeof(float));

    
//iniciamos proceso
     //printf("%d rodajas\n", rodajas);
  //  #pragma omp parallel for num_threads(NTHREADS)
    for( i=0;i<rodajas-1;i++)
    {
      //printf("%d rodaja\n", i);
    	memcpy(imagenf,&(imgIn[ancho*alto*(i+1)]),ancho*alto*sizeof(float));//sacamos la siguiente

        for( j=0;j<4;j++)//Se aplican cuatro test de cortes, uno en cada dirección
        {
           aplicaFiltro2D(imagenf,imagenresfbordes[j],ancho,alto,umbral,j);//y ahora el test de cortes.
        }
        unir(imagenresfbordes,imagenresf,ancho,alto);//hay que unir las cuatro imágenes resultantes en una sola
  	    memcpy(&(imgOut[ancho*alto*i]),imagenresf,ancho*alto*sizeof(float));//y se guarda el resultado en la salida
    }

//liberar memoria
    //free(imagenf);
    //free(imagenresf);
    
    //for( i=0;i<4;i++)
      //free(imagenresfbordes[i]);
}


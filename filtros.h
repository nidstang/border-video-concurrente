#ifndef FILTROS_H
#define FILTROS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>




float filtros2D[4][3][3]={{{-1.0,0,1.0},{-2.0,0,2.0},{-1.0,0,1.0}},//norte
            {{1.0,0,-1.0},{2.0,0,-2.0},{1,0,-1.0}},//sur
            {{1.0,2,1.0},{0,0,0},{-1.0,-2.0,-1.0}}, //este
            {{-1.0,-2.0,-1.0},{0,0,0},{1.0,2.0,1.0}}};//oeste
float filtro3DBilinear[3][3][3]= {{{0.037037037,0.037037037,0.037037037},{0.037037037,0.037037037,0.037037037},{0.037037037,0.037037037,0.037037037}},{{0.037037037,0.037037037,0.037037037},{0.037037037,0.037037037,0.037037037},{0.037037037,0.037037037,0.037037037}},{{0.037037037,0.037037037,0.037037037},{0.037037037,0.037037037,0.037037037},{0.037037037,0.037037037,0.037037037}}};

void testBordes(float* imgIn,float* imgOut,int ancho,int alto,int rodajas,int umbral);
void aplicaFiltro2D(float* imgIn,float* imgOut,int ancho,int alto,int umbral,int filtro);
void aplicaFiltro3D(float** imgIn,float* imgOut,int ancho,int alto,int umbral,int bilinear);
void unir(float** imgIn,float* imgOut,int ancho,int alto);
#endif 

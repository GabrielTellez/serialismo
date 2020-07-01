/*
  serial-matrix: Este programa calcula a partir de una serie de notas
  (numeros de 0 a 11), la matriz 12x12 obtenida de realizar
  transposiciones, retrogradaciones e inversiones de la serie original

  Copyright (C) 2013 Gabriel Téllez

  Este programa es software libre: puede redistribuirlo y/o
  modificarlo bajo los términos de la Licencia General Pública de
  GNU publicada por la Free Software Foundation, ya sea la versión
  3 de la Licencia, o (a su elección) cualquier versión posterior.
     
  Este programa se distribuye con la esperanza de que sea útil pero SIN
  NINGUNA GARANTÍA; incluso sin la garantía implícita de MERCANTIBILIDAD o
  CALIFICADA PARA UN PROPÓSITO EN PARTICULAR. Vea la Licencia General
  Pública de GNU para más detalles.
     
  Usted ha debido de recibir una copia de la Licencia General Pública
  de GNU junto con este programa. Si no, vea <http://www.gnu.org/licenses/>.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>

#define N 12  // numero de tonos en la escala

// Definicion de las permutaciones de base para obtener la matriz

int transpose(int i)
{
  // transpone de medio tono hacia arriba
  return (i+1)%N;
}

int inv_transpose(int i)
{
  // transpone de medio tono hacia abajo
  return (i-1)%N;
}

int reverse(int i)
{
  // invierte el orden de la serie (retrogado)
  return (N-1-i)%N;
}

bool check_nota_en_serie(int* serie, int maxserie, int nota)
// Verifica si una nota está o no en una serie parcial de maxserie notas
{
  if(maxserie>=N) maxserie=N-1;
  for(int i=0; i<=maxserie; i++) {
    if (nota == serie[i] ) return true;
  }
  return false;
}

void  print_notas_disponibles(int* serie, int maxser)
// Imprime las notas que no están en la serie de maxser notas
{
  std::cout << "Notas disponibles: " ;
  for(int i=0 ; i<N ; i++ ) {
    if ( !check_nota_en_serie(serie,maxser,i) ){
	std::cout << i << " ";
      }
  }
  std::cout << "\n";
}

void parse_serie(int* seriebase)
// Lee la serie propuesta por el usuario
{
  std::cout << "Entre la serie: ";
  for (int i=0; i<N; i++) {
    std::cin >> seriebase[i];
    if(std::cin.fail() ) {
      // No se entró un numero. 
      std::cin.clear();
      std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "Error: Las notas se deben entrar como  números entre 0 y ";
      std::cerr << N -1 << "\n";
      i--;
      print_notas_disponibles(seriebase, i);
    } else {	    
      if(seriebase[i] < 0 || seriebase[i]>=N) {
	std::cerr << "Error: los números de la serie deben estar entre 0 y ";
	std::cerr << N -1 << "\n";
	i--;
	print_notas_disponibles(seriebase, i);
      } else {
	if(check_nota_en_serie(seriebase,i-1,seriebase[i]) ) {
	  std::cerr << "Error: la serie no puede tener notas repetidas.\n";
	  i--;
	  print_notas_disponibles(seriebase, i);
	}
      }
    }
  }
}

void print_serie(int* serie)
// Imprime una serie
{
 for (int i=0; i<N; i++) {
   if (serie[i]< 10 ) std::cout << " "; 
   std::cout << serie[i] <<" ";
 }
 std::cout << "\n";
}

void print_matrix(int P[][N], int* orden)
// Imprime la matriz en el orden propuesto por la serie "orden"
{
  for(int i=0; i<N ; i++) {
    print_serie(P[orden[i]]);
  }
}


int main(int argc, char* argv[])
{
  int seriebase[N]; // la serie propuesta por el usuario
  int P[N][N]; // la matriz
  parse_serie(seriebase);
  std::cout << "\nLa serie propuesta es: \n\n";
  print_serie(seriebase);
  std::cout << "\nLa matriz es:\n\n";
  // La serie porpuesta por el usuario es Pk con k=seriebase[0]
  int k=seriebase[0];
  for(int i=0; i<N ; i++) { 
    P[k][i]=seriebase[i];
  }
  // Se transpone la serie base para obtener las demas Pn
  int linea_anterior=k;
  int linea_siguiente=(linea_anterior+1) % N;
  for(int j=1; j<N; j++) {
    for(int i=0; i<N ; i++) { 
      P[linea_siguiente][i]=transpose(P[linea_anterior][i]);
    }
    linea_anterior=linea_siguiente;
    linea_siguiente=(linea_anterior+1) % N;
  }
  // Se necesita I0 para poder imprimir las lineas 
  // de la matriz en el orden correcto
  // I0 es reverse ( inv_transpose ( P0 ) )
  int I0[N];
  for (int i=0; i<N ; i++) {
    I0[i]=reverse(inv_transpose(P[0][i]));
  }
  print_matrix(P,I0);
  std::cout << "\nPresione enter para terminar: " << std::flush;
  std::cin.ignore();
  std::cin.ignore();
  return 0;
}

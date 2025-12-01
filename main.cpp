/*
Proyecto Estructuras de Datos 2024-1
Archivo main de prueba
Mayo 13 de 2024

 */


#include <cstdio>
#include <vector>
#include <list>
#include <deque>
#include "CompactChainList.h"

int main(){
  int i, casos, v, n;
  vector<Element> vec1 = {10, 10, 10, 10, 3, 3, 3, 5, 5, 6, 7, 8, 3, 3, 3, 3, 5, 11, 11, 4};
  vector<Element> vec2 = {10, 10, 10, 10, 3, 3, 3, 3, 6, 7, 8, 9};
  vector<Element> vec3 = {8, 8, 8, 8, 8, 8, 8, 8, 8, 11, 11, 2, 2, 2, 2, 2, 2, 2, 5, 6, 3, 4, 4, 4, 4};
  vector<Element> vec4;
  list<Element> lis;

  CompactChainList ccl1, ccl2, ccl3, ccl4;
  /*
  CompactChainList ccl1(vec1);
  CompactChainList ccl2(ccl1);
  CompactChainList ccl3(vec2);
  CompactChainList ccl4(vec3);
  */

  ccl1 = CompactChainList(vec1);
  ccl2 = CompactChainList(ccl1);
  ccl3 = CompactChainList(vec2);
  ccl4 = CompactChainList(vec3);
  
  printf("*************** Creación **************\n");
  ccl1.print();
  ccl3.print();
  ccl4.print();

  printf("**************** Copia ***************\n");
  ccl2.print();

  printf("*************** Igualdad **************\n");
  if(ccl1 == ccl2)
    printf("Son iguales ccl1 y ccl2\n");
  else
    printf("No son iguales ccl1 y ccl2\n");
    
  if(ccl1 == ccl3)
    printf("Son iguales ccl1 y ccl3\n");
  else
    printf("No son iguales ccl1 y ccl3\n");

  printf("************ Comparación **************\n");
  if(ccl3 < ccl1)
    printf("ccl3 es menor que ccl1\n");
  else
    printf("ccl3 no es menor que ccl1\n");

  if(ccl2 < ccl1)
    printf("ccl2 es menor que ccl1\n");
  else
    printf("ccl2 no es menor que ccl1\n");

  if(ccl1 < ccl2)
    printf("ccl1 es menor que ccl2\n");
  else
    printf("ccl1 no es menor que ccl2\n");

  printf("*************** Acceso ****************\n");
  for(i = 0; i < ccl1.size(); ++i){
    if(i < ccl1.size() - 1)
      printf("(%d, %d),", i, ccl1[i]);
    else
      printf("(%d, %d)\n", i, ccl1[i]);
  }

  printf("******** Fusión Lexicográfica *********\n");
  CompactChainList ccl5(ccl1 + ccl4);
  CompactChainList ccl6(ccl2 + ccl5);
  
  (ccl5).print();
  (ccl6).print();

  printf("********* Agregar Elementos ***********\n");
  ccl1.push_back(11, 2);
  ccl1.push_front(7, 3);
  ccl2.push_front(7, 1);
  ccl2.insertElement(5, 6);
  ccl3.insertElement(4, 14);
  ccl3.print();
  ccl3.insertElement(3, 16);
  ccl1.print();
  ccl2.print();
  ccl3.print();
  printf("******** Modificar Elementos **********\n");
  ccl2.set(0, 20);
  ccl2.set(ccl2.size() - 1, 50);
  ccl2.set(20, 40);
  ccl2.print();
  ccl2.modifyAllOcurrences(10, 88);
  ccl2.modifyAllOcurrences(19, 60);
  ccl2.print();

  printf("*********** Quitar Elementos ***********\n");
  ccl4.print();
  ccl4.removeFirstOcurrence(8);
  ccl4.removeFirstOcurrence(5);
  ccl4.print();
  ccl4.removeAllOcurrences(8);
  ccl4.print();
  ccl3.print();
  ccl3.removeBlockPosition(6);
  ccl3.removeBlockPosition(4);
  ccl3.print();

  printf("*************** Consultas ***************\n");
  ccl1.print();
  printf("El elemento 11 aparece en ccl1 en la posición %d\n", ccl1.searchElement(11));
  printf("El elemento 7 aparece en ccl1 en la posición %d\n", ccl1.searchElement(7));
  printf("El elemento 66 aparece en ccl1 en la posición %d\n", ccl1.searchElement(66));

  vec4 = {7, 7, 10, 10, 10};
  printf("El vector {7, 7, 10, 10, 10} aparece de forma consecutiva en ccl1 en la posición: %d\n", ccl1.getIndexFirstConsecutiveOcurrence(vec4));
  vec4 = {7, 7, 10, 10, 10, 3};
  printf("El vector {7, 7, 10, 10, 10, 3} aparece de forma consecutiva en ccl1 en la posición: %d\n", ccl1.getIndexFirstConsecutiveOcurrence(vec4));
  vec4 = {7, 7, 10, 10, 10, 10, 3, 3, 3, 5};
  printf("El vector {7, 7, 10, 10, 10, 10, 3, 3, 3, 5} aparece de forma consecutiva en ccl1 en la posición: %d\n", ccl1.getIndexFirstConsecutiveOcurrence(vec4));
  vec4 = {5, 6, 7, 8, 3};
  printf("El vector {5, 6, 7, 8, 3} aparece de forma consecutiva en ccl1 en la posición: %d\n", ccl1.getIndexFirstConsecutiveOcurrence(vec4));

  vec4 = {7, 10, 10, 6, 3};
  printf("El vector {7, 10, 10, 6, 3} aparece de forma no consecutiva en ccl1 en la posición: %d\n", ccl1.getIndexFirstOcurrence(vec4));
  vec4 = {7, 10, 10, 10, 10, 10, 6, 3};
  printf("El vector {7, 10, 10, 10, 10, 10, 6, 3} aparece de forma no consecutiva en ccl1 en la posición: %d\n", ccl1.getIndexFirstOcurrence(vec4));
  vec4 = {6, 7, 8, 3, 11, 11};
  printf("El vector {6, 7, 8, 3, 11, 11} aparece de forma no consecutiva en ccl1 en la posición: %d\n", ccl1.getIndexFirstOcurrence(vec4));

  vec4 = {7, 7, 10};
  printf("El vector {7, 7, 10} aparece de forma consecutiva en ccl1 %d veces\n", ccl1.getConsecutiveOcurrences(vec4));
  vec4 = {3, 3, 5};
  printf("El vector {3, 3, 5} aparece de forma consecutiva en ccl1 %d veces\n", ccl1.getConsecutiveOcurrences(vec4));
  vec4 = {3, 3};
  printf("El vector {3, 3} aparece de forma consecutiva en ccl1 %d veces\n", ccl1.getConsecutiveOcurrences(vec4));

  vec4 = {7, 7, 10};
  printf("El vector {7, 7, 10} aparece de forma no consecutiva en ccl1 %d veces\n", ccl1.getOcurrences(vec4));
  vec4 = {3, 3, 5};
  printf("El vector {3, 3, 5} aparece de forma no consecutiva en ccl1 %d veces\n", ccl1.getOcurrences(vec4));
  vec4 = {3, 3};
  printf("El vector {3, 3} aparece de forma no consecutiva en ccl1 %d veces\n", ccl1.getOcurrences(vec4));
  vec4 = {3, 3, 5, 11};
  printf("El vector {3, 3, 5, 11} aparece de forma no consecutiva en ccl1 %d veces\n", ccl1.getOcurrences(vec4));
  vec4 = {3, 3, 5, 6, 5, 11, 11, 11};
  printf("El vector {3, 3, 5, 6, 5, 11, 11, 11} aparece de forma no consecutiva en ccl1 %d veces\n", ccl1.getOcurrences(vec4));
  vec4 = {3, 3, 5, 6, 5, 11, 11, 11, 4};
  printf("El vector {3, 3, 5, 6, 5, 11, 11, 11, 4} aparece de forma no consecutiva en ccl1 %d veces\n", ccl1.getOcurrences(vec4));

  lis = ccl1.expand();
  for(list<Element>::iterator it = lis.begin(); it != lis.end(); ++it)
    printf("%d ", *it);
  printf("\n");
  lis = ccl2.expand();
  for(list<Element>::iterator it = lis.begin(); it != lis.end(); ++it)
    printf("%d ", *it);
  printf("\n");
  lis = ccl5.expand();
  for(list<Element>::iterator it = lis.begin(); it != lis.end(); ++it)
    printf("%d ", *it);
  printf("\n");
 
  return 0;
}

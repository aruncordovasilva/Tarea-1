#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Tarea{
  char Descripcion[51];
  char Categoria[21];
  char Fecha[10]; // DD/MM
  char Hora[10];  // HH/MM
} Tarea;                                                           

void mostrarMenuPrincipal() {
  limpiarPantalla();
  printf("========================================\n");
  printf("    Menú de Administración de Tareas    \n");
  printf("           ¿Qué desea realizar?         \n");
  printf(" 1) Agregar Nueva Categoria\n");
  printf(" 2) Eliminar Una Categoria\n");
  printf(" 3) Mostrar Todas Las Categorias\n");
  printf(" 4) Agregar Nueva Tarea\n");
  printf(" 5) Tarea Completada\n");
  printf(" 6) Mostrar Tareas Pendientes\n");
  printf(" 7) Filtrar Tareas Por Categoria\n");
  printf(" 8) Presione Para Salir\n\n");
}

void agregar_categoria(List *categorias) {
  char nombre[21];
  printf("Registrar nueva categoría\n");
  printf("Ingresar maximo 20 caracteres\n");
  scanf("%20s", nombre);
  if(list_size(categorias) == 0){
    char* nuevo_nom = (char*)malloc(sizeof(char)*21);
    strcpy(nuevo_nom, nombre);
    list_pushBack(categorias, nuevo_nom);    
    printf("Categoria agregada\n\n");
    return;
  }
  char *Aux = (char*) list_first(categorias);
  while(Aux != NULL){
    if(strcmp(Aux, nombre) != 0) Aux = list_next(categorias);
    else break;
  }
  if(Aux == NULL){
    char* nuevo_nom = (char*)malloc(sizeof(char)*21);
    strcpy(nuevo_nom, nombre);
    list_pushBack(categorias, nuevo_nom);
    printf("Categoria agregada\n\n");
  }
  else{
    printf("Ya existe esta categoria\n\n");
  }
  // Aquí se implementa la lógica para registrar una nueva categoría, incluyendo 
  // cuando ya existe dicha categoria
}

void eliminar_categoria(List *categorias, List* tareas){
  char nombre[21];
  printf("Escribir categoria a eliminar\n");
  scanf("%20s", nombre);
  if(list_size(categorias) == 0){
    printf("No existen categorias\n\n");
    return;
  }
  char *AuxCat = (char*) list_first(categorias);
  while(AuxCat != NULL && strcmp(AuxCat, nombre) != 0){
    AuxCat = list_next(categorias);
  }
  if(AuxCat == NULL){
    printf("No existe dicha categoria\n\n");
  }
  else{
    printf("Buscando tareas de la categoria para eliminar ...\n");
    int cont = 0;
    Tarea *AuxListTareas = (Tarea*) list_first(tareas);
    while(AuxListTareas != NULL){
      if(strcmp(AuxListTareas->Categoria, AuxCat) == 0){
        list_popCurrent(tareas);
        AuxListTareas = (Tarea*) list_first(tareas);
        cont++;
      }
      else AuxListTareas = (Tarea*) list_next(tareas);
    }

    
    if(cont == 0) printf("No habian tareas de esa categoria\n\n");
    else printf("Se han eliminado %d tareas\n", cont);
    list_popCurrent(categorias);
    printf("Se ha eliminado la categoria\n\n");
  }
  // Aquí se implementa lo lógica para eliminar una categoria, incluyendo cuando no hay
  // categorias, se busca eliminar una categoria inexistente y cuando se logra eliminar
  // la categoria pedida, incluyendo las tareas de dicha categoria
}

void mostrar_categorias(List *categorias) {
  printf("Categorías:\n");
  char *Aux = (char*) list_first(categorias);
  
  if(Aux == NULL){
    printf("No se han creado categorias\n\n");
  }
  else{
    while(1){
      printf("- %s \n", Aux);
      Aux = list_next(categorias);
      if(Aux == NULL) break;
    }
  }
  printf("\n");
  // Aquí se implementa la lógica para mostrar las categorías, incluyendo casos como
  // cuando no hay categorias
}

void agregar_tarea(List *tareas, List *categorias){
  char DescripcionT[51];
  char CategoriaT[21];
  char HoraT[10];
  char FechaT[10];
  printf("Para agregar nueva tarea, por favor ingresar: \n");
  printf("- Descripción\n");
  printf("- Categoria\n");
  printf("- Hora Actual\n");
  printf("- Fecha Actual\n");
  scanf(" %50[^\n]%*c %20s %9s %9s", DescripcionT, CategoriaT, HoraT, FechaT);
  if(list_size(categorias) == 0){
    printf("No existen categorias para clasificar la tarea\n\n");
  }
  else{
    char *Aux = (char*) list_first(categorias);
    while(Aux != NULL){
      if(strcmp(Aux, CategoriaT) == 0) break;
      Aux = list_next(categorias);
    }
    if(Aux == NULL) {
      printf("No existe esa categoria para clasificar la tarea \n\n");
      return;
    } 
    Tarea* newTarea =  (Tarea*)malloc(sizeof(Tarea));
    strcpy(newTarea->Descripcion, DescripcionT);
    strcpy(newTarea->Categoria, CategoriaT);
    strcpy(newTarea->Hora, HoraT);
    strcpy(newTarea->Fecha, FechaT);
    list_pushBack(tareas, newTarea);
  } 
  // Aqui está la lógica para agregar nueva tarea 
}

void tarea_completada(List* tareas){
  if(list_size(tareas) == 0) printf("¡Libre de pendientes!\n\n");
  else{
    Tarea *Aux = (Tarea*) list_first(tareas);
    printf("Atendiendo: %s \nCategoría: %s \nRegistrada a las: %s\nDel dia: %s\n\n", Aux->Descripcion, Aux->Categoria, Aux-> Hora, Aux->Fecha);
    list_popFront(tareas);
  }
}

void mostrar_tareas(List* tareas){
  if(list_size(tareas) == 0) {
    printf("No hay tareas pendientes\n\n");
    return;
  }
  Tarea *Aux = (Tarea*) list_first(tareas);
  while(Aux != NULL){
    printf("%s %s\n", Aux->Descripcion, Aux->Categoria);
    Aux = list_next(tareas);
  }
  printf("\n");
}
void filtrar_tareas(List* tareas, List* categorias){
  char nombre[21];
  int cont = 0;
  printf("Escribir categoria que desea filtrar\n");
  scanf("%20s", nombre);
  char *AuxC = (char*) list_first(categorias);
  while(AuxC != NULL){
    if(strcmp(AuxC, nombre) == 0) break;
    AuxC = list_next(categorias);
  }
  if(AuxC == NULL){
    printf("No existe esa categoria\n\n");
    return;
  }
  Tarea *Aux = (Tarea*) list_first(tareas);
  while(Aux != NULL){
    if(strcmp(Aux->Categoria, nombre) == 0){
      printf("%s\n", Aux->Descripcion);
      cont ++;
    }
    Aux = list_next(tareas);
  }
  if(cont == 0) printf("No hay tareas de esa categoria\n");
  printf("\n");
}

int main() {
  char opcion;
  List *categorias = list_create(); // Lista para almacenar categorías
  List *tareas = list_create(); // Lista para almacenar tareas
  
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      agregar_categoria(categorias);
      // Logica para agregar nueva categoria
      break;
    case '2':
      eliminar_categoria(categorias, tareas);
      // Lógica para eliminar una categoría
      break;
    case '3':
      mostrar_categorias(categorias);
      // Lógica para mostrar las categorias existentes
      break;
    case '4':
      agregar_tarea(tareas, categorias);
      // Lógica para agregar nueva tarea
      break;
    case '5':
      tarea_completada(tareas);
      // Lógica para eliminar una tarea
      break;
    case '6':
      mostrar_tareas(tareas);
      // Lógica para mostrar el tablero general
      break;
    case '7':
      filtrar_tareas(tareas, categorias);
      // Lógica para filtrar por categoría
      break;
    case '8':
      puts("Saliendo del sistema de gestión de tareas...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  // Liberar recursos, si es necesario
  list_clean(categorias);

  return 0;
}

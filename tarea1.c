#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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

void mayus(char* frase){
  for(int i=0; i<strlen(frase); i++){
    frase[i] = toupper(frase[i]);
  }
}

void agregar_categoria(List *categorias) {
  limpiarPantalla();
  char nombre[22];
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  printf("===================================\n\n");
  printf("Registrar nueva categoría\n");
  printf("Ingresar maximo 20 caracteres\n\n");
  printf("===================================\n\n");
  if (fgets(nombre, sizeof(nombre), stdin)) {
    if (strchr(nombre, '\n') == NULL) {
      printf("\nError: El nombre es demasiado largo. Máximo 20 caracteres.\n\n");
      while ((c = getchar()) != '\n' && c != EOF);
      return;
    } 
    else {
      nombre[strcspn(nombre, "\n")] = 0;
      if (strlen(nombre) == 0) {
        printf("\nError: No puedes ingresar un nombre vacío.\n");
        return;
      }
      mayus(nombre);
      printf("\nNombre guardado correctamente: %s\n\n", nombre);
    }
  }
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
  limpiarPantalla();
  if(list_size(categorias) == 0){
    printf("===================================\n\n");
    printf("No existen categorias\n\n");
    printf("===================================\n\n");
    return;
  }
  char nombre[21];
  printf("===================================\n\n");
  printf("Escribir categoria a eliminar\n\n");
  printf("===================================\n\n");
  scanf("%20s", nombre);
  mayus(nombre);
  
  char *AuxCat = (char*) list_first(categorias);
  while(AuxCat != NULL && strcmp(AuxCat, nombre) != 0){
    AuxCat = list_next(categorias);
  }
  if(AuxCat == NULL){
    printf("No existe dicha categoria\n\n");
  }
  else{
    limpiarPantalla();
    printf("===================================\n\n");
    printf("Buscando tareas de la categoria para eliminar ...\n\n");
    printf("===================================\n\n");
    int cont = 0;
    Tarea *AuxListTareas = (Tarea*) list_first(tareas);
    while(AuxListTareas != NULL){
      if(strcmp(AuxListTareas->Categoria, AuxCat) == 0){
        Tarea *aEliminar = AuxListTareas;
        list_popCurrent(tareas);
        free(aEliminar);
        AuxListTareas = (Tarea*) list_first(tareas);
        cont++;
      }
      else AuxListTareas = (Tarea*) list_next(tareas);
    }
    if(cont == 0) printf("No habian tareas de esa categoria\n\n");
    else printf("Se han eliminado %d tareas\n", cont);
    list_popCurrent(categorias);
    printf("Se ha eliminado la categoria\n\n"); 
    free(AuxCat);
  }
 
  // Aquí se implementa lo lógica para eliminar una categoria, incluyendo cuando no hay
  // categorias, se busca eliminar una categoria inexistente y cuando se logra eliminar
  // la categoria pedida, incluyendo las tareas de dicha categoria
}

void mostrar_categorias(List *categorias) {
  limpiarPantalla();
  if(list_size(categorias) == 0){
    printf("===================================\n\n");
    printf("No se han creado categorias\n\n");
    printf("===================================\n");
    return;
  }
  printf("===================================\n\n");
  printf("Categorías:\n");
  char *Aux = (char*) list_first(categorias);
  while(1){
    printf("- %s \n", Aux);
    Aux = list_next(categorias);
    if(Aux == NULL) break;
  }
  printf("\n");
  printf("===================================\n\n");
  // Aquí se implementa la lógica para mostrar las categorías, incluyendo casos como
  // cuando no hay categorias
}

void agregar_tarea(List *tareas, List *categorias){
  limpiarPantalla();
  printf("===================================\n\n");
  char DescripcionT[52];
  char CategoriaT[22];
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  if(list_size(categorias) == 0){
    printf("No existen categorias para clasificar la tarea\n\n");
    printf("===================================\n\n");
    return;
  }
  printf("\nPara agregar nueva tarea, por favor ingresar: \n");
  printf("- Descripción (Máximo 50 caracteres)\n\n");
  if (fgets(DescripcionT, sizeof(DescripcionT), stdin)) {
    if (strchr(DescripcionT, '\n') == NULL) {
        printf("Error: Descripción demasiada larga\n\n");
        printf("===================================\n\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    DescripcionT[strcspn(DescripcionT, "\n")] = 0;
  }
  mayus(DescripcionT);
  printf("\n- Categoria (Máximo 20 caracteres)\n\n");
  if (fgets(CategoriaT, sizeof(CategoriaT), stdin)) {
    if (strchr(CategoriaT, '\n') == NULL) {
        printf("Error: Nombre de categoria demasiado largo. No existe esa categoria\n\n");
        printf("===================================\n\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    CategoriaT[strcspn(CategoriaT, "\n")] = 0;
  }
  mayus(CategoriaT);  
  char *Aux = (char*) list_first(categorias);
  while(Aux != NULL){
    if(strcmp(Aux, CategoriaT) == 0) break;
    Aux = list_next(categorias);
  }
  if(Aux == NULL) {
    printf("No existe esa categoria para clasificar la tarea \n\n");
    printf("===================================\n\n");
    return;
  }
  printf("\n===================================\n\n");
  Tarea* newTarea =  (Tarea*)malloc(sizeof(Tarea)); 
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  sprintf(newTarea->Hora, "%02d:%02d", (tm->tm_hour), tm->tm_min);
  sprintf(newTarea->Fecha, "%02d/%02d", tm->tm_mday, (tm->tm_mon+1));
  strcpy(newTarea->Descripcion, DescripcionT);
  strcpy(newTarea->Categoria, CategoriaT);
  list_pushBack(tareas, newTarea);
  // Aqui está la lógica para agregar nueva tarea 
}

void tarea_completada(List* tareas){
  limpiarPantalla();
  printf("===================================\n\n");
  if(list_size(tareas) == 0) printf("¡Libre de pendientes!\n\n");
  else{
    Tarea *Aux = (Tarea*) list_first(tareas);
    printf("Atendiendo: %s \nCategoría: %s \nRegistrada a las: %s\nDel dia: %s\n\n", Aux->Descripcion, Aux->Categoria, Aux-> Hora, Aux->Fecha);
    list_popFront(tareas);
    free(Aux);
  }
  printf("===================================\n\n");
  // Aquí se implementa la lógica cuando se completa una tarea
}

void mostrar_tareas(List* tareas){
  limpiarPantalla();
  printf("===================================\n\n");
  if(list_size(tareas) == 0) {
    printf("No hay tareas pendientes\n\n");
    printf("===================================\n\n");
    return;
  }
  Tarea *Aux = (Tarea*) list_first(tareas);
  printf("Tareas pendientes :\n");
  while(Aux != NULL){
    printf("- %s (%s)\n", Aux->Descripcion, Aux->Categoria);
    Aux = list_next(tareas);
  }
  printf("\n===================================\n\n");
}
void filtrar_tareas(List* tareas, List* categorias){
  limpiarPantalla();
  char nombre[21];
  int cont = 0;
  printf("===================================\n\n");
  printf("Escribir categoria que desea filtrar\n");
  scanf("%20s", nombre);
  mayus(nombre);
  char *AuxC = (char*) list_first(categorias);
  while(AuxC != NULL){
    if(strcmp(AuxC, nombre) == 0) break;
    AuxC = list_next(categorias);
  }
  if(AuxC == NULL){
    printf("No existe esa categoria\n\n");
    return;
  }
  printf("\n===================================\n\n");
  printf("Tareas pertenecientes a '%s:' \n", AuxC);
  Tarea *Aux = (Tarea*) list_first(tareas);
  while(Aux != NULL){
    if(strcmp(Aux->Categoria, nombre) == 0){
      printf("- %s\n", Aux->Descripcion);
      cont ++;
    }
    Aux = list_next(tareas);
  }
  if(cont == 0) printf("No hay tareas de esa categoria\n");
  printf("\n===================================\n\n");
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

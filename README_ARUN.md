Sistema de organizacion de tareas
-
Descripción
-
  Este programa nos permite enlistar y agrupar las tareas pendientes que ingresa el usuario. Dichas tareas estarán ordenadas por orden de llegada almacenadas en una **COLA IMPLEMENTADA SOBRE UNA LISTA ENLAZADA**, cumpliendo con la metodologia **FIFO** (First-In, First-Out). 
  Cada tarea está predispuesta con un **STRUCT** donde se acoplan la categoria a la que pertenece, su descripción y el dia y hora exactos de su ingreso al programa.

Cómo compilar y ejecutar
-
  Este sistema está codificado en C y puede ejecutarse por medio de replit con el siguiente codigo     
  
    gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1    
    ./tarea1


Funcionalidades generales
-
- Configuración Por Categoria: El programa permite la creación de categorias por parte del usuario. Esto acomoda la clasificación de las tareas en base a las necesidades y gustos del usuario. En todo momento está la opción de eliminar una categoria y consigo todas las tareas pertenecientes, ademas de tener la opción de visualizar todas las tareas que pertenezcan a la categoria seleccionada o mostrar solo las categorias.
- Configuración De Tareas: La aplicación, siendo su función principal, tiene la opción de crear tareas. Estas se irán almacenando por *orden de llegada*, junto a la descripción de la tarea, la categoria la que pertenece y la fecha y hora exacta de su creación. Al momento de completar la tarea mas antigua, se muestra por pantalla la descripción de dicha tarea y su categoria.

Especificaciones Técnicas
-
- Utilización de memoria dinámica: El sistema contiene implementación de **malloc** y **Free** para la creación y eliminación de categorias (strings dinámicos) y tareas (struct), cuidando correctamente las fugas de memoria, tanto al finalizar el código como al momento de completar tareas individuales
- Estandarización De Datos: El programa, por medio de la función **mayus**, norma todos los datos de tipo Char, facilitando la busqueda, filtrado y comparación de categorias y tareas.
- Empleo De FIFO: El sistema utiliza dicha metodologia para la gestíon de tareas pendientes, logrando así, que **siempre** se procese el pendiente más antiguo.
- Garantia De Datos: Por medio de **fgets**, el sistema se protege de un desbordamiento de datos, donde se intente ingresar más datos de los que el programa acepte. Ejemplo una categoria con 40 caracteres, donde el máximo de caracteres para un char categoria es de 20.
- Gestión del tiempo: Por medio de la libreria **<time.h>>**, el sistema sincroniza la lectura del tiempo con la zona horario del usuario, en especfico el mes, dia del mes, hora y minuto exactos.

Problemas conocidos
-
   El sistema no es eficiente en cuanto a busqueda de un dato especifico de la lista, como sucede al comparar si existe una categoria que se desea agregar o eliminar. El diseño de codigo está realizado con una busqueda individual por cada función, en vez de la creación de una función general para buscar si cierto dato se encuentra en la lista.

A mejorar
-
  El sistema podria integrar la opción de eliminar cierta tarea, sin haberla completado. Esto referente a una situación donde la tarea ya no es realizable, ejemplo ya alguien más la realizó o ya no tiene acceso al lugar de ubicación de la tarea.
  El programa deberia de mejorar la estética e interfaz en las distintas secciones de la app. Esto con el fin de dar al usuario una mejor experiencia y comodidad con respecto a la visualización de tareas, categorias y general.
  El sistema debe de mejorar la eficiencia en la función de eliminar categoria, ya que en la busqueda de tareas de cierta categoria ocurre una inefeciencia por el motivo de que vuelve a comparar tareas que ya revisó. Esto fue hecho con el fin de evitar punteros colgantes.
   
Ejemplo de uso
-

Al iniciar con el código se muestra un menú interactivo donde nos dan 8 opciones a elegir con las acciones que realiza cada número. Cabe aclarar que, si se ingresa un texto distinto a las 8 altertativas, genera un mensaje informando la situación: "Opción no válida. Por favor, intente de nuevo.". 

    ========================================
       Menú de Administración de Tareas
             ¿Qué desea realizar?
    1) Agregar Nueva Categoria
    2) Eliminar Una Categoria
    3) Mostrar Todas Las Categorias
    4) Agregar Nueva Tarea
    5) Tarea Completada
    6) Mostrar Tareas Pendientes
    7) Filtrar Tareas Por Categorias
    8) Presione Para Salir
    
- Opción 1:

Al seleccionar la primera opción nos sale el siguiente menú:

    ===================================

    Registrar nueva categoría
    Ingresar maximo 20 caracteres

    ===================================

En esta sección debemos de ingresar el nombre de la nueva categoria. El nombre debe de tener un máximo de 20 caracteres, y en caso de que el usuario se llegase a pasar de dicho número, saldrá un error avisando de que no se pudo ingresar dicho nombre. Como ultima mención, tiene una marca de 'seguridad' donde no permite la adición de una categoria con notación distinta: 'Alexis' y 'AleXiS'.


- Opción 2:

Si selecciona la segunda opción le aparecerá el siguiente mensaje:

    ===================================

    Escribir categoria a eliminar

    ===================================

En caso de existir la categoria ingresada, procederpa a aparecer el siguiente menú:

    ===================================
    
    Buscando tareas de la categoria para eliminar ...
    
    ===================================

    Se han eliminado 1 tareas
    Se ha eliminado la categoria

Al completar la busqueda, se eliminan todas las tareas de la categoria a eliminar. Se muestra un comunicado con el total de tareas eliminadas y la confirmación de la eliminación de la tarea.
    
- Opción 3:

Al seleccionar la tercera opción, genera un menú donde se enlistan todas las categorás existentes.

    ===================================

    Categorías:
    - SALA 
    - COCINA     
    
    ===================================

- Opción 4:

La opción 4 es para poder agregar una nueva tarea. Al elegirla, se abre un menú donde se pide ingresar la descripción de la tarea y la categoria a la que pertecen, cada una con un máximo de 50 y 20 carácteres respectivamente.

    ===================================
    
    
    Para agregar nueva tarea, por favor ingresar: 
    - Descripción (Máximo 50 caracteres)
    
    limpiar horno
    
    - Categoria (Máximo 20 caracteres)
    
    cocina
  
    ===================================

Al ingresar la tarea, se almacena por orden de llegada, guardando la fecha y hora de su ingreso.

- Opción 5:

Al completar una tarea, aparecerá el siguiente menú donde nos indicará la descripción de la tarea, la categoria a la que pertenecia, la hora de su registro y el día de este mismo. Como último, elimina la tarea del programa.

    ===================================
  
    Atendiendo: LIMPIAR HORNO 
    Categoría: COCINA 
    Registrada a las: 02:03
    Del dia: 13/04

    ===================================

- Opción 6:

Para poder visulaiza **TODAS** las tareas pendientes, se debe de seleccionar la opción 6, en la cual se generará un listado con todas las tareas ordenada por orden de llegada independiente de su categoria.

    ===================================

    Tareas pendientes :
    - LIMPIAR ALFOMBRA (SALA)
    - LIMPIAR BANDEJAS (COCINA)
    - BARRER PISO (SALA)
    - TRAPEAR (COCINA)

    ===================================

- Opción 7:

Para poder visualizar las tareas pendientes de cierta categoria, debe de ingresar la penúltima opción. Aquí se mostraran todas las tareas de la categoría de llegada.

    ===================================
    
    Escribir categoria que desea filtrar
    sala
    
    ===================================
    
    Tareas pertenecientes a 'SALA:' 
    - LIMPIAR ALFOMBRA
    - BARRER PISO
    
    ===================================

- Opción 8:

Para finalizar, al seleccionar la última opción, estaremos saliendo del programa.

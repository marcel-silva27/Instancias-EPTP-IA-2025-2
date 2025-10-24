GENERADOR DE INSTANCIAS (EPTP)
===============================

  Este es un script simple en C++ diseñado para generar sets de instancias de prueba para el Enhanced Profitable Tour Problem (EPTP).

  El generador crea dos tipos de archivos por cada set de instancia:
    1. Un archivo de instancia (nodos) que define las propiedades de los nodos (tiempos de servicio, ventanas de tiempo, distancias).
    2. Un archivo de usuarios que define los perfiles de los usuarios (tiempo total, valoraciones de nodos y arcos).

===== COMPILACIÓN =====

  El script no tiene dependencias externas. Puedes compilarlo usando el archivo makefile y ejecutando:

  make

===== REQUISITO PREVIO: CREAR CARPETAS =====

  El script guarda los archivos en las carpetas "nodos/" y "usuarios/". Debes crearlas antes de ejecutar el programa:

  mkdir nodos
  
  mkdir usuarios

===== USO =====

  Una vez compilado y con las carpetas creadas, ejecuta el programa: 

  ./generator

El programa te solicitará dos entradas:
  1. Número de nodos: La cantidad de nodos (n) que tendrá la instancia (debe ser > 1).
  2. Cantidad de sets: Cuántos pares de archivos (instancia + usuarios) deseas generar (debe ser >= 1).

===== CONSIDERACIONES =====

   Los valores aleatorios (tiempos de viaje, duración de ventanas, etc.) se escalan en función del número de nodos "n". Esto hace que instancias más grandes sean proporcionalmente más complejas.

   Si pides generar una instancia de 5 nodos y ya existe "5_instancia_0.txt", el script buscará automáticamente el siguiente índice disponible (ej. "5_instancia_1.txt") para no borrar trabajo anterior.
   
   Es libre de modificar las instancias y el código fuente a su gusto.

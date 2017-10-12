# Primes
Búsqueda paralela de números primos.

Para más información sobre este proyecto visita [mi blog](https://vikman90.blogspot.com.es/2014/01/busqueda-paralela-de-numeros-primos.html).

## Dependencias
Para compilar este proyecto, el paquete de desarrollo para _SQLite3_ debe estar instalado.

### Ubuntu
```shellsession
$ sudo apt install libsqlite3-dev python3-pandas
```

### CentOS
```shellsession
$ sudo yum update
$ sudo yum install sqlite-devel 
$ sudo yum install epel-release
$ sudo yum install python-pandas
```

### Arch linux
```shellsession
$ sudo pacman -S python-pandas
```

## Compilación
Para compilar el programa, usa el _Makefile_ disponible:
```shellsession
$ make
```

## Ejecución
Para ejecutar el programa, usa el binario `list` disponible en el directorio `bin`:
```shellsession
$ bin/list [-seq] [-out=off|sqlite|file] <number> 
```

* La opción `-seq` se usa para ejecutar el programa en modo secuencial.
* La opción `-out` se usa para especificar la salida del programa: esta puede ser o bien a un fichero `.txt` o bien a una base de datos `SQLite`.
* Por último, debemos especificar el número hasta el cual buscar.


## Ejemplo
Por ejemplo, para encontrar todos los números primos hasta el 10:
```shellsession
$ bin/list 10
Encontrados 4 numeros primos.
Tiempo: 1.5253e-05 seg.
Tiempo en escribir: 0.000914791 seg.
```

Una vez encontrados podemos consultarlos en el fichero `output.txt`:
```shellsession
$ cat output.txt
2
3
5
7
```

# Primes
Búsqueda paralela de números primos.

Para más información sobre este proyecto visita [mi blog](https://vikman90.blogspot.com.es/2014/01/busqueda-paralela-de-numeros-primos.html).

## Dependencias
Para compilar este proyecto, el paquete de desarrollo para _SQLite3_ debe estar instalado. _Pandas_ se utiliza para ejecutar el benchmark en Pyton.

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

## Benchmark
Si quieres poner a prueba tu ordenador, prueba a ejecutar el benchmark:
```shellsession
$ chmod +x benchmark.py
$ ./benchmark.py -h
usage: benchmark.py [options]

Ejecuta un benchmark con distintas versiones del algoritmo.

optional arguments:
  -h, --help     show this help message and exit
  --begin BEGIN  Número desde el que empezar el test
  --end END      Número desde el que acabar el test
  --step STEP    Número por el que incrementar el test
  --style STYLE  Estilo de la gráfica final
```

Una gráfica mostrando los tiempos de ejecución de cada versión (paralela, secuencial y la criba original) se guarda en el archivo `time_compare.png`. Puedes seleccionar el estilo de la gráfica de entre todos estos:

```python
>>> import matplotlib.pyplot as plt
>>> print(plt.style.available)
['ggplot', 'seaborn-ticks', 'seaborn-dark-palette', 'seaborn-whitegrid', 'fivethirtyeight', 'seaborn-dark', 'seaborn-notebook', 'seaborn-bright', 'classic', 'dark_background', 'bmh', 'seaborn-colorblind', 'seaborn-darkgrid', 'seaborn-paper', 'seaborn-deep', 'grayscale', 'seaborn-muted', 'seaborn-poster', 'seaborn-talk', 'seaborn-pastel', 'seaborn-white']
```
Si ningún estilo se selecciona, se elige uno aleatorio.

# Diseño de bucle de aplicación

## TL;DR

Vamos a usar 'update capado y FPS descapados'

## Opciones

Hay diversas opciones de atacar el problema del diseño del bucle principal de nuestro motor; desde ignorar la diferencia de velocidades en ejecucion a tenerla en cuenta de distintas formas. 

### Bucle sin más 

```cpp
while(jugar){
    update();
    render();
}
```
El problema de esa implementación es que depende completamente del hardware en el que se ejecuta el juego.

### FPS y update capados a un tope (PCE) 

```cpp
while(jugar){
    update();
    render();
    if(vamosRapido){
        Esperar(x);
    }else{
        fuck();
    }
}
```
Si puedes asegurar un minimo de velocidad este sistema se asegura de que el juego no vaya demasiado rápido, pero en el caso de hardware más limitado, al ir lento no se puede hacer nada. 

Este era el sistema utilizado en el Programa de Convivencia Espacial.

### Actualización dependiente de FPS 

```cpp
while(jugar){
    tiempoTranscurrido = getTime() - tiempoAnterior;

    update(tiempoTranscurrido);
    render();
}
```

A primera vista esta puede ser una solución ideal, asegurandose de simular cada paso dependiendo del tiempo que tarde en cada uno de los equipos. 

El problema es que empieza a acarrear problemas de precisión que varían con el tiempo transcurrido, y hace que el bucle dependa también de la velocidad de renderizado.

### update capado y FPS descapados  

```cpp
while(jugar){
    while(HayQueActualizar && numUpdates < maxUpdatesSinRenderizar){
        update();
        numUpdates++;
    }

    render();

    //HayQueActualizar es revisar si han pasado el minimo de ticks para considerar otro bucle
}
```
Esta implementacion se encarga de actualizar la lógica a una velocidad estándar a costa de renderizar más lentamente en el caso de que el juego se esté quedando atrás (Se pone un máximo de frames que se pueden saltar).

Aún así puede dar problemas en hardware más lento, aunque no tantos como metiendo el render en cada bucle. Y en hardware rápido se desperdician ciclos gráficos.

### Update fijo y fps variables con interpolacion 

```cpp
TicksPorSegundo = 25;
SiguienteUpdate = 1000/TicksPorSegundo; //40
while(jugar){
    while(tiempo() > nextUpdate && numUpdates < maxUpdatesSinRenderizar){
        update();
        nextUpdate += SiguienteUpdate;
        numUpdates++;
    }

    interpolacion = (tiempo()+TicksPorSegundo-nextUpdate)/ SiguienteUpdate
    //Interpolacion dice cuanto "porcentaje" del siguiente frame hay que simular en el render.
    render(interpolacion);
}
```
Este sistema asume que la lógica del juego es suficientemente simple para actualizarla 25 veces por segundo (40ms por frame, 2.5 veces más tiempo que el que le dábamos al PCE).

La interpolacion funciona realizando calculos simples y visibles (por ejemplo posicion con velocidad) sin cambiar la lógica del juego, para que se vea más suave en sistemas con mejor hardware y no afecte a los que tienen peor.

## Conclusión

El mejor sistema sería utilizar la interpolación de fps junto con update constante, para asi poder reducir el numero de updates/segundo al minimo y aumentar el de renders/segundo al maximo. 

Debido a la implementación de nuestro ECS el sistema de render no sabe de la velocidad que lleva por ejemplo el transform, por lo que para no complicarnos la vida usaremos el mismo sistema pero sin interpolacion (repite frames en hardware rapido) y hay que aumentar el numero de frames por segundo (menos libertad de gasto de tiempo de update en cada frame) para que se vea smooth.

#### Docs & referencias

* [Un señor que sabe vainas cuya sabiduría robé](https://dewitters.com/dewitters-gameloop/)

* [Stackexchange en el que dan consejos a un tío que se enfrenta a lo mismo](https://gamedev.stackexchange.com/questions/651/what-should-a-main-game-loop-do)
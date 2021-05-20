# CEED to Lua
## Conceptos básicos
* **Scheme**: define todos los widget (termino CEGUI para referirse a ventana/objeto/item de la UI) que se van a usar en la GUI.
* **Layout**: define la disposición de las ventanas que se muestran.
* **Font**: describe la fuente que se va a usar.
* **Imageset**: tiene información de donde está y las medidas de cada sprite en una imagen (.png,.jpg).
* **LookNFeel**: determina como actua cada widget (cuando se pasa por encima de un boton, como se construye el borde y fondo de una ventana...).
* Por ahora solo se usa TaharezLook.scheme que define todos los tipos que se podrán usar en CEED **"TaharezLook/Tipo"**
* TaharezLook.imageset que define las celdas de los sprites en TaharezLook.png
* Y los .layout que son construidos en CEED con la info de .scheme y .imageset
## Instrucciones para instalar CEED
* Instalar y configurar CEED http://cegui.org.uk/wiki/CEED
* Las rutas de los ficheros están en PTSD-Engine\bin\assets\UI
## Cómo usar CEED
* IMPORTANTE: CEED solo puede abrir .project, .layout y .imageset
* Primero podemos abrir testProject.project desde CEED, este proyecto ya tiene configurada la ventana 1280x720
* Después se podrán abrir y crear los diferentes .layout en CEED
* Es importante que todos los elementos tengan nombres diferentes para luego identificarlos en LUA, incluso entre distintos .layout (Se pueden usar varios .layout a la vez)
* Los botones se crean en LUA porque al crearlos en CEED, a veces en algunos lanzamientos funcionaban y en otros no.
* También se pueden añadir elementos al .imageset para usarlos en los .layout. Abrir .imageset, click derecho y **Create Image Definition** (es posible que haya que guardar y reiniciar CEED para que aparezcan como opción en la Property Image)
## Usar los archivos en LUA
* Una vez generados los .layout con CEED, hay que hacer la carga de los ficheros (en resources.lua y resourceLoader.lua)
* Los callbacks que usaran los botones están en UIcallbacks.lua
## Usar los elementos de CEGUI en LUA
* name = nombre que identifica al elemento, source = fuente definida en .scheme o .imageset
*  Inicialmente se debe dar un valor al cursor **setUIMouseCursor(source="TaharezLook/CualquierNombreDel.imageset")**
* Ocultar/Mostrar cursor UI **setUIMouseCursorVisible(true/false)**
* Cambiar texto **changeText(name="Title",newText="TaiFighter")**
* Cambiar imagen **changeStaticImage(name="NombreImagen",source="TaharezLook/CualquierNombreDel.imageset")**
* Ocultar/Mostrar elementos (si se oculta el padre se ocultan los hijos) **setWindowVisible(name, true/false)**
* Crear botón **createButton(name="PushButton", "Texto", source="TaharezLook/Button", fontName="DejaVuSans-24",vec2:new(x, y), vec2:new(w, h))**
* Asociar callback a botón **setButtonFunction(name="NombreBoton","NombreFuncionEnUIcallbacks.lua")**
* Cambiar valor de progress bar **setProgressBarValue(name="DimensionBar", value=0.2)**
## Crear una fuente
* Se necesita el .ttf y .font (fijarse como están hechos los existentes en PTSD-Engine\bin\assets\UI\fonts) y añadirlo al .scheme como `<Font filename="NewFont-Size.font" />`
## Crear un imageset
* Crear un archivo de imagen para los sprites (.png) y crear un .imageset en CEED a partir de este, para definir cada sprite/elemento. Y añadirlo al .scheme como `<Imageset filename="TaharezLook.imageset" />`
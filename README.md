# Fundamentos_TF
Trabajo Final de Fundamentos de la Teoría de Juegos

Integrantes:
------------
Joaquín Aguirre Peralta - u201620285
Bruno Tiglla Arrascue - u20181A686
Franco Jair Vigil Bravo - u201614933
Diego Bedriñana Alberca - u201614284

Para este trabajo final, se creó a un personaje Goku, que debe salvar a los humanos de los zombies. Los zombies no pueden matar a Goku, solo stunnearlo por unos segundos.
Si Goku llega a matar a todos los zombies, pasará de nivel (con un total de 4 niveles), sin embargo si los zombies matan a todos los humanos, Goku perderá.

Los niveles 2, 3 y 4 están hechos a propósito de una manera en la que se pueda ganar rápidamente para cuestiones de verificación de toda la funcionalidad completa
del código.

Los datos mas importantes a resaltar para este proyecto son la creación de: Kamehameha (arma para matar zombies), Stunneo a Goku, Pase de niveles, Textos indicadores 
de zombies, humanos, nivel actual, de victoria y de derrota. Interacción con botones, sprites y un menú básico.

#Nota 1:
---------
Presionar 3 veces la tecla "E" antes de comenzar a moverte para que los textos cuadren

#Nota 2:
--------
Para desactivar el sonido de fondo ir a la función GamePlayScreen.cpp, ir a la línea de código 40 "_music.SDL2SoundEffect(_currenLevel+1);" y comentarla.
Así se podrá escuchar el kamehameha.

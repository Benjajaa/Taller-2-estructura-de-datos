# Integrantes
Benjamín Cuello, 21.682.135-1, benjamin.cuello@alumnos.ucn.cl, Paralelo C1 

Benjamín Salas, 21.758.667-4, benjamin.salas02@alumnos.ucn.cl, Paralelo C2
# Implementación del Algoritmo Minimax con Poda Alfa-Beta en un Juego

El proyecto trata sobre la aplicacion del algoritmo `Minimax` con `Poda Alfa-Beta` para crear un agente inteligente que tome las decisiones más optimas, utilizando el juego `Gato` tambien conocido como `Tres en linea` o `Tic-Tac-Toe`.

## **Explicación del algoritmo utilizado**

### **Minimax**
El algoritmo `Minimax` permite tomar decisiones óptimas en juegos de dos jugadores de suma cero. Su objetivo principal es minimizar la pérdida máxima que un jugador puede sufrir, asumiendo que el oponente juega de manera óptima. Se basa en:

1. **Árbol de decisiones:** Representa todos los movimientos posibles desde el estado actual del tablero.
2. **Evaluación de estados:** Se asigna un valor a cada estado terminal:
   - +1: Victoria del jugador Max.
   - -1: Victoria del jugador Min.
   - 0: Empate.
3. **Recursión:** Se calcula el mejor valor posible alternando entre movimientos del jugador Max (maximiza) y Min (minimiza).

#### **Funcionamiento:**
1. El árbol de decisiones del juego se representa como un conjunto de estados (nodos) y movimientos posibles (ramas).
2. Los jugadores alternan turnos:
   - **Maximización:** Trata de maximizar la puntuación.
   - **Minimización:** Trata de minimizar la puntuación.
3. Se evalúan los valores de los nodos hoja utilizando una función de utilidad.
4. Se realiza un recorrido **de abajo hacia arriba** en el árbol:
   - Los nodos **Max** toman el valor máximo de sus hijos.
   - Los nodos **Min** toman el valor mínimo de sus hijos.

### **Poda Alfa-Beta**

La **Poda Alfa-Beta** es una mejora del algoritmo Minimax que reduce el número de nodos evaluados sin alterar el resultado final.

#### **Funcionamiento:**
1. Utiliza dos límites:
   - **Alfa (α):** El mejor valor que el maximizador puede garantizar.
   - **Beta (β):** El mejor valor que el minimizador puede garantizar.
2. **Poda:** Si un nodo genera un valor que no afecta el resultado, se deja de explorar esa rama.

## **Explicación teórica**

### **Minimax**
1. **Objetivo:** Maximizar la ganancia del jugador mientras se minimiza la pérdida causada por el oponente.
2. **Funcionamiento:**
   - Representa el juego como un árbol de decisiones.
   - Los nodos hoja tienen valores calculados por una función de utilidad (evaluación del estado).
   - Se recorre el árbol **de abajo hacia arriba**, alternando entre los jugadores:
     - **Max:** Escoge el valor máximo de los hijos.
     - **Min:** Escoge el valor mínimo de los hijos.

### **Poda Alfa-Beta**
1. **Optimización:** Reduce la cantidad de nodos evaluados.
2. **Límites:**
   - **Alfa (α):** Mejor resultado garantizado para el maximizador.
   - **Beta (β):** Mejor resultado garantizado para el minimizador.
3. **Poda:** Si un nodo no mejora el resultado, se deja de evaluar.

## Análisis de Complejidad Temporal

### Minimax sin poda:
- **Complejidad:** \(O(b^d)\), donde:
  - \(b\): Número de movimientos posibles (factor de ramificación).
  - \(d\): Profundidad del árbol de decisiones.

Para **Tic-Tac-Toe**:
- \(b <= 9\), \(d <= 9\).
- Nodos a evaluar en el peor caso: \(9^9 = 387,420,489\).

### Minimax con poda alfa-beta:
- **Complejidad:** \(O(b^{d/2})\) en el mejor caso.
- Nodos a evaluar en el peor caso: \(9^{9/2} \approx 31,623\).

### Comparación:
| **Método**          | **Complejidad**  | **Nodos evaluados** |
|----------------------|------------------|---------------------|
| **Minimax**          | \(O(b^d)\)      | 387,420,489         |
| **Poda Alfa-Beta**   | \(O(b^{d/2})\)  | 31,623              |

## Estructura del Código

- **Lenguaje de Programación:** C++
- **Compilador:** g++
- **Estructura del Código:**
    - El código está organizado en múltiples archivos `.cpp` y `.h` para mantener una estructura modular y escalable.
    - Uso de punteros y arrays estáticos para la gestión de la memoria dinámica.

## Ejecución del Programa

Para compilar y ejecutar el programa, utiliza los siguientes comandos:

- **Compilar:** `g++ main.cpp App.cpp Sistema.cpp Tablero.cpp -o Juego`
- **Ejecutar:** `./Juego`

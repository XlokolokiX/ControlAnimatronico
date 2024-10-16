# 🤖 Proyecto Animatrónico - Five Nights at Freddy's (FNAF)

Este proyecto fue desarrollado como parte de la materia **Sistemas de Control II**, con el objetivo de crear un animatrónico inspirado en el popular juego *Five Nights at Freddy's (FNAF)*. La principal característica de interés de este juego es la atracción que ha generado tanto en los fanáticos de los videojuegos como en los entusiastas de la animatrónica, debido a la relación entre el mundo de FNAF y el campo de la animatrónica.

## 🚀 Descripción del Proyecto

El animatrónico creado está basado en uno de los personajes del juego, y su control es implementado utilizando un mando de PS3 🎮, conectado mediante Bluetooth a un microcontrolador **ESP32**.
El sistema permite el control de varios movimientos y efectos visuales, brindando una experiencia interactiva y realista.

<image src="/Media/Cupcake.jpeg" alt="Cupcake Chica">

### ✨ Funcionalidades Implementadas:

- 👀 **Movimiento de los ojos** en los ejes X e Y.
- 👁️ **Parpadeo** de los ojos.
- 🌈 **Cambio de color** en cada ojo mediante tiras LED.
- 👄 **Movimiento de la boca** utilizando un servo de alto torque.
- 🕯️ **Efecto de llama** para una vela simulada mediante un LED.

## 🛠️ Componentes Utilizados

Para implementar el sistema del animatrónico, se emplearon los siguientes componentes electrónicos y mecánicos:

- 💡 **2 tiras LED** para el control del color de los ojos.
- 🕯️ **1 LED** para simular la llama de una vela.
- 🔧 **6 servos SG90** para controlar el movimiento de los ojos y las pestañas.
- 🔩 **1 servo de alto torque** para el movimiento de la boca.
- 🛡️ **1 shield Adafruit** para la conexión y control de los servos.
- 📡 **1 microcontrolador ESP32** para la lógica de control y la conexión Bluetooth.
- 🎮 **1 mando PS3** para el control remoto del animatrónico.

## 🔗 Conexiones y Control

La comunicación entre el mando de PS3 🎮 y el microcontrolador ESP32 se realiza a través de **Bluetooth**, permitiendo un control inalámbrico de todas las funcionalidades ya mencionadas.

## 📚 Librerías Utilizadas

Para facilitar la implementación de este sistema, se utilizó una librería que permite la conexión y el control del animatrónico a través del mando de PS3. Esta librería maneja la comunicación Bluetooth entre el ESP32 y el mando, así como el control de los servos y los LEDs.

## 🔧 Futuras Mejoras

Algunas posibles mejoras para este proyecto incluyen:

- 💡 Incluir más efectos visuales con las tiras LED.
- ⚡ Optimizar el control inalámbrico para reducir el tiempo de respuesta.
- 🎭 Mejorar la sincronización entre los movimientos y las luces para una experiencia más inmersiva.
- 🔊 Agregar la funcionalidad de producir sonidos para una experiencia más "Terrorífica".
  
## 🎓 Conclusión

Este proyecto permitió aplicar conceptos de control y robótica en un proyecto práctico e interactivo. La implementación de un animatrónico controlado remotamente demuestra cómo se pueden utilizar microcontroladores como el ESP32 y dispositivos cotidianos como el mando de PS3 para crear sistemas complejos y realistas.

## Video de demostración

[Ver video de la demostración](./Media/vid.mp4)

---

Este proyecto es parte de la materia **Sistemas de Control II** y está inspirado en el mundo de *Five Nights at Freddy's* 🎮👾.

# Robô Sumô
Este projeto faz parte da disciplina de Robótica do curso de Tecnologia em Mecatrônica Industrial do Instituto Federal de São Paulo, campus Catanduva.

O projeto consistiu em criar um robô sumô de até 3 kg, inicialmente controlado manualmente, que posteriormente seria convertido em autônomo.

Há dois códigos desenvolvidos na Arduino IDE, utilizando o Arduino Uno como microcontrolador, um módulo relé de 4 canais e um receptor de rádio frequência no modo manual.

No código *Robo_Sumo_Autonomo_Manual*, utilizamos 3 canais do receptor: um para a chave seletora, um para a alavanca de aceleração e outro para a alavanca de direção. A leitura desses pinos é realizada verificando o comprimento de onda, uma vez que é dessa forma que o receptor entrega a informação. Além disso, no modo autônomo, há 4 sensores infravermelhos (um em cada canto do robô), permitindo verificar se ele está na borda da arena, já que o centro é branco e as bordas são pretas, facilitando a identificação. Por fim, utilizamos um sensor ultrassônico para detectar a presença de um oponente à frente. Caso contrário, o robô realiza uma leve rotação e faz uma nova medição.

No código *Robo_Sumo_Autonomo_Ultrassom_Duplo*, toda a parte manual foi removida. Os sensores infravermelhos foram mantidos e um sensor ultrassônico adicional foi adicionado na parte frontal, permitindo verificar a diferença de distância entre os sensores e o oponente, tornando a interceptação mais precisa. Contudo, como efeito colateral, foi necessário realizar as medições de forma alternada, para que um sensor não interferisse no outro.
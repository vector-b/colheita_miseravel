Nome : Pedro Martins e Sá			
Nome : Gustavo Valente  				
Nome : Victor Gabriel Souza Barbosa	
Nome : Vitor Gaio Salmória


O jogo é iniciado através do executável "jogo", onde o mapa contido num arquivo de texto é carregado e exibido na 
tela, depois os caracteres e elementos no jogo são exibidos no mapa.

Para jogar o usuário controla o personagem com as teclas w, a, s, d (respectivamente cima, esquerda, baixo, direita),
ele pode pegar as sementes dispostas pelo terreno com a tecla x e planta-las com a tecla p, já a colheita é feita 
com a tecla c, o personagem se alimenta dos frutos com a tecla f, ele pode jogar elementos da mochila fora com a 
tecla jalém de observar a planta crescer com a tecla o. O objetivo do jogo é plantar as sementes e aguardar até que
cresçam e produzam frutos, o jogador é premiado com um ponto a cada colheita bem sucedida, vale lembrar que cada 
movimento conta como um turno onde o nível de fome do personagem aumenta, caso chegue a 100 a sua saúde começa a 
diminuir, para reduzir o nível de fome é preciso comer os frutos colhidos, caso a saúde chegue a zero o jogo acaba. 

Os elementos do jogo e os caracteres que os representam são: personagem "i", cerca ou limite do mapa "| ou _", terreno
de plantio " * ", diferentes tipos de semente presentes no mapa "w " " , " " o " " b "  , sua representação após 
serem plantadas no terreno " ~ " " , " " + " " d " e a representação das plantas que originam " W " " B " " + " " D ",
respectivamente alface,  batata, tomate e batata doce. Quando uma planta morre é representado pelo caractere X no 
mapa.

Foram criados os seguintes tipos de dados:
-Mapa: contém o número de linhas e colunas da matriz que forma o mapa além dos caracteres;
- Semente: similar ao nodo de uma lista contém um ponteiro para próxima estrutura (que é do mesmo tipo) e um tipo
abstrato de dados "tipo_semente" que serve como conteúdo do nodo;
- Tipo_semente: é o conteúdo da estrutura "semente", contém o nome, tempo de crescimento em turnos, nível de 
satisfação e as coordenadas da semente;
- Mochila: guarda os elementos do jogo como sementes, por exemplo, tem um tamanho definido e quantidade atual de 
itens;
- Personagem: contém os níveis de saúde e fome do personagem e sua mochila;
- Planta: contém a estrutura de dados "semente", o estado atual  de crescimento da planta, e dois ponteiros, anterior
e próximo;
- Fila_plantio: tipo abstrato de dados da fila gerada ao plantar uma semente, contém o tamanho atual da fila, o número
máximo de elementos que ela comporta, seu inicio, fim e um ponteiro para os dados nela quadrados.


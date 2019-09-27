Nome : Pedro Martins e S�			
Nome : Gustavo Valente  				
Nome : Victor Gabriel Souza Barbosa	
Nome : Vitor Gaio Salm�ria


O jogo � iniciado atrav�s do execut�vel "jogo", onde o mapa contido num arquivo de texto � carregado e exibido na 
tela, depois os caracteres e elementos no jogo s�o exibidos no mapa.

Para jogar o usu�rio controla o personagem com as teclas w, a, s, d (respectivamente cima, esquerda, baixo, direita),
ele pode pegar as sementes dispostas pelo terreno com a tecla x e planta-las com a tecla p, j� a colheita � feita 
com a tecla c, o personagem se alimenta dos frutos com a tecla f, ele pode jogar elementos da mochila fora com a 
tecla jal�m de observar a planta crescer com a tecla o. O objetivo do jogo � plantar as sementes e aguardar at� que
cres�am e produzam frutos, o jogador � premiado com um ponto a cada colheita bem sucedida, vale lembrar que cada 
movimento conta como um turno onde o n�vel de fome do personagem aumenta, caso chegue a 100 a sua sa�de come�a a 
diminuir, para reduzir o n�vel de fome � preciso comer os frutos colhidos, caso a sa�de chegue a zero o jogo acaba. 

Os elementos do jogo e os caracteres que os representam s�o: personagem "i", cerca ou limite do mapa "| ou _", terreno
de plantio " * ", diferentes tipos de semente presentes no mapa "w " " , " " o " " b "  , sua representa��o ap�s 
serem plantadas no terreno " ~ " " , " " + " " d " e a representa��o das plantas que originam " W " " B " " + " " D ",
respectivamente alface,  batata, tomate e batata doce. Quando uma planta morre � representado pelo caractere X no 
mapa.

Foram criados os seguintes tipos de dados:
-Mapa: cont�m o n�mero de linhas e colunas da matriz que forma o mapa al�m dos caracteres;
- Semente: similar ao nodo de uma lista cont�m um ponteiro para pr�xima estrutura (que � do mesmo tipo) e um tipo
abstrato de dados "tipo_semente" que serve como conte�do do nodo;
- Tipo_semente: � o conte�do da estrutura "semente", cont�m o nome, tempo de crescimento em turnos, n�vel de 
satisfa��o e as coordenadas da semente;
- Mochila: guarda os elementos do jogo como sementes, por exemplo, tem um tamanho definido e quantidade atual de 
itens;
- Personagem: cont�m os n�veis de sa�de e fome do personagem e sua mochila;
- Planta: cont�m a estrutura de dados "semente", o estado atual  de crescimento da planta, e dois ponteiros, anterior
e pr�ximo;
- Fila_plantio: tipo abstrato de dados da fila gerada ao plantar uma semente, cont�m o tamanho atual da fila, o n�mero
m�ximo de elementos que ela comporta, seu inicio, fim e um ponteiro para os dados nela quadrados.


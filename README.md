# TP2-PAA
Segundo trabalho prático de Projeto e análise de algoritmos 


Universidade Federal de Ouro Preto
Departamento de Computação
Projeto e Análise de Algoritmos

Trabalho prático
Data de entrega: 13/12/2021
Data de apresentação: 03/01/2022 e 05/01/2022
O trabalho pode ser feito em grupo de até 3 alunos.
Valor: 10 pontos – peso 1.5

Este trabalho prático consiste na implementação de três programas. São eles
Satisfabilidade, Clique e Conjunto Independentes.
Satisfabilidade – Dada uma formula booleana na forma normal conjuntiva, encontre uma
atribuição de valores-verdade às variáveis da fórmula que a torne verdadeira, ou informe
que não existe tal atribuição.
Clique – Dado um grafo, encontre um conjunto máximo de vértices tal que todas as
possíveis arestas entre eles estejam presentes.
Conjunto independente – dado um grafo, o objetivo é encontrar o maior número de
vértices independentes, isto é, não existe aresta entre nenhum par deles.
O Conjunto Independente deve ser resolvido usando Branch and Bound.
O problema da Satisfabilidade deve ser resolvido por meio de redução com custo
polinimial ao problema do conjunto Independente, já implementado usando Branch and
Bound.
E o problema do Clique deve ser resolvido por meio de redução com custo polinimial
também ao problema do Conjunto Independente, já implementado usando branch and
bound.
Você deve entregar uma documentação contendo as descrições e explicações dos 3
algoritmos, juntamente com as decisões tomadas em suas implementações e os resultados
de 3 instâncias de cada problema.
A entrada dos programas para os problemas envolvendo grafo deve ser feita por meio de
um arquivo contendo na primeira linha a quantidade de vértices e nas próximas uma matriz
indicando se há uma aresta (1) ou não (0) entre dois vértices.
Exemplo:
9
0 0 1 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0
1 1 0 1 1 0 0 0 0
0 0 1 0 0 0 1 0 0
0 0 1 0 0 1 0 1 0
0 0 0 0 1 0 0 0 0
0 0 0 1 0 0 0 1 1
0 0 0 0 1 0 1 0 1
0 0 0 0 0 0 1 1 0
A saída deve informar os vértices envolvidos na solução do problema, além do tempo de
execução.
Para o problema da satisfabilidade, a entrada, na primeira linha, deve informar a
quantidade de variáveis e cada uma das demais deve ser referente a uma cláusula, onde o
primeiro valor da linha é referente a primeira variável, o segundo a segunda variável e assim
por diante.
Por exemplo, para a fórmula , o arquivo de
entrada deve ser:
3
1 1 1
1 0 -1
-1 1 0
0 -1 1
0 0 0
Sendo que, 1 indica que a variável está presente na cláusula e não é negada, 0 indica que a
variável está presente na cláusula e está negada e -1 indica que a variável não está presente
na cláusula. A saída deve informar o tempo de execução e os valores-verdade atribuídos a
cada variável se a fórmula for satisfatível, caso contrário, informe que não é satisfatível.
Você deve entregar os códigos fontes, as instâncias utilizadas e a documentação, via
Moodle, até 23h00 dia 13/12/2021.
Cada grupo deverá apresentar o trabalho para a turma nos dias 5 e 7 de janeiro de 2022.
A ordem será definida por sorteio no início da aula. Cada grupo terá 15 min para a
apresentação.
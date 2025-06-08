# Cadastro de Pessoas em C

Este projeto foi desenvolvido como parte da disciplina de Estrutura de Dados, na linguagem C. Ele oferece um sistema para o cadastro de indivíduos, com validações de entrada e gerenciamento dos dados em uma estrutura de pilha implementada com lista encadeada.

## Funcionalidades

- Cadastro de Pessoas: Permite o registro de indivíduos com os seguintes dados:

  Nome
  CPF: Inclui validação dos dígitos verificadores para garantir a integridade da informação.
  Idade: Validação para garantir que a idade esteja dentro de uma faixa etária razoável (0 a 150 anos).
  Altura: Validação de valor para assegurar que a altura esteja em um intervalo lógico (0.0 a 3.0 metros).

- Armazenamento Inicial em Vetor Dinâmico: Os dados são inicialmente coletados e armazenados em um vetor alocado dinamicamente, otimizando o uso de memória.
- Migração para Estrutura de Pilha: Após o cadastro no vetor, os dados são migrados para uma estrutura de pilha.
- Implementação de Pilha com Lista Encadeada.
- Operações de Pilha: Suporte para as operações básicas de:

  Empilhar (push): Adiciona novos indivíduos ao topo da pilha.
  Desempilhar (pop): Remove o indivíduo do topo da pilha.

- Ordenação de Dados:

  Ordenação por Altura: Implementa o algoritmo Bubble Sort para organizar os indivíduos com base em sua altura.
  Ordenação por Idade: Utiliza o algoritmo Selection Sort para ordenar os indivíduos por idade.
  A lista é impressa a cada iteração dos algoritmos para visualização do processo.
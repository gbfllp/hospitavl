# Sistema de Gerenciamento de Pacientes

## Descrição
Este é um programa em C++ que implementa um sistema de gerenciamento de pacientes utilizando uma árvore AVL. O sistema permite gerenciar registros de pacientes de forma eficiente, com operações como inserção, remoção, busca e listagem de pacientes.

1. Inserir paciente
2. Listar pacientes (ordem de prioridade)
3. Buscar paciente por ID
4. Buscar paciente por prioridade
5. Buscar paciente por nome
6. Editar paciente por ID
7. Remover paciente por ID

## Funcionalidades
- **Inserir Paciente**: adiciona um novo paciente com detalhes como ID, prioridade, nome, telefone e histórico.
- **Listar Pacientes**: exibe todos os pacientes em ordem de prioridade.
- **Buscar Paciente por ID**: encontra um paciente usando seu ID único.
- **Buscar Paciente por Prioridade**: encontra pacientes com base na prioridade.
- **Buscar Paciente por Nome**: encontra pacientes com base no nome.
- **Editar Paciente por ID**: permite atualizar a prioridade de um paciente específico usando seu ID.
- **Remover Paciente**: remove um paciente do sistema usando seu ID.

## Estruturas de Dados
- **Árvore AVL**: usada para armazenar e gerenciar registros de pacientes, garantindo operações balanceadas.
- **Pilha**: usada para percorrer a árvore AVL em ordem, de forma repetitiva.

## Como Executar o Projeto

Por padrão, o projeto possui os arquivos pré-compilados na pasta "output". Todavia, é possível compilá-lo por conta própria seguindo os passos abaixo:

Certifique-se de ter um compilador C++ instalado.

*É necessário ter um compilador como o g++ (parte do GCC) ou equivalente.*

1. Clone o repositório

```bash
git clone https://github.com/gbfllp/hospitavl.git # clone o repositório usando o git
cd hospitavl # vá para o diretório contendo o projeto
```

2. Compile o arquivo principal

```bash
g++ index.cpp -o hospitavl # compila o arquivo "index.cpp" em um executável com o nome "hospitavl"
```

3. Execute o arquivo compilado

* Caso esteja no windows, o arquivo a ser executado será "hospitavl.exe", no linux/macOs simplesmente "hospitavl".

## Exemplo
### Exemplo de Entrada/Saída
```
Menu:
1. Inserir paciente
2. Listar pacientes (ordem de prioridade)
3. Buscar paciente por ID
4. Buscar paciente por prioridade
5. Buscar paciente por nome
6. Editar paciente por ID
7. Remover paciente por ID
0. Sair

Escolha uma opção: 1
Digite o ID do paciente: 101
Digite a prioridade: 2
Digite o nome: João Silva
Digite o telefone: 1234-5678
Digite o histórico: Hipertensão

Paciente inserido com sucesso.
```

## Autores

- César Nogueira
- Gabriel Fellipe
- Ian Libânio

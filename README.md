# Trabalho Final de Algoritmo e Estrutura de Dados 1

## Introdução
Este repositório contém o trabalho final desenvolvido em grupo para a disciplina de Algoritmo e Estrutura de Dados 1. O projeto tem como objetivo criar uma aplicação em linguagem C para organizar uma fila hospitalar de pacientes. A aplicação permite que os pacientes sejam cadastrados na fila, consultados e organizados com base em prioridades médicas.

## Membros do Grupo
- [Lucas de Almeida Bueno]
- [Mateus Lisita]
- [Lucas Miguelin]
- [Brenna de Mesquita]

## Funcionalidades

O sistema possui várias funcionalidades que permitem o gerenciamento eficiente da fila hospitalar, incluindo:

1. **Cadastro de Pacientes**: Os atendentes podem cadastrar novos pacientes na fila, fornecendo informações como nome, idade e gravidade da condição. Além disso, é possível identificar se o atendimento é preferencial.

2. **Chamada do Próximo Paciente**: A aplicação permite chamar o próximo paciente da fila, com a opção de escolher entre a fila comum e a fila preferencial.

3. **Chamada Regular de Pacientes**: O sistema implementa uma lógica de chamada alternada entre pacientes comuns e preferenciais, garantindo um atendimento justo.

4. **Visualização da Fila**: Os atendentes podem visualizar a fila, incluindo a fila comum, a fila preferencial ou ambas, com informações detalhadas sobre os pacientes.

5. **Busca de Pacientes**: É possível buscar pacientes na fila por nome, distinguindo entre preferencial e comum.

6. **Ordenação da Fila**: As filas podem ser ordenadas com base na idade dos pacientes, permitindo que os pacientes mais velhos sejam atendidos primeiro.

## Estrutura do Código

O código do projeto está organizado em vários arquivos e diretórios:

- `main.c`: Contém a função principal do programa e a interface do usuário.
- `tad.c` e `tad.h`: Implementação das estruturas de dados e operações para gerenciar a fila hospitalar.
- `Makefile`: Arquivo de configuração para compilar o código.

## Contribuições
Este projeto é resultado do esforço conjunto de todos os membros do grupo. Se você deseja contribuir para o desenvolvimento ou aprimoramento deste projeto, sinta-se à vontade para fazer um fork deste repositório e criar uma solicitação de pull.

Agradecemos por visitar nosso projeto! Esperamos que nossa aplicação de gerenciamento de fila hospitalar seja útil e eficaz. Se você tiver alguma dúvida ou sugestão, entre em contato conosco por meio dos perfis dos membros do grupo listados acima.

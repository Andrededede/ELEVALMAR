# Simulação de Elevador 🏢🛗

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

## 🎓 Contexto Acadêmico
Projeto desenvolvido como atividade prática para a disciplina de **Estrutura de Dados**, durante o **3º semestre** do curso de **Engenharia de Computação** no **Instituto Federal do Ceará (IFCE)**.

## 📖 Sobre o Projeto
Este repositório contém uma simulação de um sistema de elevador desenvolvida em linguagem C. O objetivo principal do sistema é gerenciar o fluxo de pessoas em um prédio, processando uma fila de eventos, gerenciando as chamadas e otimizando a rota do elevador para atender aos passageiros.

O projeto foi construído com foco na **modularização** (utilizando `structs` e ponteiros), dividindo o domínio do problema em entidades lógicas distintas.

## ⚙️ Arquitetura e Módulos
O código fonte está organizado separando as definições (arquivos `.h`) das implementações (arquivos `.c`). As principais entidades do sistema são:

* **`Predio`**: Gerencia a estrutura física, a lista de andares e as filas de pessoas aguardando o elevador.
* **`Elevador`**: Controla o estado atual, a direção de movimento, a lista de passageiros internos, a energia (andares percorridos) e a rota a ser seguida.
* **`Pessoa`**: Representa os usuários do sistema, guardando informações de identificação, andar de origem, destino e tempo de chegada.
* **`main.c`**: Ponto de entrada que recebe a string de configuração inicial, instancia os componentes e executa o laço temporal (loop) da simulação segundo a segundo.

## 🚀 Como Executar

**Pré-requisitos:**
* Ter um compilador C instalado (como GCC ou MinGW).

**Via Terminal:**
1. Clone este repositório:
   ```bash
   git clone [link-do-seu-repositorio]
   ```
2. Navegue até a pasta do projeto e compile os arquivos utilizando o GCC:
   ```bash
   gcc main.c Elevador.c Predio.c Pessoa.c -o simulador_elevador
   ```
3. Execute o programa compilado:
   * No Windows: `.\simulador_elevador.exe`
   * No Linux/Mac: `./simulador_elevador`
```

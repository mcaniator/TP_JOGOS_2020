Este repositório contém um conjunto de projetos em C++ que implementam um jogo 2D simples, que pode ser utilizado como auxílio no ensino de programação. O jogo foi pensado de forma a abordar os principais tópicos da disciplina de Algoritmos ofertada pelo Departamento de Ciência da Computação (DCC) da Universidade Federal de Juiz de Fora (UFJF). O objetivo é, a cada aula, fornecer uma versão inicial do jogo já implementada, com algumas funcionalidades faltando, para que a(o) aluna(o) as implemente como exercícios de programação vinculados ao tópico discutido naquela aula. O código foi construído de forma a esconder complexidades do aluno iniciante. Todas as funções que precisam ser implementadas estão localizadas no arquivo principal do projeto (main.cpp) e exigem apenas o conhecimento daquilo que foi visto até então na disciplina. O jogo foi desenvolvido com a biblioteca SFML (https://www.sfml-dev.org/).


# Organização do repositório
Cada branch está associada a uma aula específica. Cada aula possui o seu próprio projeto configurado.

As aulas foram divididas da seguinte forma:

Aula01: Movimentação básica
Tópicos trabalhados: 
- Uso de funções
- Declaração de variáveis
- Expressões aritméticas e atribuições

Aula02: Movimentação com colisão
Tópicos trabalhados:
- Condicionais

Aula03: Movimentação com colisão e geração de itens e inimigos
Tópicos trabalhados:
- Condicionais
- Estruturas de repetição

Aula04: Coleta de itens e ranking de pontuação
Tópicos trabalhados:
- Vetores numéricos

Aula05: Coleta de itens em uma ordem específica
Tópicos trabalhados:
- Strings

Aula06: Inclusão de nome no ranking e minimapa
Tópicos trabalhados:
- Strings
- Matrizes

Aula07: Inclusão de itens no minimapa
Tópicos trabalhados:
- Matrizes
- Structs


Há duas versões do projeto para cada aula: uma para o Linux e outra para o Windows. A princípio, para testar o jogo, basta fazer o checkout da branch desejada, abrir o projeto Code::Blocks (arquivo .cbp) referente ao sistema instalado na sua máquina, compilar e executar. Em cada branch, há uma versão da SFML na própria pasta do projeto. Isso foi feito para evitar problemas com a configuração do laboratório na ocasião. Caso o projeto não execute, ou você prefira utilizar uma versão mais recente da SFML, siga os passos de configuração do projeto na seção a seguir.


# Configuração do projeto
Caso ocorra algum problema na execução dos projetos incluídos nas branches, você pode configurá-los manualmente.

Para configurar o projeto, é necessário ter a biblioteca SFML instalada.

No Windows, é necessário baixar a biblioteca apropriada, de acordo com o compilador instalado na sua máquina: https://www.sfml-dev.org/download.php
No Linux, a biblioteca é tipicamente encontrada nos repositórios da distribuição:
Debian/Ubuntu: sudo apt-get install libsfml-dev
Arch: sudo pacman -Sy sfml

Ao abrir o projeto no Code::Blocks, deve-se seguir os seguintes passos:
1) Clicar com o botão direito no nome do projeto e selecionar "Build options"
2) Acessar a aba "Linker settings" e incluir as seguintes bibliotecas na caixa "Link libraries", **nesta ordem**:
- sfml-graphics
- sfml-window
- sfml-system
3) Caso os arquivos da biblioteca não tenham sido descompactados em uma pasta padrão do sistema, será necessário incluir os diretórios no PATH ou fazer os passos abaixo:
  1) Na aba "Search directories", incluir na sub-aba "Compiler" o diretório de instalação dos arquivos de cabeçalho (.h) da biblioteca (normalmente estes arquivos estão em uma pasta chamada "include")
  2) Na aba "Search directories", incluir na sub-aba "Linker" o diretório de instalação dos arquivos compilados (.a) da biblioteca (normalmente estes arquivos estão em uma pasta chamada "lib")

Mais detalhes sobre o processo de configuração de um projeto com a SFML podem ser encontrados na seção "Getting started" dos tutoriais oficiais da biblioteca:
https://www.sfml-dev.org/tutorials/2.6/

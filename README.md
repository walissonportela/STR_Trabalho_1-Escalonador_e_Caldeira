# SBL0092 - SOFTWARE EM TEMPO REAL (2022.2 - T01)
## SIMULADOR DE ESCALONEMANTO DE TAREFAS PARA RM E EDF

- Para executar o programa dentro do terminal do computador é importante lebrar que a função `main` de nosso
arquivo no formato `.c` recebe o arquivo por argumentos `(argv[1])` e para sua execução precisamos utilizar
uma forma diferente. Siga o passo a passo para conseguir `executar` nosso programa:

**1° - *Abra a pasta do arquivo dentro do prompt de comando (recomendo usar o comando "cd")*;**

**2° - *Digite o comando*:**

    gcc -o escalonador main.c -lm

**3° - *Digite o comando*:**

    ./escalonador sistema1.txt

**4° - *Repita o passo 3 para cada arquivo de sistema*.**

- Ao entrar no programa você terá em tela o arquivo lido e um pequeno menu onde pode-se fazer dois tipos de
escalomento, Rate Monotonic (RM) e Earliest Deadline First (EDF). Ao selecionar a opção desejada será mos-
trado em tela a linha de tempo e a tarefa executada em cada instante de tempo pelo processador.

## CONTROLE E SUPERVISÃO DE UMM SISTEMA DE CALDEIRA SIMULADO

**1° - *Executar o simulador dado por `Aquecedor2021.jar` clicando duas vezes nele ou abrindo no terminal pelo seguinte comando*:**

    java -jar Aquecedor2021.jar <numero-porta-escutada>
    
- Caso o usuário execute o simulador dando dois cliques no arquivo, a porta padrão é 4545.

**2° - *Digite o seguinte comando no terminal*:**

    gcc -o main main.c atuadores.c bufduplo.c sensores.c socket.c tela.c referenciaTemp.c referenciaNivel.c -lpthread
    
**3° - *Logo em seguida execute o seguinte no terminal, caso seja a porta padrão, se não, coloque a porta referente*:**

    ./main localhost 4545

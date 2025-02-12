[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=16166970)
# Computação Móvel - Projeto 1 - Introdução

Projeto em C++ com arduino. O projeto consiste em fazer um jogo que possui três etapas: Joga da memoria onde uma sequência aleatória pisca nos leds verde e vermelho, e caso o jogador acerte a ordem ele passa para a segunda fase, O jogo das perguntas: Um jogo de 5 perguntas aleatórias onde o jogador deve responder com sim ou não (nos respectivos botões). O jogador tem a opção de pular uma pergunta caso deixe o tempo esgotar, caso ele tente pular mais de uma, o jogo acaba. Por fim a terceira e última fase é uma pergunta final fixa que quando acertada, o jogador vence o jogo e toca uma música de vitória. O jogo também possui sons para indicar acerto e erro das perguntas e da ordem dos leds. O projeto possui três botões, da esqueda para a direita sendo o primeiro o botão de start e reset(caso o jogo ja tenha sido iniciado); botão que corresponde ao led verde e a resposta "sim"; botão que corresponde ao led vermelho e a responder "não".

## Metodologia
- ` Materiais Utilizados`
    - 1 led vermelho(Para o jogo de Memoria)
    - 1 led verde  (Para o jogo de Memoria)
    - 3 botões (primero de Start/Desistencia,segundo Led Verde/Sim e terceiro Led Vermelho/Não)
    - 1 Arduino Uno (Utilizado para Programação do Jogo)
    - 2 Placas de Ensaio (Para conexao dos Fios, Leds, Botoes , Lcd , Resistores, Potenciomentro, )
    - 1 Buzzer (Para os sons de Acerto,Erro, Acabou Tempo e Vitoria )
    - 1 Potenciometro (Acender o LCD)
    - 1 LCD 16x2 (Para o jogo de perguntas e Todas as frases do jogo )
    - 3 Resistores (Um para led verde, um para led vermelho e um para o lcd)
- `Desenvolvimento`
    - O projeto teve o início do seu desenvolvimento no Tinkercad, onde montamos primeiro a parte elétrica, para que ficasse mais fácil de visualizar o que iriamos fazer. Em seguida, desenvolvemos o código para o jogo da memória,  onde foi criado algumas funções que permitissem o seu funcionamento, como a "startLedGame" , que foi a base inicial para o nosso projeto. Por fim, na semana final da entrega desenvolvemos o código para o jogo de perguntas e respostas, onde foi armazenada uma série de perguntas sobre jogos dentro de um Array, e também suas respectivas respostas em um outro Array, assim criamos uma função para começar o jogo de perguntas e respostas assim que o jogador vencesse o nivel 1. Tivemos alguns desafios pelo caminho, como a parte de integrar ambos os jogos, porém no dia final da entrega conseguimos cumprir todos os requisitos do projeto. Abaixo temos foto do circuito montado e no tinkercad
![Foto do Circuito do Jogo](https://github.com/user-attachments/assets/ae59ffa3-054c-4c88-874e-40bf25679745)
![tinkercad](https://github.com/user-attachments/assets/ff07e86c-5183-447e-81ee-6926b2767f84)


## Experimentos

- `Fase 1: Jogo da memória:`  neste video demonstramos o funcionamento do jogo de leds, onde os leds piscam 10 vezes aleatoriamente (no video piscam 5 vezes para facilitar a demonstração) depois o jogador tem que acertar a sequencia dos leds. Se o jogador errar algum led da sequencia o jogo acaba instantaneamente, e se acertar todos tem um som de acerto e vai para segunda fase do jogo.

https://github.com/user-attachments/assets/55b4a751-aa95-44e5-b102-ab3847fc41ce

- `Fase 2: Jogo das perguntas:` neste video mostramos o funcionamento do jogo das perguntas e respostas. Onde o jogador deve responder uma sequencia de 5 perguntas de sim ou não, tendo a opção de pular uma questão caso deixe o tempo acabar. Quando as 5 perguntas são respondidas corretamente, o jogador avança para a fase final.

https://github.com/user-attachments/assets/bc1242bb-bb82-4ea4-af64-c3a6b081dd64

- `Última fase: Pergunta final:` neste video mostramos a ultima fase do jogo, a pergunta final onde o jogador tem 15 segundos para responder, e quando acertada ela toca o som da vitoria, que é a melodia do hino do São Paulo.

https://github.com/user-attachments/assets/6550432d-71de-4b16-8e3a-ba08f2c28e39

## Conclusão
Nosso grupo chegou a conclusão que o arduino possui infinitas possibilidades para se trabalhar, estimulando a criatividade e mudando a nossa maneira de resolver problemas.

- `Dificuldades encontradas e como resolvemos:`
    - encontramos algumas dificuldades ao longo do projeto, como na função que verificava o clique do usuário e comparava com a sequência de leds aleatórias que o jogo fornecia, esse problema foi resolvido alterando a maneira que foi feita a função booleana que verificava os cliques. Também tivemos problema na função scroll, que movia as palavras para a esquerda do display, porém esse problema foi resolvido colocando um delay antes do print no lcd. E por fim, a última dificuldade que enfrentamos foi na hora de atribuir a função de reiniciar o jogo q uando pressionado o botão de start, para resolver esse problema criamos uma função que retorna true ou false para caso o jogo esteja rodando ou não, essa função foi chamada em cada etapa do game, para que o usuário consiga desistir do jogo em qualquer etapa.
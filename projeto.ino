#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

// LEDs, botões e buzzer 
int LedG = 12;
int LedR = 13;
int sButton = 3;  
int nButton = 10;   
int startButton = 2;
int buzzer = A2;

volatile bool iniciarJogo = false;
bool jogofuncionando = false;

//contador de sequencia
const int numPiscar = 10;
int sequencia[numPiscar];
int userInput[numPiscar];

//frases usadas no display
char frase[41] = "Bem-vindo, pressione start para iniciar.";
char jogoMem[25] = "Fase 1. Jogo da memoria:";
char acertouS[23] = "Acertou! Proxima fase.";
char errouS[24] = "Errou! Tente novamente.";
char jogoResp[28] = "Fase 2. Jogo das perguntas.";

//jogo das perguntas
String perguntas[12] = {
 "O Bowser sempre sequestra Peach?",
 "Brasil ja ganhou mundial no LOL?",
 "O heroi de Halo eh chamado Master Chief?",
 "Minecraft foi lancado antes de 2010?",
 "Fortnite eh somente battle royale?",
 "COD eh uma serie de estrategia?",
 "Cosmog eh um pokemon lendario?",
 "Red Dead 2 se passa no Velho Oeste?",
 "The Sims eh um simulador de vida?",
 "GTA V se passa na cidade de Los Santos?",
 "Valorant tem 5 classes de agentes?",
 "Faker eh o nome do melhor player de LOL?",
 
};

//// Respostas corretas (0 para Nao, 1 para Sim)
int respostas[12] = {1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1};

bool perguntasUsadas[12] = {false};

char perguntaFinal[25] = "Onde tem tela roda DOOM?";

int respostaFinal = 1;


//sons de erro e acerto
void somAcerto(){
  tone(buzzer, 1000, 300);
}
void somErro(){
  tone(buzzer, 400, 300);
}
//som da vitoria com o hino do sao paulo futebol clube 
//melodia 
int hinoSaoPaulo[] = {
294,330,370,330,294,247,220,
220,220,294,294,330,330,247,247,294,277,
0,277,294,330,294,277,294,277,247,
0,247,277,294,277,330,294,247,220,
0,220,247,277,247,277,294,330,330,294,
330,294,330,370,415,330,440,440,
0,0,440,392,370,330,440,330,440,
330,220,247,277,247,247,220,
0,370,392,370,330,440,330,440,330,
440,440
};
//duração das notas
int duracao[] = {
3,8,8,8,8,8,2,
3,8,3,8,8,8,8,8,4,4,
4,3,8,8,8,8,8,2,4,
4,3,8,8,8,8,8,2,4,
4,3,8,8,8,8,8,2,3,8,
8,8,3,8,8,8,2,3,
8,4,4,4,4,4,4,4,4,
4,8,8,4,4,8,2,
8,4,4,4,2,2,4,4,4,
2,2

};;

int numNotas = sizeof(hinoSaoPaulo) / sizeof(int);
const int compasso = 1450;
//implementação no som de vitoria 
void somVitoria() {
  for (int nota = 0; nota < numNotas; nota++) {
    int tempo = compasso / duracao[nota]; 
    tone(buzzer, hinoSaoPaulo[nota], tempo); 
    delay(tempo * 1.2);
  }
}
void somPulou(){
  tone(buzzer,550,300);
}
void somDesistiu(){
  tone(buzzer,200,100);
}


//função para os jogos de led e perguntas

void startLedGame() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(jogoMem);
  delay(1500);
  for (int positionCounter = 0; positionCounter < strlen(jogoMem); positionCounter++) {
    lcd.scrollDisplayLeft();
     delay(200);
    if (!jogofuncionando) return;
  }
  delay(1000);
  lcd.clear();
  lcd.print("Prepare-se");
  delay(2000);
  lcd.clear();
  delay(500);
  

  for (int i = 0; i < numPiscar; i++) {
    sequencia[i] = random(12, 14); 
  }

  piscarLeds();
  lcd.print("Sua vez!");
  
  

  if (sequenciaUsuario()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(acertouS);
    somAcerto();
    delay(500);
    for (int positionCounter = 0; positionCounter < strlen(acertouS); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(300);
    if (!jogofuncionando) return;
      
    } 
    lcd.clear();
    
    delay(1500);
    lcd.print(jogoResp);
    delay(1500);
    for (int positionCounter = 0; positionCounter < strlen(jogoResp); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(300);
    if (!jogofuncionando) return;
    }
    
    //chama a função do jogo de perguntas:
    startJogoPerguntas();
    
    } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(errouS);
    somErro();
    delay(500);
    for (int positionCounter = 0; positionCounter < strlen(errouS); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(300);
      
  }
  }
  
  delay(500); 
}
//função para o jogo de perguntas 
void startJogoPerguntas() {
  int contadorAcertos = 0; 
  int pularPergunta = 1;  
  bool perguntasUsadas[12] = {false};  

  for (int i = 0; i < 5; i++) {
    int randomIndex;
    bool respondeu = false;
    bool respostaCorreta = false;

    do {
      randomIndex = random(0, 12); 
    } while (perguntasUsadas[randomIndex] == true);

    perguntasUsadas[randomIndex] = true; 

    lcd.clear();
    lcd.setCursor(0, 0);
    delay(1000);
    lcd.print(perguntas[randomIndex]); 
    delay(1500);

    for (int positionCounter = 0; positionCounter < perguntas[randomIndex].length(); positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(300); 
      if (!jogofuncionando) return;
    }

    
    lcd.clear();
    delay(500);
    lcd.print(perguntas[randomIndex]);  
    delay(2000); 

    unsigned long tempoLimite = millis() + 10000;  

    while (millis() < tempoLimite && !respondeu) {
      int tempoRestante = (tempoLimite - millis()) / 1000; 
      lcd.setCursor(0, 1);
      lcd.print("Tempo: ");
      lcd.print(tempoRestante);
      lcd.print(" ");

      // Verifica as respostas do jogador
      if (digitalRead(sButton) == LOW) {
        delay(50);
        if (digitalRead(sButton) == LOW) {
          respondeu = true;
          respostaCorreta = (respostas[randomIndex] == 1);
        }
      }

      if (digitalRead(nButton) == LOW) {
        delay(50); 
        if (digitalRead(nButton) == LOW) {
          respondeu = true;
          respostaCorreta = (respostas[randomIndex] == 0);  
        }
      }

      delay(100);  
    }
//compara a resposta do jogador com a resposta correta se correta continua se errada acaba o jogo
    if (respondeu && respostaCorreta) {
      contadorAcertos++;
      somAcerto();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Acertou!");
      lcd.setCursor(0, 1);
      lcd.print(contadorAcertos);
      lcd.print("/5");
      delay(2000);
    }
    else if (respondeu && !respostaCorreta) {
      somErro();
      lcd.clear();
      lcd.print(errouS);
      delay(2000);
      lcd.clear();
      lcd.print(frase);
      return; 
    }
    else if (!respondeu && pularPergunta > 0) {
      pularPergunta--;
      lcd.clear();
      lcd.print("Pulando pergunta...");
      delay(2000);
      
    }
    else {
      lcd.clear();
      lcd.print("Tempo esgotado!");
      delay(2000);
    somPulou();
      lcd.clear();
      lcd.print(frase);
      return;
    }
     if (!jogofuncionando) return;
  }

  if (contadorAcertos == 5 && jogofuncionando) {
    lcd.clear();
    lcd.print(perguntaFinal);
    delay(2000);
    for (int positionCounter = 0; positionCounter < strlen(frase); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(200);
    }
    lcd.print(perguntaFinal);
    
    unsigned long tempoLimiteFinal = millis() + 15000;  
    bool acertouPerguntaFinal = false;

    while (millis() < tempoLimiteFinal && !acertouPerguntaFinal) {
      int tempoRestante = (tempoLimiteFinal - millis()) / 1000; 
      lcd.setCursor(0, 1);
      lcd.print("Tempo: ");
      lcd.print(tempoRestante);

      if (digitalRead(sButton) == LOW) {
        delay(50);
        if (digitalRead(sButton) == LOW) {
          acertouPerguntaFinal = (respostaFinal == 1);
        }
      }

      if (digitalRead(nButton) == LOW) {
        delay(50);
        if (digitalRead(nButton) == LOW) {
          acertouPerguntaFinal = (respostaFinal == 0); 
        }
      }

      delay(100);
    }

    if (acertouPerguntaFinal) {
      lcd.clear();
      lcd.print("Venceu o jogo!");
      somVitoria();
      delay(5000);
    }
    else {
      lcd.clear();
      lcd.print(errouS);
      delay(5000);
      lcd.clear();
      lcd.print(frase);
      return;
    }
  }
}


//função para os leds
void piscarLeds() {
  for (int i = 0; i < numPiscar; i++) {
    digitalWrite(sequencia[i], HIGH);
    delay(500);
    digitalWrite(sequencia[i], LOW);
    delay(500); 
    if (!jogofuncionando) return;
  }
}
//verfica a sequencia utilizada pelo usuario no jogo dos leds 
bool sequenciaUsuario() {
  int contador = 0;  
  lcd.setCursor(0, 1); 
  lcd.print("Sequencia: 0");

  for (int i = 0; i < numPiscar; i++) {
    bool botaoPress = false;

    while (!botaoPress) {
      int sButtonValor = digitalRead(sButton);
      int nButtonValor = digitalRead(nButton);
      
      if (sButtonValor == LOW) {  
        delay(50);  
        if (digitalRead(sButton) == LOW) {  
          userInput[i] = LedG;
          botaoPress = true;

          contador++;
          lcd.setCursor(0, 1);
          lcd.print("Sequencia: ");
          lcd.print(contador);
          
          while (digitalRead(sButton) == LOW);
        }
      }

      if (nButtonValor == LOW) {
        delay(50);
        if (digitalRead(nButton) == LOW) {  
          userInput[i] = LedR;
          botaoPress = true;
          
          contador++;
          lcd.setCursor(0, 1);
          lcd.print("Sequencia: ");
          lcd.print(contador);

          while (digitalRead(nButton) == LOW);
        }
      }
      if (!jogofuncionando) return false;
    }
    if (userInput[i] != sequencia[i]) {
      return false;  
    }
  }

  return true;  
}
//função para iniciar o jogo ou desistir
void iniciarJogoo() {
  if (jogofuncionando) {
    iniciarJogo = false;  
    jogofuncionando = false;
    lcd.clear();
    delay(2000);
    lcd.print("Desistiu!");  
    somDesistiu();
    delay(5000);
    lcd.clear();
    lcd.print(frase);

    for (int positionCounter = 0; positionCounter < strlen(frase); positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(300);
    }
  } else {
    iniciarJogo = true;  
  }  
}

void setup(){
  lcd.begin(16, 2); 
  lcd.print(frase);
  delay(1000);
  for (int positionCounter = 0; positionCounter < strlen(frase); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }
  
  
  pinMode(startButton, INPUT_PULLUP);
  pinMode(sButton, INPUT_PULLUP);
  pinMode(nButton, INPUT_PULLUP);
  pinMode(LedG, OUTPUT);
  pinMode(LedR, OUTPUT);
  
  randomSeed(analogRead(A0));
  attachInterrupt(digitalPinToInterrupt(startButton), iniciarJogoo, FALLING);
}
//inicia o jogo
void loop() {
  if (iniciarJogo) {
    iniciarJogo = false;  
    jogofuncionando = true;
    startLedGame();       
  }
  
  delay(100);
}
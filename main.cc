#include <iostream>
#include <fstream>

using namespace std;

const int INF = INT_MAX/2;  
const int MAX = 1001;
string nomeArq;
unsigned short numLinha;
unsigned short camin[MAX][MAX];
int maiorValor[3];


int main(void){

   cout << "Digite o nome do arquivo a ser aberto (sem o .txt) : ";
   cin >> nomeArq;
   ifstream ark (nomeArq + ".txt");           // Realiza a abertura do arquivo


   if(!ark.is_open() ){                             // Verifica se o arquivo esta aberto
      cout << "ERROR! Arquivo nao encontrado \n";        
      return 0;
   } else{                                                
      cout << "Arquivo aberto com sucesso! \n";
   }

   ark >> numLinha;
   unsigned short repComp[numLinha][numLinha];

   for(int i = 0; i < numLinha; i++){
      for(int j = 0; j < numLinha; j++){
         repComp[i][j] = INF;
         camin[i][j] = i;
         if(i == j){
            repComp[i][j] = 0;          
         }
      }
   }

   while( !ark.eof() ){               //Conta o número de linhas do arquivo
      int aux1, aux2, aux3;
      ark >> aux1; 
      ark >> aux2;
      ark >> aux3;
      repComp[aux1][aux2] = aux3;  
      repComp[aux2][aux1] = aux3;  
   } 
   ark.close();
   ark.clear();


   //Programacao Dinamica
   for(int k=0; k < numLinha; k++){
      for(int i=0;i< numLinha;i++){
         for(int j=0;j< numLinha;j++){       
            if(repComp[i][k] + repComp[k][j] < repComp[i][j]){
               repComp[i][j] = repComp[i][k] + repComp[k][j];
               camin[i][j] = k;
            }      
         }
      }
   }

   for(int i = 0; i < numLinha; i++){
      for(int j = 0; j < numLinha; j++){
         if(repComp[i][j] > maiorValor[0]){
            maiorValor[0] = repComp[i][j];
            maiorValor[1] = i;
            maiorValor[2] = j;
         }
      }
   }

   string resposta;
   resposta += to_string(maiorValor[2]);

   int aux = maiorValor[2];
   int precedente;
   while(precedente != maiorValor[1]){
      precedente = camin[maiorValor[1]][aux];
      resposta = to_string(camin[maiorValor[1]][aux]) + " " + resposta;
      aux = precedente;
   }
   
   cout << nomeArq << "\n" << resposta << "\n" << maiorValor[0];

   return 0;
   } 
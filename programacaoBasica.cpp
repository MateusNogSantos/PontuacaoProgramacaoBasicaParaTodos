/*
Tabela para controle da pontuação da atividade em grupos do evento.
Evento:         Faixa etária de 12 a 15 anos.
Projeto:        Programação básica para todos.
Data de criação: 09/05/2026.

Etapas de funcionamento:

1° -> Leitura de equipes:   Digite a quantidade de equipes presentes no evento.
2° -> Leitura de atividades:    Digite uma tupla no formato "identificadorDaEquipe identificadorDaAtividade".

            identificadorDaEquipe : (n pertence à N | 1 <= n <= quantidade de equipes).
            identificadorDaAtividade :  0 - Ajuda
                                        1 - Conclusão de um exercício fácil.
                                        2 - Conclusão de um exercício médio.
                
3° -> Conclusão do Evento : Ao digitar "-1" o programa para e exibe a tabela final.

*/
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <stdexcept>
using namespace std;

class Grupo{

    friend class Evento;

    protected:

    int ajudas;

    private:

    int pontuacao;

    // Posição
    vector<int> exerciciosFaceis, exerciciosMedios;

    void adicionaPontuacaoFacil(int pos){
        exerciciosFaceis.push_back(pos);
        pontuacao += max((20 - pos),15);
    }

    void adicionaPontuacaoMedio(int pos){
        exerciciosMedios.push_back(pos);
        pontuacao += max((25 - pos),20);
    }

    void ajudou(){
        ajudas++;
        pontuacao += 8;
    }

    public:


    // Setters e Getters
    int getPontuacao(){return pontuacao;}
    int getExerciciosFaceis(){return exerciciosFaceis.size();}
    int getExerciciosMedios(){return exerciciosMedios.size();}

    // Construtor
    Grupo(): pontuacao(0),ajudas(0){
    }
    

};

class Evento{

    private:

    int qtdeEquipes;
    int posExerciciosFaceis;
    int posExerciciosMedios;
    vector<Grupo> equipe;

    public:

    Evento(int numeroEquipes){
        qtdeEquipes = numeroEquipes;
        equipe.resize(qtdeEquipes,Grupo());
        posExerciciosFaceis = 0;
        posExerciciosMedios = 0;
    }

    void concluiuExercicioMedio(int indiceEquipe){

        if(indiceEquipe < 1 || indiceEquipe > qtdeEquipes)throw runtime_error("Índice inválido");
        else{
            equipe[indiceEquipe - 1].adicionaPontuacaoMedio(posExerciciosMedios);
            posExerciciosMedios++;
        }
    }

    void concluiuExercicioFacil(int indiceEquipe){

        if(indiceEquipe < 1 || indiceEquipe > qtdeEquipes)throw runtime_error("Índice inválido");
        else{
            equipe[indiceEquipe - 1].adicionaPontuacaoFacil(posExerciciosFaceis);
            posExerciciosFaceis++;
        }
    }

    void ajudou(int indiceEquipe){

        if(indiceEquipe < 1 || indiceEquipe > qtdeEquipes)throw runtime_error("Índice inválido");
        else equipe[indiceEquipe - 1].ajudou();
    }

    // Pontuação : Equipe
    priority_queue<pair<int,int>,vector<pair<int,int>>,less<pair<int,int>>> mostrarTabela(){


    priority_queue<pair<int,int>,vector<pair<int,int>>,less<pair<int,int>>> result;

    for(int i = 0;i < qtdeEquipes;i++){
        pair<int,int> tempTupla;
        tempTupla.second = i + 1;
        tempTupla.first = equipe[i].getPontuacao();
        result.push(tempTupla);
    }

    return result;

    }

    int getAjudas(int i){return equipe[i].ajudas;}
    int getExerciciosFaceis(int i){return equipe[i].getExerciciosFaceis();}
    int getExerciciosMedios(int i){return equipe[i].getExerciciosMedios();}


};

int main(){

    int n;

    cout << "Digite a quantidade de equipes." << endl;
    cin >> n;

    Evento event(n);

    bool continuar = true;

        while(continuar){

            int tempType,tempIndex;
            string warning = "";

            cout << "-------------------------------------------------------------" << endl;

            cout << "Digite o id do grupo e o tipo da atividade(0 para ajuda,1 para facil,2 para medio)"<< endl;

            cin >> tempIndex;

            try{
                if(tempIndex != -1){
                    cin >> tempType;
                    switch(tempType){
                    case 0:
                    event.ajudou(tempIndex);
                    break;
                    case 1:
                    event.concluiuExercicioFacil(tempIndex);
                   break;
                    case 2:
                    event.concluiuExercicioMedio(tempIndex);
                    break;
                    break;
                    default:
                    warning = "comando não valido,atividade não registrada";
                    }
                }else continuar = false;
            }catch(const runtime_error& e){
                warning = e.what();
            }

        system("clear");

        if(!warning.empty())cout << warning << endl;

        priority_queue<pair<int,int>,vector<pair<int,int>>,less<pair<int,int>>> table = event.mostrarTabela();

        cout << endl;
        for(int i = 0;i < n;i++){
            pair<int,int> tempTupla = table.top();
            table.pop();
            cout << i+1 << "-> Equipe " <<  tempTupla.second << "  Ajudas: " << event.getAjudas(i) << 
            "   Exercícios do nível fácil: " << event.getExerciciosFaceis(i) << "   Exercícios do nível médio: " <<
            event.getExerciciosMedios(i) << "   Total: " << tempTupla.first << endl;
        }
    }

    return 0;
}
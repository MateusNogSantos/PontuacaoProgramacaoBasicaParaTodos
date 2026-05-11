#include "programacaoBasica.h"
#include <algorithm>
#include <iostream>

using namespace std;

Grupo::Grupo()
    : ajudas(0), pontuacao(0) {
}

void Grupo::adicionaPontuacaoFacil(int pos) {
    exerciciosFaceis.push_back(pos);
    pontuacao += max((20 - pos), 15);
}

void Grupo::adicionaPontuacaoMedio(int pos) {
    exerciciosMedios.push_back(pos);
    pontuacao += max((25 - pos), 20);
}

void Grupo::ajudou() {
    ajudas++;
    pontuacao += 8;
}

Evento::Evento(int numeroEquipes)
    : qtdeEquipes(numeroEquipes),
      posExerciciosFaceis(0),
      posExerciciosMedios(0),
      equipe(numeroEquipes, Grupo()) {
}

void Evento::concluiuExercicioMedio(int indiceEquipe) {
    if (indiceEquipe < 1 || indiceEquipe > qtdeEquipes)
        throw runtime_error("Índice inválido");

    equipe[indiceEquipe - 1].adicionaPontuacaoMedio(posExerciciosMedios);
    posExerciciosMedios++;
}

void Evento::concluiuExercicioFacil(int indiceEquipe) {
    if (indiceEquipe < 1 || indiceEquipe > qtdeEquipes)
        throw runtime_error("Índice inválido");

    equipe[indiceEquipe - 1].adicionaPontuacaoFacil(posExerciciosFaceis);
    posExerciciosFaceis++;
}

void Evento::ajudou(int indiceEquipe) {
    if (indiceEquipe < 1 || indiceEquipe > qtdeEquipes)
        throw runtime_error("Índice inválido");

    equipe[indiceEquipe - 1].ajudou();
}

// Pontuação : Equipe
priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> Evento::mostrarTabela() {
    priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> result;

    for (int i = 0; i < qtdeEquipes; i++) {
        pair<int,int> tempTupla;
        tempTupla.second = i + 1;
        tempTupla.first = equipe[i].getPontuacao();
        result.push(tempTupla);
    }

    return result;
}

int Evento::getAjudas(int i) {
    return equipe[i].ajudas;
}

int Evento::getExerciciosFaceis(int i) {
    return equipe[i].getExerciciosFaceis();
}

int Evento::getExerciciosMedios(int i) {
    return equipe[i].getExerciciosMedios();
}

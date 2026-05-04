#pragma once //inclui o arquivo apenas uma vez mesmo com vários .cpp
#include <vector> //biblioteca de vetores c++
#include <limits> //da acesso a valores limites de tipos numericos
#include <string> //biblioteca de texto

//Ao invés de escrever vector<vector<double>> toda vez escrevemos Matriz
using Matriz = std::vector<std::vector<double>>;

//-------DECLARAÇÃO DAS FUNÇÕES-------

//lê um arquivo .txt e retorna a matriz de distâncias
Matriz lerMatriz(const std::string& filename);

//calcula o custo total de um caminho completo
double custoTotal(const Matriz& dist, const std::vector<int>& caminho);

// ──────────────────────────────────────────────
// Algoritmo Exato: Held-Karp
// ──────────────────────────────────────────────
// Complexidade: O(n² * 2^n) em tempo, O(n * 2^n) em memória
// Retorna o custo ótimo e preenche 'caminho' com a rota encontrada
double heldKarp(const Matriz& dist, std::vector<int>& caminho);

// ──────────────────────────────────────────────
// Algoritmo Aproximativo: 2-aproximado via MST
// ──────────────────────────────────────────────
// Passo 1 – Prim:  constrói a Árvore Geradora Mínima
// Passo 2 – DFS:   percorre a MST em pré-ordem (visita cada nó uma vez)
// Garantia:  custo(resultado) ≤ 2 * custo(ótimo)
double doisAprox(const Matriz& dist, std::vector<int>& caminho);
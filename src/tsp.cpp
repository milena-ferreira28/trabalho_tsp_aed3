#include "tsp.h" //inclui o header
#include <fstream> //permite ler e escrever em arquivos
#include <iostream> //entrada e saída paadrão
#include <stdexcept> //exceções padrao do c++
#include <algorithm> //funções utilitárias para coleções
#include <sstream> // permite tratar strings como fluxo (como se fosse um arquivo)
#include <cmath> //funções matemáticas

// ================================================================
// lerMatriz — lê o arquivo .txt e monta a matriz de distâncias
// ================================================================
Matriz lerMatriz(const std::string& filename) {

    // abre o arquivo para leitura
    std::ifstream file(filename);

    // verifica se o arquivo foi aberto corretamente
    if (!file.is_open())
        // se não abriu, lança um erro com o nome do arquivo
        throw std::runtime_error("Erro ao abrir arquivo: " + filename);

    // matriz que será preenchida e retornada
    Matriz dist;

    // variável para armazenar cada linha do arquivo como texto
    std::string linha;

    // lê o arquivo linha por linha
    while (std::getline(file, linha)) {

        // transforma a linha (string) em um fluxo de leitura
        // assim conseguimos extrair números dela com >>
        std::istringstream iss(linha);

        // vetor para armazenar os valores de uma linha da matriz
        std::vector<double> row;

        // variável auxiliar para cada número lido
        double valor;

        // lê todos os números da linha atual
        while (iss >> valor)
            row.push_back(valor);

        // se a linha não estiver vazia, adiciona à matriz
        if (!row.empty())
            dist.push_back(row);
    }

    // retorna a matriz completa
    return dist;
}

// ================================================================
// custoTotal — calcula o custo total de uma volta completa
// ================================================================
double custoTotal(const Matriz& dist, const std::vector<int>& caminho) {

    //acumula o custo total das arestas percorridas
    double custo = 0.0;

    // .size() retorna o número de elementos do vetor caminho
    int n = caminho.size();

    //percorre os pares consecutivos
    for (int i = 0; i < n - 1; i++)
        //distancia entre o vertice atual e o próximo
        custo += dist[caminho[i]][caminho[i + 1]];

    //adiciona o custo de voltar ao vertice inicial
    custo += dist[caminho[n - 1]][caminho[0]];

    return custo;
}

// ================================================================
// heldKarp — algoritmo exato
// ================================================================
double heldKarp(const Matriz& dist, std::vector<int>& caminho) {

    // .size() retorna o número de linhas da matriz = nº de vértices
    int n = dist.size();

    //inf = custo impossível
    const double INF = std::numeric_limits<double>::infinity();

    //subTotal = numero total de subconjuntos de vertices = 2^n
    int subTotal = 1 << n; //desloca o bit 1 pra esquerda n vezes (2^n)

    //Tabela dp: dp[mask][v] = menor custo chegando em v tendo visitado os vértices em 'mask'.
    //inicializa com inf (custo desconhecido)
    std::vector<std::vector<double>> dp(subTotal, std::vector<double>(n, INF));

    // Tabela parent: guarda DE ONDE viemos para reconstituir o caminho
    std::vector<std::vector<int>> parent(subTotal, std::vector<int>(n, -1));

    //mask = 1 --> só o vertice 0 foi visitado
    dp[1][0] = 0.0;

    //passa por todos os subconjuntos possíveis de vértices
    for (int mask = 1; mask < subTotal; mask++) {

        //pra cada vertice v que esta no subconjunto mask
        for (int v = 0; v < n; v++) {
            //verifica se o bit v esta ligado em mask
            if (!(mask & (1 << v))) continue;

            //se o custo pra chegar aqui ainda é inf, o estado nunca foi alcançado
            if (dp[mask][v] == INF) continue;

            //tenta expandir para cada vértice u ainda não visitado
            for (int u = 0; u < n; u++) {
                //se u ja esta em mask, pula
                if (mask & (1 << u)) continue;

                //adiciona u ao conjunto
                int novoMask = mask | (1 << u);

                //custo de ir de v para u, somado ao custo de chegar em v
                double novoCusto = dp[mask][v] + dist[v][u];

                //se encontrar um caminho mais barato, atualiza a tabela
                if (novoCusto < dp[novoMask][u]) {
                    dp[novoMask][u] = novoCusto;
                    //guarda que viemos de v pra reconstruir o caminho
                    parent[novoMask][u] = v;
                }
            }
        }
    }

    //fullMask = todos os vertices visitados
    int fullMask = subTotal - 1;

    //encontra o melhor vertice pra fechar o ciclo voltando ao 0
    double best = INF;
    int lastNode = -1;

    //testa cada vertice v (exceto 0) como ultimo antes de voltar ao inicio
    for (int v = 1; v < n; v++) {
        if (dp[fullMask][v] == INF) continue;
        //custo total = custo de chegar em v + custo de voltar ao vertice 0
        double total = dp[fullMask][v] + dist[v][0];
        if (total < best) {
            best = total;
            lastNode = v; //guarda qual foi o melhor ultimo vertice
        }
    }

    //RECONSTROI O CAMINHO
    //Segue os ponteiros de trás pra frente
    caminho.clear(); //garante que o vetor esta vazio antes de preencher

    int mask = fullMask; //começa com todos visitados
    int atual = lastNode; //começa do último vertice

    //enquanto houver vertice anterior, volta pelo caminho
    while (atual != -1) {
        caminho.push_back(atual); //adiciona vertice atual ao caminho

        int prev = parent[mask][atual]; //quem veio antes de atual?

        //remove atual do conjunto
        mask ^= (1 << atual);

        atual = prev; //avança para o vertice anterior
    }

    // begin() aponta para o primeiro elemento, end() para depois do último
    std::reverse(caminho.begin(), caminho.end());

    return best;
}

// =========================================================
// dfsHelper - função auxiliar recursiva para o DFS na MST
// =========================================================
static void dfsHelper(int node, const std::vector<std::vector<int>>& adjMST, std::vector<bool>& visitado, std::vector<int>& caminho) {

    //Marca o nó atual como visitado para nao voltar nele
    visitado[node] = true;

    //adiciona o nó ao caminho na ordem em que é visitado (pré-ordem)
    caminho.push_back(node);

    //visita cada vizinho do nó atual na MST
    for (int vizinho : adjMST[node]) {
        //só visita o vizinho se ele ainda nao foi visitado
        if (!visitado[vizinho])
            dfsHelper(vizinho, adjMST, visitado, caminho);
    }
}

// =========================================================
// doisAprox - algoritmo 2-aproximado via MST (Prim) + DFS
// =========================================================

double doisAprox(const Matriz& dist, std::vector<int>& caminho) {

    
    int n = dist.size();
    const double INF = std::numeric_limits<double>::infinity();

    //PASSO 1 - ALGORITMO DE PRIM

    // key[v] = menor custo conhecido para conectar v à MST.
    // Começa INF para todos (nenhum vértice conectado ainda).
    std::vector<double> key(n, INF);

    // mstParent[v] = qual vértice já na MST conecta v.
    // usado para reconstruir as arestas da árvore.
    std::vector<int> mstParent(n, -1);

    // inMST[v] = true se o vértice v já foi adicionado à MST.
    std::vector<bool> inMST(n, false);

    // Começa pelo vértice 0: custo 0 para entrar na MST.
    key[0] = 0.0;

    // Repete n vezes — adiciona um vértice à MST por iteração.
    for (int iter = 0; iter < n; iter++) {

        // Encontra o vértice FORA da MST com menor key.
        int u = -1;
        for (int v = 0; v < n; v++)
            // Se v não está na MST E (ainda não escolhemos nenhum OU v é mais barato):
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;

        // Marca u como parte da MST.
        inMST[u] = true;

        // Atualiza as keys dos vizinhos de u que ainda não estão na MST.
        for (int v = 0; v < n; v++) {
            // Se v não está na MST E a aresta u→v é mais barata que a key atual de v:
            if (!inMST[v] && dist[u][v] < key[v]) {
                key[v]       = dist[u][v]; // atualiza o custo mínimo para alcançar v
                mstParent[v] = u;          // u é o melhor vizinho para conectar v
            }
        }
    }

    // Constrói a lista de adjacência da MST a partir dos parents.
    // adjMST[v] = lista de vértices vizinhos de v NA MST.
    std::vector<std::vector<int>> adjMST(n);

    // Para cada vértice v (exceto a raiz 0), adiciona a aresta
    // (mstParent[v] ↔ v) na lista de adjacência — em AMBAS direções
    // porque a MST é não-direcionada.
    for (int v = 1; v < n; v++) {
        int u = mstParent[v];
        adjMST[u].push_back(v); // aresta de u para v
        adjMST[v].push_back(u); // aresta de v para u (não-direcionada)
    }

    // PASSO 2: DFS PRÉ-ORDEM

    caminho.clear(); // limpa o vetor antes de preencher

    // visitado[v] = true se o vértice v já foi incluído no caminho.
    // Começa tudo false (nenhum visitado ainda).
    std::vector<bool> visitado(n, false);

    // Inicia o DFS pelo vértice 0.
    // A função vai preencher 'caminho' recursivamente.
    dfsHelper(0, adjMST, visitado, caminho);

    // custoTotal calcula o custo total do caminho gerado pelo DFS.
    
    return custoTotal(dist, caminho);
}
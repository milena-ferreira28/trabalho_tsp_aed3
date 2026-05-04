#include "tsp.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>

void runInstance(const std::string& filename, double otimo) {

    // Imprime um separador visual e o nome da instância.
    std::cout << "\n========================================\n";
    std::cout << "Instancia: " << filename << "\n";
    std::cout << "Custo otimo esperado: " << otimo << "\n";
    std::cout << "========================================\n";

    // Declara a variável que vai guardar a matriz de distâncias.
    Matriz dist;

    // try/catch: tenta executar o código, captura erros se falhar
    try {
        dist = lerMatriz(filename);
    } catch (const std::exception& e) {
        std::cerr << "  ERRO: " << e.what() << "\n";
        return;
    }

    // .size() retorna o número de linhas da matriz = nº de vértices
    int n = dist.size();
    std::cout << "Numero de vertices: " << n << "\n\n";

    // ── ALGORITMO APROXIMATIVO ───────────────────────────────────
    {
        std::vector<int> caminho;

        // high_resolution_clock é o relógio de maior precisão disponível
        // now() captura o instante atual
        auto start = std::chrono::high_resolution_clock::now();

        //executa o algoritmo aproximativo
        double custo = doisAprox(dist, caminho);

        // Captura o tempo após a execução.
        auto end = std::chrono::high_resolution_clock::now();

        // duration<double> calcula a diferença entre dois instantes e converte para segundos
        // .count() extrai o valor numérico da duração
        double elapsed = std::chrono::duration<double>(end - start).count();

        // Razão entre o custo encontrado e o ótimo conhecido.
        double ratio = custo / otimo;

        //imprime o resultado
        std::cout << "[2-APROXIMADO (MST + DFS)]\n";
        std::cout << "  Custo encontrado : " << std::fixed << std::setprecision(2) << custo << "\n";
        std::cout << "  Razao c/ otimo   : " << std::fixed << std::setprecision(4) << ratio << "x\n";
        std::cout << "  Tempo            : " << std::fixed << std::setprecision(6) << elapsed << "s\n";

        // Imprime a sequência de vértices do caminho
        std::cout << "  Caminho          : ";
        for (int v : caminho)
            std::cout << v << " ";
        std::cout << "0\n"; // mostra o retorno ao vértice inicial
    }

    // ── ALGORITMO EXATO: HELD-KARP ───────────────────────────────
    std::cout << "\n[HELD-KARP (Exato)]\n";

    if (n > 24) {
        std::cout << "  n=" << n << " > 24, impraticavel.\n";
        std::cout << "  Use a estimativa de tempo no relatorio.\n";
        return;
    }

    std::vector<int> caminho;

    auto start = std::chrono::high_resolution_clock::now();
    double custo = heldKarp(dist, caminho);
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed = std::chrono::duration<double>(end - start).count();

    std::cout << "  Custo encontrado : " << std::fixed << std::setprecision(2) << custo << "\n";
    std::cout << "  Tempo            : " << std::fixed << std::setprecision(6) << elapsed << "s\n";

    std::cout << "  Caminho          : ";
    for (int v : caminho)
        std::cout << v << " ";
    std::cout << "0\n";
}

// INT MAIN
int main() {
    struct Instance {
        std::string file; //caminho do arquivo
        double otimo;     //custo otimo
    };

    //Lista com as 5 instancias do trabalho
    std::vector<Instance> instances = {
        {"instances/tsp1_253.txt",    253.0},
        {"instances/tsp2_1248.txt",  1248.0},
        {"instances/tsp3_1194.txt",  1194.0},
        {"instances/tsp4_7013.txt",  7013.0},
        {"instances/tsp5_27603.txt", 27603.0},
    };

    // Cabeçalho visual no terminal.
    std::cout << "TSP - Held-Karp + 2-Aproximado (MST)\n";

    // Percorre cada instância e executa os algoritmos.
    for (auto& inst : instances)

        runInstance(inst.file, inst.otimo);

    std::cout << "\nFim da execucao.\n";
    return 0;
}
# Trabalho TSP — Milena & Kananda

Trabalho da disciplina **Algoritmos e Estruturas de Dados III — UFPel**
Implementação de soluções para o Problema do Caixeiro Viajante (TSP):

* **Held-Karp** (algoritmo exato)
* **2-Aproximado via MST + DFS** (algoritmo aproximativo)

**Linguagem:** C++17

---

## 📁 Estrutura de Pastas

```
Trabalho_TSP_Milena_Kananda/
├── include/
│   └── tsp.h          ← declarações de funções e tipos
├── src/
│   ├── tsp.cpp        ← implementação dos algoritmos
│   └── main.cpp       ← leitura de arquivos, execução e saída
├── instances/
│   ├── tsp1_253.txt
│   ├── tsp2_1248.txt
│   ├── tsp3_1194.txt
│   ├── tsp4_7013.txt
│   └── tsp5_27603.txt
├── Makefile
└── README.md
```

---

## ⚙️ Pré-requisitos

* Compilador **g++** com suporte a C++17
  Linux/macOS:

  ```
  g++ --version
  ```

  Windows (MSYS2/MinGW):

  ```
  pacman -S mingw-w64-x86_64-gcc
  ```

---

## 🛠️ Como Compilar

Dentro da pasta do projeto:

```
make
```

Isso gera o executável `tsp.exe` (Windows) ou `tsp` (Linux).

Para limpar arquivos compilados:

```
make clean
```

---

## ▶️ Como Executar

### Executar todas as instâncias:

```
make run
# ou
./tsp
```

### Executar manualmente:

```
./tsp
```

O programa já está configurado para rodar automaticamente todas as instâncias da pasta `instances/`.

---

## 📄 Formato dos Arquivos de Instância

Cada arquivo `.txt` contém **apenas a matriz de adjacência**, sem o número de vértices na primeira linha.

Exemplo:

```
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
```

O número de vértices é determinado automaticamente pela leitura do arquivo.

---

## 📊 Saída do Programa

Para cada instância, o programa imprime:

* número de vértices
* custo encontrado
* tempo de execução
* caminho percorrido
* razão entre custo aproximado e ótimo

Exemplo:

```
[2-APROXIMADO (MST + DFS)]
  Custo encontrado : 281.00
  Razao c/ otimo   : 1.1107x
  Tempo            : 0.000008s

[HELD-KARP (Exato)]
  Custo encontrado : 253.00
  Tempo            : 0.000680s
```

Para instâncias grandes (n > 24), o algoritmo exato não é executado devido ao alto custo computacional.

---

## 📈 Complexidade dos Algoritmos

| Algoritmo         | Tempo       | Memória    | Garantia            |
| ----------------- | ----------- | ---------- | ------------------- |
| Held-Karp         | O(n² × 2^n) | O(n × 2^n) | Solução ótima       |
| 2-Aprox (MST+DFS) | O(n²)       | O(n²)      | ≤ 2 × solução ótima |

---

## 👩‍💻 Autoras

* Milena Alves Ferreira
* Kananda (completar nome, se quiser)

---

## 📌 Observações

* O algoritmo exato (Held-Karp) torna-se inviável para instâncias maiores devido à sua complexidade exponencial.
* O algoritmo aproximativo apresenta execução extremamente rápida e resultados próximos do ótimo, sendo adequado para problemas maiores.

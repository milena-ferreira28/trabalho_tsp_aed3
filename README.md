# TSP — Held-Karp + 2-Aproximado via MST

Trabalho de Algoritmos e Estruturas de Dados III — UFPel  
Algoritmos: **Held-Karp** (exato) e **2-Aproximado MST+DFS** (aproximativo)  
Linguagem: **C++17**

---

## Estrutura de Pastas

```
tsp_project/
├── include/
│   └── tsp.h          ← declarações de funções e tipos
├── src/
│   ├── tsp.cpp        ← implementação dos algoritmos
│   └── main.cpp       ← leitura de arquivos, medição de tempo, saída
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

## Pré-requisitos

- **g++** com suporte a C++17  
  Linux/macOS: `g++ --version`  
  Windows (MSYS2/MinGW): `pacman -S mingw-w64-x86_64-gcc`

---

## Como Compilar

```bash
# Dentro da pasta tsp_project/
make
```

Isso gera o executável `./tsp`.

Para limpar:
```bash
make clean
```

---

## Como Executar

### Rodar todas as instâncias de uma vez:
```bash
make run
# ou
./tsp
```

### Rodar uma instância específica:
```bash
./tsp instances/tsp1_253.txt
```

---

## Formato dos Arquivos de Instância

Cada arquivo `.txt` contém:
- Linha 1: `N` (número de vértices)
- Linhas seguintes: matriz N×N de distâncias (separadas por espaço)

Exemplo (`tsp2_1248.txt`, 6 vértices):
```
6
0  10  20  ...
10  0  15  ...
...
```

---

## Saída Esperada

```
[2-APROXIMADO (MST + DFS)]
  Custo encontrado : 281.00
  Razão c/ ótimo   : 1.1107x
  Tempo            : 0.000006s
  Tour             : 0 3 7 1 5 ...

[HELD-KARP (Exato)]
  Custo encontrado : 253.00
  Tempo            : 0.005927s
  Tour             : 0 2 5 1 ...
```

Para instâncias com n > 24, o Held-Karp é pulado automaticamente
(memória necessária seria impraticável: n × 2^n células).

---

## Complexidades

| Algoritmo          | Tempo          | Memória       | Garantia       |
|--------------------|----------------|---------------|----------------|
| Held-Karp          | O(n² × 2^n)    | O(n × 2^n)    | Solução ótima  |
| 2-Aprox (MST+DFS)  | O(n²)          | O(n²)         | ≤ 2 × ótimo    |
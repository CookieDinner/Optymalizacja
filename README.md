# Kolorowanie grafu - GA

1. Zachłanny z każdego wierzchołka -> początkowa populacja chromosomów (n) + dodatkowo dopełnienie do liczby M całej populacji.

2. Te dodatkowe dopełnienia czyścimy (żeby kolorowanie się zgadzało).
...

Potrzebne funkcje:
- fitness() - [nadawanie oceny każdemu chromosomowi - liczba kolorów] - [wpisuje do tablicy ocen <n-1> ]

- chooseparents() - [wybiera dwóch parent'ów do crossingu na podstawie czegoś tam] - [jedna lub dwie funkcje tego typu] - [zwraca tych parentów do funkcji poniższej]

- crossover() - [losuje w chromosomach parent'ów (taki sam w obu) punkt crossingu i wrzuca do child'a, do tego punktu, z 1. parenta i, od tego punktu, z 2. parenta] - [Zawiera parametr prawdopodobieśtwa wystąpienia CROSS_CHANCE = 50% populacji].

PS. W przypadku gdy istnieją nowo wylosowane chromosomy, które są pokolorowane niepoprawnie - naprawiamy je (albo kolejno po stworzeniu albo na końcu po stworzeniu wszystkich nowych).

PS2. Zabijamy CROSS_CHANCE najgorszych chromosomów

- mutation() - [mutuje wybrany chromosom z prawdobodobieństwem wystąpienia MUTATION_CHANCE = np. 5%]

3. Wykonanie powyższych funkcji dla danej populacji i zastąpienie najgorszych chromosomów nowymi chromosomami.

4. Powtarzanie puktu 3. do momentu braku lepszego wyniku w np. 5-10 (lub więcej) ostatnich wykonań albo jakiejś tam liczby wykonań do tego momentu. STOP_MOMENT

5. Wybranie najlepszego chromosomu z obecnej populacji - Wynik (liczba kolorów).

Define'y:
- POPULATION
- CROSS_CHANCE
- MUTATION_CHANCE
- STOP_MOMENT

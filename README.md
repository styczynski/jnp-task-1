# JNP Task 1 (University of Warsaw)

Contributors: 

* @styczynski
* @joald

## Building

Please run `make` to build everything.
Run `make rebuild` to force rebuild.
Run `make clean` to clean compilation files.

## Task Description

### Task "Points"

This year we introduced negative points for multiple
cooperation with the same person during this course .
To better understand the principle of disposing negative points bonus
and help us calculate them, please write the appropriate program.

### Functional requirements

The program is called with one argument, which is the name of the file
containing IDs of the students participating in the assignments.
Each Identifier is placed in a separate line.
The correct student ID consists of two lower case letters of the English alphabet and six digits
or two small letters of English alphabet, letter m, a hyphen and four digits.

After loading a list of student IDs from the file, the program reads from
standard input descriptions of teams that solved individual tasks.
Each description resides in a separate line. A proper description of the team consists of
word "Grupa" (pol. group), group number (number from 1 to 8), semicolon, word "zadanie" (pol. task),
task number (number from 1 to 6), semicolon and student identifiers
separated by a plus sign.

After processing all the descriptions of the teams the program prints to the standard
output the list of students to substrac points and then exit with code 0.
Each line written to the output is composed of student
index number (six of the last characters of its identifier), semicolon, the number of points
to be substracted and the terminating semicolon. The data is sorted by index numbers.

### Error handling

The program must be resistant to data incompatible with the specification.
The error messages described below should be written to the standard error output.

If a program has been called with an invalid number of parameters, it should
exit with code 0 printing the following statement

` Usage: PROGRAM file `

where `PROGRAM` is the program name given in the command line
(zero argument passed to the main function).

If a program cannot open a file given as an argument or
any other error occurs when handling the file, it should
output a message:

` Error: problem with file FILE `

where `FILE` is the name of the file (the first argument passed to main)
and they will end up with code 1.

For each line read from a file that does not contain a valid
student identifier, the program should print the following message

` Error in FILE, line N: TEXT `

where `FILE` is the file name, `N` is the line number, and `TEXT` is the original
line that was loaded.

For each input line read from a line of the file that contains the valid
student ID, but such ID has already occurred, program should output a message:

` Error in FILE, line N: ID `

where `FILE` is the file name, `N` is the line number, and the `ID` is
duplicate student ID.

The program prints erroneous lines in the file in the order of increasing line mnumbers.

For each line read from the standard input, which does not contain the correct
team description, the program should print the following message:

` Error in cin, line N: TEXT `

where `N` is the line number and `TEXT` is the original form of the loaded line.

If the team description is correct, there may be two reasons for questioning
the student ID: 

* it did not appear in the file passed as program argument, 

* it repeats in the same team. 

In case of questioning the student ID, the program should output a message:

` Error in cin, line 4: ID `

where `N` is the line number and `ID` is the contested student ID.

The program outputs erroneous lines from the standard input
in the order of ascending line numbers, and messages about questioned identifiers
in the order they appear in the team's description.
For the invalid ids points are not counted!

Lines are numbered from 1.
Empty lines should be ignored, but they will matter when it comes to numbering.
Any white characters in non-empty lines should be treated as
invalid and program should print them in output messages.

### Usage example

List of student IDs in _test_1.file:

```

ab111111
cd222222
ef333333
gh444444
ij555555
ab111111
ab01234
cab12345
ZZM-1000

```

List of team descriptions:

```

grupa1/zadanie1/ab111111+cd222222
grupa2/zadanie1/gh444444+ij555555
grupa1/zadanie2/ab111111+cd222222+ef333333
grupa2/zadanie2/gh444444 + ij555555
grupa1/zadanie3/ab111111+cd222222+pr999999
grupa1/zadanie4/cd222222+cd222222
grupa1/zadanie5/cd222222+cd222222+cd222222
grupa1/zadanie5/cd222222+cd222222+ab111111
grupa1/zadanie5/cd222222+cd222222+pr999999
grupa1/zadanie5/pr999999+pr999999+pr999999
grupa1/zadanie2/ab111111+ef333333


```

The program outputs to the standard output:

```

111111; 7;
222222; 6;
333333; 1;

```

The program writes to the standard error output:

```

Error in _test_1.file, line 6: ab111111
Error in _test_1.file, line 7: ab01234
Error in _test_1.file, line 8: cab12345
Error in cin, line 4: grupa2/zadanie2/gh444444 + ij555555
Error in cin, line 5: pr999999
Error in cin, line 6: cd222222
Error in cin, line 7: cd222222
Error in cin, line 7: cd222222
Error in cin, line 8: cd222222
Error in cin, line 9: cd222222
Error in cin, line 9: pr999999
Error in cin, line 10: pr999999
Error in cin, line 10: pr999999
Error in cin, line 10: pr999999


```

### Formal requirements

The program will be compiled on the student machine with a command

`g++ -Wall -Wextra -O2 -std=c++17 punkty.cc -o punkty`

Expected solution should not contain definitions of own structures and classes!
Instead, you should use containers and algorithms
provided by the standard C++ language library extensively.
Input and output operations should be implemented using C++ streams.

The solution should reside in the file `points.cc`, which shall be placed
in the SVN repository in the directory

`grupaN/zadanie1/ab123456+cd123456`

or

`grupaN/zadanie1/ab123456+cd123456+ef123456`

where `N` is the group number, and `ab123456, cd123456, ef123456` are identifiers
of the members of the team submitting this solution.
Catalog with solution should contain no additional files to the source code,
but may contain a subdirectory `"private"` where you can place other files, such as your tests.
Files placed in subdirectories are not evaluated.
Do not place in the repository large, binary, temporary or any other way unnecessary files.

**English translation done by @styczynski (MIT license)**

## Opis zadania

### Zadanie punkty

W tym roku wprowadziliłmy na tym przedmiocie punkty ujemne za wielokrotną
współpracę z tą samą osobą. Aby lepiej zrozumieć zasady odejmowania tych punktów
i pomóc nam je policzyć, prosimy o napisanie stosownego programu.

### Wymagania funkcjonalne

Program wywoływany jest z jednym argumentem, który jest nazwą pliku
zawierającego identyfikatory studentów uczestniczących w zająciach.
Każdy identyfikator znajduje się w osobnej linii.
Poprawny identyfikator studenta składa sią z dwóch małych liter alfabetu angielskiego
i szejściu cyfr albo z dwóch małych liter alfabetu angielskiego, litery m, łącznika
i czterech cyfr.

Po wczytaniu z pliku listy identyfikatorów studentów program
czyta ze standardowego wejłcia opisy zespołów,
które rozwiązywały poszczególne zadania.
Każdy opis znajduje sią w osobnej linii.
Poprawny opis zespołu składa sią ze słowa grupa, numeru grupy,
bądącego liczbą od 1 do 8, ukośnika, słowa "zadanie",
numeru zadania (bądącego liczbą od 1 do 6), ukośnika i identyfikatorów studentów
oddzielonych znakiem plus.

Po przetworzeniu wszystkich opisów zespołów program wypisuje na standardowe
wyjscie liste studentów, którym należy odjąć punkty, a nastąpnie kończy się
kodem wykonania 0. Każda wypisywana linia składa sią z numeru indeksu studenta
(sześć ostatnich znaków jego identyfikatora), średnika, liczby punktów do odjącia
i średnika.
Wypisywane dane są posortowane według numerów indeksów.

### Obsługa błądów

Program musi byą odporny na niezgodności danych wejściowych ze specyfikacją.
Opisane poniżej komunikaty o błądach powinny byą wypisywane na standardowe
wyjście błędów.

Jeśli program został wywołany ze złą liczbą parametrów, powinien wypisać
komunikat:

` Usage: PROGRAM file `

gdzie `PROGRAM` jest nazwą programu, jaką podano w linii poleceń
(zerowy argument przekazany do funkcji main), a nastąpnie zakołczyć sią z kodem 1.

Jeśli program nie może otworzyć pliku o nazwie podanej jako argument lub
wystąpił jakiś inny błąd związany z obsługą pliku, powinien wypisać komunikat:

` Error: problem with file PLIK `

gdzie `PLIK` jest nazwą pliku
(pierwszy argument przekazany do funkcji main), a nastąpnie zakołczyć sią z kodem 1.

Dla każdej czytanej z pliku linii, która nie zawiera poprawnego identyfikatora
studenta, program powinien wypisać komunikat:

` Error in PLIK, line N: TEKST `

gdzie `PLIK` jest nazwą pliku, `N` jest numerem wiersza, a `TEKST` to oryginalna
postać wczytanej linii.

Dla każdej czytanej z pliku linii, która zawiera poprawny składniowo
identyfikator studenta, ale taki identyfikator już wcześniej wystąpił, program
powinien wypisać komunikat:

` Error in PLIK, line N: IDENTYFIKATOR `

gdzie `PLIK` jest nazwą pliku, `N` jest numerem wiersza, a `IDENTYFIKATOR` to
powtórzony identyfikator studenta.

Program wypisuje komunikaty o błądnych liniach w pliku w kolejnołci numerów
linii.

Dla każdej czytanej ze standardowego wejłcia linii, która nie zawiera poprawnego
opisu zespołu, program powinien wypisaą komunikat:

` Error in cin, line N: TEKST `

gdzie N jest numerem wiersza, a TEKST to oryginalna postać wczytanej linii.

Jeśli opis zespołu jest poprawny, to mogą wystąpią dwa powody zakwestionowania
w nim identyfikatora studenta: 

* nie pojawił sią w pliku, którego nazwą podano jako argument programu,  

* wystąpuje jego powtórzenie w tym samym zespole. 

W przypadku zakwestionowania identyfikatora studenta program powinien wypisać
komunikat:

` Error in cin, line 4: IDENTYFIKATOR `

gdzie `N` jest numerem wiersza, a `IDENTYFIKATOR` to zakwestionowany identyfikator
studenta.

Program wypisuje komunikaty o błędnych liniach ze standardowego wejścia
w kolejności numerów linii, a komunikaty o zakwestionowanych identyfikatorach
w kolejności ich występowania w opisie zespołu. Dla zakwestionowanych
identyfikatorów punkty nie są liczone.

Linie numeruje się od jedynki. Puste linie należy ignorować, ale uwzglądniać je
w numeracji. Wszelkie białe znaki w niepustych liniach należy traktować jako
błąd i uwzglądniać je w wypisywanych komunikatach.

### Przykład użycia

Lista identyfikatorów studentów w pliku _test_1.file:

```

ab111111
cd222222
ef333333
gh444444
ij555555
ab111111
ab01234
cab12345
zzm-1000

```

Lista opisów zespołów:

```

grupa1/zadanie1/ab111111+cd222222
grupa2/zadanie1/gh444444+ij555555
grupa1/zadanie2/ab111111+cd222222+ef333333
grupa2/zadanie2/gh444444 + ij555555
grupa1/zadanie3/ab111111+cd222222+pr999999
grupa1/zadanie4/cd222222+cd222222
grupa1/zadanie5/cd222222+cd222222+cd222222
grupa1/zadanie5/cd222222+cd222222+ab111111
grupa1/zadanie5/cd222222+cd222222+pr999999
grupa1/zadanie5/pr999999+pr999999+pr999999
grupa1/zadanie2/ab111111+ef333333

```

Program wypisuje na standardowe wyjście:

```

111111;7;
222222;6;
333333;1;

```

Program wypisuje na standardowe wyjście błędów:

```

Error in _test_1.file, line 6: ab111111
Error in _test_1.file, line 7: ab01234
Error in _test_1.file, line 8: cab12345
Error in cin, line 4: grupa2/zadanie2/gh444444 + ij555555
Error in cin, line 5: pr999999
Error in cin, line 6: cd222222
Error in cin, line 7: cd222222
Error in cin, line 7: cd222222
Error in cin, line 8: cd222222
Error in cin, line 9: cd222222
Error in cin, line 9: pr999999
Error in cin, line 10: pr999999
Error in cin, line 10: pr999999
Error in cin, line 10: pr999999

```

### Wymagania formalne

Program będzie kompilowany na maszynie students poleceniem

`g++ -Wall -Wextra -O2 -std=c++17 punkty.cc -o punkty`

Oczekiwane rozwiązanie nie powinno zawierać definicji własnych struktur i klas.
Zamiast tego należy intensywnie korzystać z kontenerów i algorytmów
dostarczanych przez standardową bibliotekę jązyka C++. Obsługę wejścia i wyjścia
oraz pliku należy zrealizować za pomocą strumieni.

Rozwiązanie należy umieścić w pliku punkty.cc, który należy umieścić
w repozytorium SVN w katalogu

`grupaN/zadanie1/ab123456+cd123456`

lub

`grupaN/zadanie1/ab123456+cd123456+ef123456`

gdzie `N` jest numerem grupy, a `ab123456, cd123456, ef123456` są identyfikatorami
członków zespołu umieszczającego to rozwiązanie. Katalog z rozwiązaniem nie
powinien zawierać innych plików, ale może zawierać podkatalog `"private"`, gdzie
można umieszczaą różne pliki, np. swoje testy. Pliki umieszczone w tym
podkatalogu nie bądą oceniane. Nie wolno umieszczać w repozytorium plików
dużych, binarnych, tymczasowych ani innych zbędnych.

# jnp-zad-1

Contributors: 

* @styczynski
* @joald

## Building

Please run `make` to build everything.
Run `make rebuild` to force rebuild.
Run `make clean` to clean compilation files.

## Task Description

### Task Points

This year, we introduced negative points for multiple reasons
cooperation with the same person. To better understand the principle of subtraction of these points
and help us calculate them, please write the appropriate program.

### functional requirements

The program is called with one argument, which is the file name
It contains student IDs participating in the assignments. Each
The identifier is in a separate line. The correct student ID consists of
with two lower case letters of the English alphabet and six digits or two small letters
English alphabet letters m, hyphen and four digits.

When you load a list of student IDs from the file, the program reads it
standard input descriptions of teams that solved individual tasks.
Each description is in a separate line. A proper description of the team consists of
word group, group number, number from 1 to 8, semicolon, word task,
task number, number from 1 to 6, semicolon, student identifiers
separated by a plus sign.

After processing all the descriptions of the assemblies the program prints to the standard
Exit the list of students to score points and then roll over
with code 0. Each line written is composed of student index number (hex
the last character of its identifier), the center, the number of points to take off
and the middle. The data is sorted by index numbers.

### support for error

The program must be resistant to incompatible input data with the specification.
The error messages described below should be written to the standard
get rid of the mistakes.

If a program has been called with a bad number of parameters, it should quit
statement

Sử dụng: PROGRAM tập tin

where PROGRAM is the program name given in the command line (zero argument
passed to the main function, and will end up with code 1.

If a program can not open a file named as an argument or
Any other error handling the file, should output a message

Error: problem with file FILE

where FILE is the name of the file (the first argument passed to main)
and they will end up with code 1.

For each read from a line file that does not contain a valid identifier
student, the program should issue a message

Error in FILE, line N: TEXT

where FILE is the file name, N is the line number, and TEXT is the original
they will load the loaded line.

For each read from a line file that contains the correct syntax
Student ID, but such ID has already occurred, program
should give a message

Error in FILE, line N: IDENTIFICATION

where FILE is the file name, N is the line number, and the ID is
duplicate student ID.

The program prints erroneous lines in the file in sequence of numbers
line.

For each read from the standard line input, which does not contain the correct one
team description, the program should issue a message

Error in cin, line N: TEXT

where N is the line number and TEXT is the original form of the loaded line.

If the team description is correct, there may be two reasons for questioning
in the student ID:
- did not appear in the file named as program argument,
- repeats in the same unit.
In case of questioning the student ID, the program should be discharged
statement

Error in cin, line 4: IDENTIFICATION

where N is the line number and ID is the contested identifier
student.

The program outputs erroneous lines from the standard input
in line numbers, and messages about questioned identifiers
in the order they appear in the team's description. For the challenged
Pointers are not counted.

Lines are numbered from 1. Empty lines should be ignored, but they will take care of them
in numbering. Any white characters in non-empty lines should be treated as
error and take note of them in the written messages.

### usage example

List of student IDs in _test_1.file:

ab111111
cd222222
ef333333
gh444444
ij555555
ab111111
ab01234
cab12345
ZZM-1000

List of team descriptions:

group1 / Job1 / ab111111 + cd222222
group2 / Job1 / gh444444 + ij555555
group1 / Job2 / ab111111 + + cd222222 ef333333
group2 / task2 / gh444444 + ij555555
group1 / Job3 / ab111111 cd222222 + + pr999999
group1 / Job4 / cd222222 + cd222222
group1 / zadanie5 / cd222222 + + cd222222 cd222222
group1 / zadanie5 / cd222222 + + cd222222 ab111111
group1 / zadanie5 / cd222222 cd222222 + + pr999999
group1 / zadanie5 / pr999999 pr999999 + + pr999999
group1 / Job2 / ab111111 + ef333333

The program outputs to the standard output:

111111; 7;
222222; 6;
333333; 1;

The program writes to the standard error output:

Error in _test_1.file, line 6: ab111111
Error in _test_1.file, line 7: ab01234
Error in _test_1.file, line 8: cab12345
Error in cin, line 4: group2 / task2 / gh444444 + ij555555
Error in cin, line 5: pr999999
Error in cin, line 6: cd222222
Error in cin, line 7: cd222222
Error in cin, line 8: cd222222
Error in cin, line 9: cd222222
Error in cin, line 9: pr999999
Error in cin, line 10: pr999999
Error in cin, line 10: pr999999
Error in cin, line 10: pr999999

### formal requirements

The program will be compiled on the student machine with a command

g ++ -Wall -Wextra -O2 -std = c ++ 17 points.cc -o points

Expected solution should not contain definitions of own structures and classes.
Instead, you should use containers and algorithms extensively
provided by the standard C ++ language library. Support for input and output
and the file should be streamed.

The solution should be placed in the file points.cc, which should be placed
in the SVN repository in the directory

grupaN / Job1 / AB123456 + cd123456

or

grupaN / Job1 / AB123456 cd123456 + + ef123456

where N is the group number, and ab123456, cd123456, ef123456 are identifiers
The members of the team placing this solution. Catalog with no solution
should contain other files, but may contain a subdirectory where private
You can place different files, such as your tests. Files placed in this
subdirectories are not evaluated. Do not place files in the repository
large, binary, temporary or otherwise unnecessary.

## Opis zadania

### Zadanie punkty

W tym roku wprowadziliłmy na tym przedmiocie punkty ujemne za wielokrotną
współpracę z tą samą osobą. Aby lepiej zrozumieć zasady odejmowania tych punktów
i pomóc nam je policzyć, prosimy o napisanie stosownego programu.

### Wymagania funkcjonalne

Program wywoływany jest z jednym argumentem, który jest nazwą pliku
zawierającego identyfikatory studentów uczestniczących w zająciach. Każdy
identyfikator jest w osobnej linii. Poprawny identyfikator studenta składa sią
z dwóch małych liter alfabetu angielskiego i szełciu cyfr albo z dwóch małych
liter alfabetu angielskiego litery m, łącznika i czterech cyfr.

Po wczytaniu z pliku listy identyfikatorów studentów program czyta za
standardowego wejłcia opisy zespołów, które rozwiązywały poszczególne zadania.
Każdy opis znajduje sią w osobnej linii. Poprawny opis zespołu składa sią ze
słowa grupa, numeru grupy, bądącego liczbą od 1 do 8, ukołnika, słowa zadanie,
numeru zadania, bądącego liczbą od 1 do 6, ukołnika, identyfikatorów studentów
oddzielonych znakiem plus.

Po przetworzeniu wszystkich opisów zespołów program wypisuje na standardowe
wyjłcie listą studentów, którym należy odjąą punkty, a nastąpnie kołczy sią
z kodem 0. Każda wypisywana linia składa sią z numeru indeksu studenta (szełą
ostatnich znaków jego identyfikatora), łrednika, liczby punktów do odjącia
i łrednika. Wypisywane dane są posortowane według numerów indeksów.

### Obsługa błądów

Program musi byą odporny na niezgodnołci danych wejłciowych ze specyfikacją.
Opisane poniżej komunikaty o błądach powinny byą wypisywane na standardowe
wyjłcie błądów.

Jełli program został wywołany ze złą liczbą parametrów, powinien wypisaą
komunikat

Usage: PROGRAM file

gdzie PROGRAM jest nazwą programu, jaką podano w linii poleceł (zerowy argument
przekazany do funkcji main), a nastąpnie zakołczyą sią z kodem 1.

Jełli program nie może otworzyą pliku o nazwie podanej jako argument lub
wystąpił jakił inny błąd związany z obsługą pliku, powinien wypisaą komunikat

Error: problem with file PLIK

gdzie PLIK jest nazwą pliku (pierwszy argument przekazany do funkcji main),
a nastąpnie zakołczyą sią z kodem 1.

Dla każdej czytanej z pliku linii, która nie zawiera poprawnego identyfikatora
studenta, program powinien wypisaą komunikat

Error in PLIK, line N: TEKST

gdzie PLIK jest nazwą pliku, N jest numerem wiersza, a TEKST to oryginalna
postaą wczytanej linii.

Dla każdej czytanej z pliku linii, która zawiera poprawny składniowo
identyfikator studenta, ale taki identyfikator już wczełniej wystąpił, program
powinien wypisaą komunikat

Error in PLIK, line N: IDENTYFIKATOR

gdzie PLIK jest nazwą pliku, N jest numerem wiersza, a IDENTYFIKATOR to
powtórzony identyfikator studenta.

Program wypisuje komunikaty o błądnych liniach w pliku w kolejnołci numerów
linii.

Dla każdej czytanej ze standardowego wejłcia linii, która nie zawiera poprawnego
opisu zespołu, program powinien wypisaą komunikat

Error in cin, line N: TEKST

gdzie N jest numerem wiersza, a TEKST to oryginalna postaą wczytanej linii.

Jełli opis zespołu jest poprawny, to mogą wystąpią dwa powody zakwestionowania
w nim identyfikatora studenta:
- nie pojawił sią w pliku, którego nazwą podano jako argument programu,
- wystąpuje jego powtórzenie w tym samym zespole.
W przypadku zakwestionowania identyfikatora studenta program powinien wypisaą
komunikat

Error in cin, line 4: IDENTYFIKATOR

gdzie N jest numerem wiersza, a IDENTYFIKATOR to zakwestionowany identyfikator
studenta.

Program wypisuje komunikaty o błądnych liniach ze standardowego wejłcia
w kolejnołci numerów linii, a komunikaty o zakwestionowanych identyfikatorach
w kolejnołci ich wystąpowania w opisie zespołu. Dla zakwestionowanych
identyfikatorów punkty nie są liczone.

Linie numeruje sią od jedynki. Puste linie należy ignorowaą, ale uwzglądniaą je
w numeracji. Wszelkie białe znaki w niepustych liniach należy traktowaą jako
błąd i uwzglądniaą je w wypisywanych komunikatach.

### Przykład użycia

Lista identyfikatorów studentów w pliku _test_1.file:

ab111111
cd222222
ef333333
gh444444
ij555555
ab111111
ab01234
cab12345
zzm-1000

Lista opisów zespołów:

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

Program wypisuje na standardowe wyjłcie:

111111;7;
222222;6;
333333;1;

Program wypisuje na standardowe wyjłcie błądów:

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

### Wymagania formalne

Program bądzie kompilowany na maszynie students poleceniem

g++ -Wall -Wextra -O2 -std=c++17 punkty.cc -o punkty

Oczekiwane rozwiązanie nie powinno zawieraą definicji własnych struktur i klas.
Zamiast tego należy intensywnie korzystaą z kontenerów i algorytmów
dostarczanych przez standardową biblioteką jązyka C++. Obsługą wejłcia i wyjłcia
oraz pliku należy zrealizowaą za pomocą strumieni.

Rozwiązanie należy umieścić w pliku punkty.cc, który należy umieścić
w repozytorium SVN w katalogu

grupaN/zadanie1/ab123456+cd123456

lub

grupaN/zadanie1/ab123456+cd123456+ef123456

gdzie N jest numerem grupy, a ab123456, cd123456, ef123456 są identyfikatorami
członków zespołu umieszczającego to rozwiązanie. Katalog z rozwiązaniem nie
powinien zawieraą innych plików, ale może zawieraą podkatalog private, gdzie
można umieszczaą różne pliki, np. swoje testy. Pliki umieszczone w tym
podkatalogu nie bądą oceniane. Nie wolno umieszczać w repozytorium plików
dużych, binarnych, tymczasowych ani innych zbędnych.
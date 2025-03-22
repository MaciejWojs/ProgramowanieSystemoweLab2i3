# Laboratorium 2 i 3 - Optymalizacja Kodu

## Opis projektu
Repozytorium zawiera rozwiązania zadań z laboratorium 2 i 3 z Programowania Systemowego, których głównym celem była nauka operacji na plikach w jezyku C.

## Dostęp do zadań

### Zakładka Releases
W sekcji "Releases" tego repozytorium znajdują się skompilowane wersje programów dla wszystkich poziomów optymalizacji (`O0`, `O1`, `O2`, `O3`). 

### Lista zadań do wykonania

1. **Testowanie praw dostępu do pliku**  
   - Przetestuj program drugi.c dla pliku z prawami: `000`, `777`, `444`.

2. **Program `t_chmod`**  
   - Tworzy pusty plik o nazwie podanej jako pierwszy argument wywołania z określonymi prawami dostępu, np.:
     ```sh
     t_chmod plik 0641
     ```

3. **Program `f_add`**  
   - Dopisuje na końcu podanego pliku (podanego jako argument wywołania) określony ciąg znaków.

4. **Program `f_read`**  
   - Odczytuje z podanego pliku (argument wywołania) określoną liczbę pierwszych znaków.

5. **Program `f_find`**  
   - Sprawdza, czy w podanym pliku (argument wywołania) znajduje się podany jako kolejny argument wzorzec.

6. **Program `f_count_r`**  
   - Zlicza liczbę wierszy w pliku tekstowym.

7. **Program `f_count_w`**  
   - Zlicza liczbę słów w pliku tekstowym.

8. **Program `f_cp`**  
   - Kopiuje podany plik źródłowy (tekstowy) do nowego pliku o nazwie `kopia.txt`.

9. **Program `f_dir`**  
   - Tworzy katalog o nazwie podanej jako argument wywołania z prawami dostępu `0755`.

---

📌 **Instrukcja kompilacji i uruchomienia:**  
Każdy program można skompilować za pomocą kompilatora `gcc` lub `g++`, np.:
```sh
gcc program.c -o program
./program
```
Dodatkowo można skorzystać z opcji optymalizacji:
```sh
gcc -O2 program.c -o program
```
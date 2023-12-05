## О проекте

Проект представляет собой библиотеку на C++ для работы с трехмерным массивом 17-битных беззнаковых целых чисел.

Основная идея реализации:

- [`UInt17View`](src/uint17/uint17_view.h) интерпретирует участок памяти как одно 17-битное число и позволяет читать и изменять его значение.
- [`Array`](src/uint17/array.h) хранит последовательность 17-битных чисел в компактном виде.
- [`ArrayView`](src/uint17/array_view.h) предоставляет представление контейнера как N-мерного массива и позволяет обращаться к элементам через цепочку индексов.
- [`ArrayWithVectorsView`](src/uint17/array_with_vectors_view.h) расширяет представление массива и реализует арифметические операции, а также ввод и вывод.

Поддерживаются:

- доступ к элементам по индексам в стиле `view[x][y][z]`;
- создание нового массива через статический метод `MakeArray`;
- операции сложения, вычитания и умножения с созданием нового массива;
- потоковый ввод и вывод содержимого массива;
- тесты на базе GoogleTest.

## Как запустить

### Сборка

Из корня репозитория выполните:

```bash
cmake -S src -B build
cmake --build build
```

Файл [`src/CMakeLists.txt`](src/CMakeLists.txt) описывает основную сборку проекта, а [`src/tests/CMakeLists.txt`](src/tests/CMakeLists.txt) подключает GoogleTest и собирает тестовый исполняемый файл.

### Запуск тестов

После сборки выполните:

```bash
ctest --test-dir build --output-on-failure
```

Это запустит тесты из файла [`src/tests/array3d_test.cpp`](src/tests/array3d_test.cpp).

## Как пользоваться

### Создание массива

Трехмерный массив можно создать через статический метод `MakeArray`:

```cpp
auto [view, array] = ArrayView<3>::MakeArray(2u, 2u, 2u);
```

После этого можно обращаться к элементам по индексам:

```cpp
view[0][0][0] = 1u;
view[0][0][1] = 2u;
view[1][1][1] = 8u;
```


### Чтение и изменение элементов

Массив поддерживает доступ в стиле многомерного контейнера:

```cpp
Array array = {1, 2, 3, 4, 5, 6, 7, 8};
ArrayView<3> view(array, 0, 2u, 2u, 2u);

view[0][1][1] = 20u;
```

Пример такого обращения есть в тесте [`view[0][1][1] = 20u`](src/tests/array3d_test.cpp:565).

### Ввод и вывод

Для представления [`ArrayWithVectorsView<3>`](src/uint17/array_with_vectors_view.h) реализованы потоковые операторы.

Ввод:

```cpp
std::string input = "1 2 3 4 5 6 7 8";
std::stringstream input_stream(input);
auto [view, array] = ArrayWithVectorsView<3>::MakeArray(2u, 2u, 2u);
input_stream >> view;
```

Вывод:

```cpp
std::stringstream output_stream;
Array array = {1, 2, 3, 4, 5, 6, 7, 8};
ArrayWithVectorsView<3> view(array, 0, 2u, 2u, 2u);
output_stream << view;
```

Примеры находятся в тестах [`operator>>()`](src/tests/array3d_test.cpp:697) и [`operator<<()`](src/tests/array3d_test.cpp:713).

### Арифметические операции

Для массивов поддерживаются операции над элементами с созданием нового результата:

- сложение двух массивов;
- вычитание двух массивов;
- умножение массива на число.

Примеры в тестах [`src/tests/array3d_test.cpp`](src/tests/array3d_test.cpp).

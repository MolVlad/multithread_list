# Multithreaded list

## Problem statement

1. Сформировать в памяти двусвязный список определенного размера,
содержащий случайные значения, которые следует получить из генератора
случайных чисел, встроенного в ядро Linux.

2. Запустить два потока (threads).

    1. Потоку №1: начиная с головы списка подсчитывать количество
нулевых битов в значениях элементов и количество пройденных
элементов, освобождать учтённый элемент сразу после учёта.

    2. Потоку №2: начиная с хвоста списка подсчитывать количество
единичных битов в значениях элементов и количество пройденных
элементов, освобождать учтённый элемент сразу после учёта.

3. По окончании элементов списка вывести результаты подсчёта.

4. Обеспечить однократную обработку каждого элемента списка (каждый
должен быть учтён, но только один раз, одним из потоков).

5. Желательно, чтобы в потоках работали не две разные функции, а
одна, принимающая особенности работы через аргументы.

## Launch instructions

`make` - compile and run execution

![image](https://user-images.githubusercontent.com/36729129/219877052-cf0087bf-3f55-4a5d-a9a4-658b9b0382e6.png)

`make print` - compile and run execution with printing list

![image](https://user-images.githubusercontent.com/36729129/219877105-d4e136d6-d3c8-45f4-b4c5-cda1d781b9ff.png)

`make memory` - compile and run execution with memory check by valgrind

![image](https://user-images.githubusercontent.com/36729129/219877128-351dc389-925b-4799-91f6-affc83fc1382.png)

`make real_random` - compile and run execution with usage `/dev/random` which is "more random"

`make debug` - compile and run execution with detailed logging




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

`make debug` - compile and run execution with detailed logging

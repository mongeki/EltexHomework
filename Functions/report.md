- Создаем файл input.txt из которого будем перенаправлять ввод в программу
- Записываем в него символов больше чем размер массива char, чтобы программа завершилась с ошибкой сегментации
- Запускаем программу с отладчиком и узнаем адрес, куда нужно возвратиться после функции IsPassOk

![](attachments/Pasted%20image%2020240710183629.png)

- В моем случае смотрим на строку 
```
0x00000000004011d8 <+66>:    lea    0xe43(%rip),%rax        # 0x402022
```
- Записываем этот адрес в конец нашего файла в little-endian : d8 11 40 00
- Подбираем оффсет добавляя или удаляя символы
- Запускаем
![](attachments/Pasted%20image%2020240710184140.png)
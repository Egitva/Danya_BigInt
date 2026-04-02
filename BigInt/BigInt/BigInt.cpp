// BigInt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class BigInt {
    //строка в которой хранятся циферки
    string digits;
public:

    //конструкторы с их перегрузками:
    BigInt(unsigned long long n = 0);
    BigInt(string&);
    BigInt(const char*);
    BigInt(BigInt&);

    //функции помошники:
    friend void divide_by_2(BigInt& a);
    friend bool Null(const BigInt&);
    friend int Length(const BigInt&);
    int operator[](const int)const;

    /* * * * Перегрузки операторов класса * * * */

    //Присвоение
    BigInt& operator=(const BigInt&);

    //Пре/пост инкримент
    BigInt& operator++();
    BigInt operator++(int temp);
    BigInt& operator--();
    BigInt operator--(int temp);

    //Сложение и вычитание с присвоением
    friend BigInt& operator+=(BigInt&, const BigInt&);
    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt& operator-=(BigInt&, const BigInt&);

    //Сравнение
    friend bool operator==(const BigInt&, const BigInt&);
    friend bool operator!=(const BigInt&, const BigInt&);

    friend bool operator>(const BigInt&, const BigInt&);
    friend bool operator>=(const BigInt&, const BigInt&);
    friend bool operator<(const BigInt&, const BigInt&);
    friend bool operator<=(const BigInt&, const BigInt&);

    //Умножение и деление
    friend BigInt& operator*=(BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt& operator/=(BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);

    //Модуль
    friend BigInt operator%(const BigInt&, const BigInt&);
    friend BigInt& operator%=(BigInt&, const BigInt&);

    //Возведение в степень
    friend BigInt& operator^=(BigInt&, const BigInt&);
    friend BigInt operator^(BigInt&, const BigInt&);

    //взятие корня
    friend BigInt sqrt(BigInt& a);

    //Ввод и вывод
    friend ostream& operator<<(ostream&, const BigInt&);
    friend istream& operator>>(istream&, BigInt&);

    //Другие
    friend BigInt NthCatalan(int n);
    friend BigInt NthFibonacci(int n);
    friend BigInt Factorial(int n);

    //преобразование к типу стринг
    operator string() const { return digits; }
    //преобразование к типу инт
    operator int() const {
        try {
            return *this <= (BigInt)2147483647 ? stoi(digits) : (int)2147483647;
        }
        catch (std::invalid_argument&) {
            throw("ERORR invalid argument");
            // Handle error here
            // You might want to throw your own exception or return a default value
        }
    }
};
//конструктор для инициализации с помощью строки string
BigInt::BigInt(string& s) {
    //инициализируем строку digits пустой строкой
    digits = "";
    //объявляем и инициализируем переменную n длинной полученной строки
    int n = s.size();
    //обратный цикл (идём от конца строки до её начала)
    for (int i = n - 1; i >= 0; i--) {
        //если символ не является цифрой выводим ошибку с текстом ERROR
        if (!isdigit(s[i]))
            throw("ERROR");
        //добавляем в конец строки digits текущий символ переводя его в тип int
        digits.push_back(s[i] - '0');
    }
}
//конструктор для инициализации с помощью неотрицательного long long числа
BigInt::BigInt(unsigned long long nr) {
    //пока число есть и больше 0
    do {
        //добавляем в конец строки digits последний разряд(правый) переданного числа
        digits.push_back(nr % 10);
        //делим переданное число на 10, чтобы избавиться от последнего(правого) разряда
        nr /= 10;
    } while (nr);
}
//конструктор для инициализации с помощью строки в виде массива char'ов
BigInt::BigInt(const char* s) {
    //инициализируем строку digits пустой строкой
    digits = "";
    //обратный цикл (идём от конца строки до её начала)
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        //если символ не является цифрой выводим ошибку с текстом ERROR
        if (!isdigit(s[i]))
            throw("ERROR");
        //добавляем в конец строки digits текущий символ переводя его в тип int
        digits.push_back(s[i] - '0');
    }
}
//конструктор для инициализации с помощью другого класса BigInt
BigInt::BigInt(BigInt& a) {
    //присваиваем текущему классу в поле digits данные из поля digits переданного класса
    digits = a.digits;
}
//метод для проверки является ли данное число в виде класса BigInt нулевым
bool Null(const BigInt& a) {
    //если длина поля digits переданного класса равно 1 и первый символ равен нулю
    if (a.digits.size() == 1 && a.digits[0] == 0)
        //возвращаем истину
        return true;
    //иначе возвращаем не истину :)
    return false;
}
//метод для получения длины числа в виде класса BigInt
int Length(const BigInt& a) {
    //возвращаем длинну поля digits
    return a.digits.size();
}
//оператор для получения значения числа в виде клсса BigNum на переданной позиции
int BigInt::operator[](const int index)const {
    //если длина поля digits меньше или равна переданой позиции или переданная позиция меньше нуля
    if (digits.size() <= index || index < 0)
        //выводим ошибку
        throw("ERROR");
    //иначе выводим значение элемента index из поля digits
    return digits[index];
}
//оператор сравнивания равно
bool operator==(const BigInt& a, const BigInt& b) {
    //возращаем булевый результат сравнения полей digits друх переданных классов BigNum
    return a.digits == b.digits;
}
//оператор сравнивания не равно
bool operator!=(const BigInt& a, const BigInt& b) {
    //возвращаем булевый результат отрицания от операции сравнивания равно
    return !(a == b);
}
//оператор сравнения меньше
bool operator<(const BigInt& a, const BigInt& b) {
    //присваиваем переменным n и m длины переданных классов BigInt соответственно
    int n = Length(a), m = Length(b);
    //если длина n не равна дине m
    if (n != m)
        //возвращаем булевый результат оператора сравнения меньше между n и m
        return n < m;
    //пока длинна левого числа n не меньше или равна 0
    while (n--)
        //проверяем с конца если элементы в классах BigNum отличаются то
        if (a.digits[n] != b.digits[n])
            //выводим булевый результат сравнения оператором меньше этих элементов
            return a.digits[n] < b.digits[n];
    //иначе возвращаем не истину ;)
    return false;
}
//оператор сравнения больше
bool operator>(const BigInt& a, const BigInt& b) {
    //возвращаем булевый результат сравнения оператором меньше перевёрнутых входных классов BigNum
    return b < a;
}
//оператор сравнения больше или равно
bool operator>=(const BigInt& a, const BigInt& b) {
    //возвращаем булевый результат отрицания от вызова оператора сравнения меньше для входных классов BigNum a и b соответственно
    //return !(a < b);
    return a < b || a == b;
}
//оператор сравнения меньше или равно
bool operator<=(const BigInt& a, const BigInt& b) {
    //возвращаем булевый результат отрицания от вызова оператора сравнения больше для входных классов BigNum a и b соответственно
    //return !(a > b);
    return a < b || a == b;
}
//оператор присваивания
BigInt& BigInt::operator=(const BigInt& a) {
    //присваиваем полю digits данного класса значение поля digits передаваемого класса BigNum
    digits = a.digits;
    //возвращаем ссылку на данный класс
    return *this;
}
//оператор преинкремента
BigInt& BigInt::operator++() {
    //объявляем переменную i и переменную n в которую записываем длину поля digits данного класса
    int i, n = digits.size();
    //цикл от нуля пока i меньше длинны n и значение ячейки под ключом i равно 9 
    for (i = 0; i < n && digits[i] == 9; i++)
        //присваиваем значение 0 в поле digits под ключом i данного класса 
        digits[i] = 0;
    //если ключ i равен длине n 
    if (i == n)
        //записываем в конец поля digits единичку
        digits.push_back(1);
    //иначе
    else
        //прибавляем единичку к полю digits под ключом i 
        digits[i]++;
    //возвращаем ссылку на данный класс
    return *this;
}
//оператор постинкремента
BigInt BigInt::operator++(int temp) {
    //объявляем экземпляр класса BigInt под именем aux
    BigInt aux;
    //инициализируем переменную aux копией данного класса
    aux = *this;
    //используем операцию преинкремента к ссылке на данный класс
    ++(*this);
    //возвращаем экземпляр класса aux 
    return aux;
}
//операция предикримента
BigInt& BigInt::operator--() {
    //проверяем ессли первый элемент в поле digits данного класса равен 0 и длинна поля digits данного класса равна 1
    if (digits[0] == 0 && digits.size() == 1)
        //выводим ошибку
        throw("UNDERFLOW");
    //объявляем переменную i и n инициализируем переменную n длинной поля digits данного класса
    int i, n = digits.size();
    //цикл от нуля пока значение эчейки поля digits под ключом i равно 0 и i меньше длинны поля digits
    for (i = 0; digits[i] == 0 && i < n; i++)
        //присваиваем 9 в ячейку поля digits под ключом i
        digits[i] = 9;
    //вычитаем единицу из ячейки поля digits под ключом i 
    digits[i]--;
    //проверяем если длинна больше 1 и левое значение от данноой ячейки равно 0
    if (n > 1 && digits[n - 1] == 0)
        //удаляем последний(правый) элемент поля digits данного класса
        digits.pop_back();
    //возвращаем ссылку на данный класс
    return *this;
}
//оператор постдекремента
BigInt BigInt::operator--(int temp) {
    //объявляем экземпляр класса BigInt под именем aux
    BigInt aux;
    //инициализируем переменную aux копией данного класса
    aux = *this;
    //используем операцию предекремента к ссылке на данный класс
    --(*this);
    //возвращаем экземпляр класса aux 
    return aux;
}
//оператор сложения с присвоением 
BigInt& operator+=(BigInt& a, const BigInt& b) {
    //объявляем переменную t и инициализируем её нулём, а так же объявляем переменные s и i
    int t = 0, s, i;
    //объявляем переменные n и m и инициализируем их длинной полей digits переданных классов BigNum a и b соответственно
    int n = Length(a), m = Length(b);
    //если длинна m больше длинны n
    if (m > n)
        //добавляем классу a в поле digits на позицию m - n значение равное 0
        a.digits.append(m - n, 0);
    //присваиваем к n длинну переданного класса a 
    n = Length(a);
    //цикд от нуля пока i меньше длинны n
    for (i = 0; i < n; i++) {
        //проверяем если счётчик i меньше длинны m
        if (i < m)
            //записываем в переменную s результат сложения полей digits под ключом i классов a и b соответственно вместе с долгом от прдыдущей операции сложения
            s = (a.digits[i] + b.digits[i]) + t;
        //иначе
        else
            //записываем в переменную s результат сложения поля digits под ключом i класса a вместе с долгом от прдыдущей операции сложения
            s = a.digits[i] + t;
        //записываем в переменную долга значение переменной s без последнего(правого) разряда
        t = s / 10;
        //присваиваем полю digits класса a остаток от деления на 10 переменной s
        a.digits[i] = (s % 10);
    }
    //если долг существует
    if (t)
        //записываем в конец поля digits класса а этот долг
        a.digits.push_back(t);
    //возвращаем класс a
    return a;
}
//оператор прибавления 
BigInt operator+(const BigInt& a, const BigInt& b) {
    //создаём экземпляр класса BigInt c именем temp
    BigInt temp;
    //присваиваем к переменной temp переданный класс a 
    temp = a;
    //прибавляем с присвоением переданный класс b к переменной temp
    temp += b;
    //возвращаем экземпляр класса temp
    return temp;
}
//оператор вычитания с присвоением
BigInt& operator-=(BigInt& a, const BigInt& b) {
    //проверяем если переданный класс a меньше переданного класса b
    if (a < b)
        //выводим ошибку
        throw("UNDERFLOW");
    //объявляем переменные n и m и инициализируем их длинной полей digits переданных классов BigNum a и b соответственно
    int n = Length(a), m = Length(b);
    //объявляем переменную t и инициализируем её нулём, а так же объявляем переменные s и i
    int i, t = 0, s;
    //цикл от нуля пока i меньше длинны n
    for (i = 0; i < n; i++) {
        //проверяем если i меньше длинны m
        if (i < m)
            //присваиваем в переменную s результат вычитания между полями digits классов а и b соответственно совместно с суммированием долг предидущей операции вычитания
            s = a.digits[i] - b.digits[i] + t;
        //иначе
        else
            //записываем в переменную s результат сложения поля digits под ключом i класса a вместе с долгом от прдыдущей операции сложения
            s = a.digits[i] + t;
        //если переменная s меньше чем 0
        if (s < 0)
            //прибавляем к переменной s 10
            s += 10,
            //и присваиваемпеременной долга минус один
            t = -1;
        //иначе
        else
            //присваиваем переменной долга 0
            t = 0;
        //присваиваем полю digits класса a значение переменной s
        a.digits[i] = s;
    }
    //цикл пока длинна n больше 1 и поле digits слева от текущего равно 0 
    while (n > 1 && a.digits[n - 1] == 0)
        //удаляем последний(правый) элемент поля digits класса a
        a.digits.pop_back(),
        //вычитаем единичку из n
        n--;
    //позвращаем класс a
    return a;
}
//оператор минус
BigInt operator-(const BigInt& a, const BigInt& b) {
    //создаём экземпляр класса BigInt c именем temp
    BigInt temp;
    //присваиваем к переменной temp переданный класс a 
    temp = a;
    //вычитаем с присвоением переданный класс b к переменной temp
    temp -= b;
    //возвращаем экземпляр класса temp
    return temp;
}
//оператор умножения с присвоением
BigInt& operator*=(BigInt& a, const BigInt& b)
{
    //проверяем если переданные классы а или b нулевые 
    if (Null(a) || Null(b)) {
        //присваиваем классу a нулевой класс BigInt
        a = BigInt();
        //возвращаем класс а
        return a;
    }
    //объявляем переменные n и m и инициализируем их длинами полей digits передаваемых классов соответственно
    int n = a.digits.size(), m = b.digits.size();
    //создаём векторный массив с типом int размером в сумму длин передаваемых классов и заполняем его нулями
    vector<int> v(n + m, 0);
    //цикл от нуля пока i меньше n
    for (int i = 0; i < n; i++)
        //цикл от нуля у цикле от нуля (тут типа смешно) пока j меньше m
        for (int j = 0; j < m; j++) {
            //суммируем с присвоением в ячейку под ключом равным сумме i и j результат умножения полей digits классов а и b с ключами i и j соответственно
            v[i + j] += (a.digits[i]) * (b.digits[j]);
        }
    //прибавляем с присвоением m к n
    n += m;
    //изменяем размер поля digits класса а соответственно размеру массива v
    a.digits.resize(v.size());
    //цикл с ключами s, i=0, t=0 пока i меньше n 
    for (int s, i = 0, t = 0; i < n; i++)
    {
        //присваиваем в переменную s результат сложения t и значения ячейки v под ключом i 
        s = t + v[i];
        //в значение ячейки v под ключом i присаиваем остаток от деления на 10 переменной s
        v[i] = s % 10;
        //в переменною t присваиваем перменную s без последнего(правого) разряда
        t = s / 10;
        //присваиваем к полю digits класса а под ключом i значение ячейки v под ключом i
        a.digits[i] = v[i];
    }
    //обратный цикл от длины n пока i больше или равно 1 и отрицание v под ключом i
    for (int i = n - 1; i >= 1 && !v[i]; i--)
        //удаляем последний(правый) элемент поля digits класса а
        a.digits.pop_back();
    //возвращаем класс а
    return a;
}
//оператор умножения
BigInt operator*(const BigInt& a, const BigInt& b) {
    //создаём экземпляр класса BigInt c именем temp
    BigInt temp;
    //присваиваем к переменной temp переданный класс a 
    temp = a;
    //умножеем с присвоением переданный класс b к переменной temp
    temp *= b;
    //возвращаем экземпляр класса temp
    return temp;
}
//оператор деление с присвоением
BigInt& operator/=(BigInt& a, const BigInt& b) {
    //если б это ноль 
    if (Null(b))
        //на ноль делить нельзя
        throw("Arithmetic Error: Division By 0");
    //проверяем если а меньше б 
    if (a < b) {
        a = BigInt();
        //возвращаем занулённое а
        return a;
    }
    //если а равно б
    if (a == b) {
        a = BigInt(1);
        //возвращаем один
        return a;
    }
    int i, lgcat = 0, cc;
    //присваиваем длины переменным м и н 
    int n = Length(a), m = Length(b);
    //делаем вектор интовский длинны н заполненный нулями
    vector<int> cat(n, 0);
    //делаем экземпляр класса под именем т
    BigInt t;
    //цикл от конца пока т * 10 + значение элемента digits под ключом i меньше б
    for (i = n - 1; t * (BigInt)10 + (BigInt)a.digits[i] < b; i--) {
        //умножаем т на 10
        t *= 10;
        //прибавляем с присвоением к т значение элемента digits под ключом i
        t += a.digits[i];
    }
    //цикл вниз пока i больше или равно 0
    for (; i >= 0; i--) {
        //присваиваем к т т * 10 + значение элемента digits под ключом i 
        t = t * (BigInt)10 + (BigInt)a.digits[i];
        //пробегаем фрорм вниз от 9 пока сс * б больше т 
        for (cc = 9; (BigInt)cc * b > t; cc--);
        //вычитаем из т сс * б
        t -= (BigInt)cc * b;
        //к ячейке кат под ключом lgcat++ прибавляем сс
        cat[lgcat++] = cc;
    }
    //расширяем поле digits соотвественно с кат 
    a.digits.resize(cat.size());
    //цикл пока i меньше lgcat
    for (i = 0; i < lgcat; i++)
        //присваиваем значения из кат в digits
        a.digits[i] = cat[lgcat - i - 1];
    //расширяем digits под lgcat
    a.digits.resize(lgcat);
    //возвращаем а
    return a;
}
//оператор деления
BigInt operator/(const BigInt& a, const BigInt& b) {
    //создаём экземпляр класса BigInt c именем temp
    BigInt temp;
    //присваиваем к переменной temp переданный класс a 
    temp = a;
    //делим с присвоением переданный класс b к переменной temp
    temp /= b;
    //возвращаем экземпляр класса temp
    return temp;
}
//оператор остатка от деления с присвоением
BigInt& operator%=(BigInt& a, const BigInt& b) {
    //если б это нуль
    if (Null(b))
        //отправляем ошибку
        throw("Arithmetic Error: Division By 0");
    //если а меньше б
    if (a < b) {
        //отправляем а
        return a;
    }
    //если а равно б
    if (a == b) {
        a = BigInt();
        //отправляем занулённое а
        return a;
    }
    int i, lgcat = 0, cc;
    //присваиваем длины переменным м и н 
    int n = Length(a), m = Length(b);
    //делаем вектор интовский длинны н заполненный нулями
    vector<int> cat(n, 0);
    //делаем экземпляр класса под именем т
    BigInt t;
    //цикл от конца пока т * 10 + значение элемента digits под ключом i меньше б
    for (i = n - 1; t * (BigInt)10 + (BigInt)a.digits[i] < b; i--) {
        //умножаем т на 10
        t *= 10;
        //прибавляем с присвоением к т значение элемента digits под ключом i
        t += a.digits[i];
    }
    //цикл вниз пока i больше или равно 0
    for (; i >= 0; i--) {
        //присваиваем к т т * 10 + значение элемента digits под ключом i 
        t = t * (BigInt)10 + (BigInt)a.digits[i];
        //пробегаем фрорм вниз от 9 пока сс * б больше т 
        for (cc = 9; (BigInt)cc * b > t; cc--);
        //вычитаем из т сс * б
        t -= (BigInt)cc * b;
        //к ячейке кат под ключом lgcat++ прибавляем сс
        cat[lgcat++] = cc;
    }
    //приравниваем а к т
    a = t;
    //возвращаем а
    return a;
}
//оператор остатка от деления
BigInt operator%(const BigInt& a, const BigInt& b) {
    //создаём экземпляр класса BigInt c именем temp
    BigInt temp;
    //присваиваем к переменной temp переданный класс a 
    temp = a;
    //вычисляем остаток от деления с присвоением переданный класс b к переменной temp
    temp %= b;
    //возвращаем экземпляр класса temp
    return temp;
}
//оператор возведения в степень с присвоением
BigInt& operator^=(BigInt& a, const BigInt& b) {
    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    while (!Null(Exponent)) {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    return a;
}
//оператор возведения в степень
BigInt operator^(BigInt& a, BigInt& b) {
    BigInt temp(a);
    temp ^= b;
    return temp;
}
//метод для проверки делится ли на 2
void divide_by_2(BigInt& a) {
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }
    while (a.digits.size() > 1 && !a.digits.back())
        a.digits.pop_back();
}
//метод взятия корня
BigInt sqrt(BigInt& a) {
    BigInt left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while (left <= right) {
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = (mid * mid);
        if (prod <= a) {
            v = mid;
            ++mid;
            left = mid;
        }
        else {
            --mid;
            right = mid;
        }
        mid = BigInt();
    }
    return v;
}
//метод опеределения катлан
BigInt NthCatalan(int n) {
    BigInt a(1), b;
    for (int i = 2; i <= n; i++)
        a *= i;
    b = a;
    for (int i = n + 1; i <= 2 * n; i++)
        b *= i;
    a *= a;
    a *= (n + 1);
    b /= a;
    return b;
}
//метод определения фибоначи
BigInt NthFibonacci(int n) {
    BigInt a(1), b(1), c;
    if (!n)
        return c;
    n--;
    while (n--) {
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}
//метод определения факториала
BigInt Factorial(int n) {
    BigInt f(1);
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}
//оператор ввода
istream& operator>>(istream& in, BigInt& a) {
    //строка буфер для входа
    string s;
    //получение данных из стрима
    in >> s;
    //присвение к н длинны строки
    int n = s.size();
    //пробегаемся по строке с кона
    for (int i = n - 1; i >= 0; i--) {
        //проверяем если это не цифра
        if (!isdigit(s[i]))
            //выдаём ошибку
            throw("INVALID NUMBER");
        //иначе записываем в поле digits символ из строки
        a.digits[n - i - 1] = s[i];
    }
    //возвращаем стрим
    return in;
}
//оператор вывода
ostream& operator<<(ostream& out, const BigInt& a) {
    //пробегаемся по digits от конца
    for (int i = a.digits.size() - 1; i >= 0; i--)
        //выводим на экран превратив в short
        cout << (short)a.digits[i];
    //возвращаем cout
    return cout;
}
//это чудо нужно для того чтобы присваивать BigNum к int в допустимых значениях
int kakoeEtoInt(BigInt x) {
    //провер.... эээ ты что подумал я это буду коментировать? хехехе, ну ты смешной... сам поймёшь
    if (x == (BigInt)"0") {
        return 0;
    }
    if (x == (BigInt)1) {
        return 1;
    }
    if (x == (BigInt)2) {
        return 2;
    }
    if (x == (BigInt)3) {
        return 3;
    }
    if (x == (BigInt)4) {
        return 4;
    }
    if (x == (BigInt)5) {
        return 5;
    }
    if (x == (BigInt)6) {
        return 6;
    }
    if (x == (BigInt)7) {
        return 7;
    }
    if (x == (BigInt)8) {
        return 8;
    }
    if (x == (BigInt)9) {
        return 9;
    }
    if (x == (BigInt)10) {
        return 10;
    }
    if (x == (BigInt)11) {
        return 11;
    }
    if (x == (BigInt)12) {
        return 12;
    }
    if (x == (BigInt)13) {
        return 13;
    }
    if (x == (BigInt)14) {
        return 14;
    }
    if (x == (BigInt)15) {
        return 15;
    }
}
//функция для перевода в систему счисления с базой системы счисления для 16
string ten_base(BigInt x, int base) {
    //массив char'ов с элементами системы счисления
    char digits[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
    //проверка если база равна длинне массива с элементами системы счисления возвращаем изначальное число в виде строки
    if (base > (sizeof(digits) / sizeof(digits[0]))) return (string)x;
    //объявляем переменную res где будет жить и процветать результат рабоы нашей функции
    string res;
    //цикл пока ПеЛьменнаЯ х больше нуля 
    while (x > (BigInt)"0")
    {
        //создаём экземпляр класса BigInt под названием тэмп и присваиваем туда копию числа х >( 
        BigInt tmp(x);
        //в переменную темп присваиваем остаток от деления на базу
        tmp %= base;
        //в переменную res присваиваем сумму элемента массива с элементами системы счисления под ключом тэмп и переменной res
        res = digits[kakoeEtoInt(tmp)] + res;
        //делим переменную х на базу
        x /= base;
    }
    //возвращаем гений выполнения нашей функции
    return res;
}
//ну это мэйн, я в целом так, для красоты добавил
int main()
{
    //ставим русский в консоль
    setlocale(LC_ALL, "Russian");
    //делаем переменную для ввода бим бим
    string input;
    //вводим бам бам
    cin >> input;
    //проверяем что во вводе только циферки
    if (input.find_first_not_of("0123456789") == std::string::npos) {
        //создаём экземпляр класса BigNum со значением введённых циферок
        BigInt a(input);
        //демонстрируем пользователю гений компьютерной мысли просчитанный лучшим алгоритмом человечества находящимся в функции ten_base
        cout << ten_base(a, 16);
    }
    else {
        //ну а тут у нас в общем для тех кто глупый записочка O:)
        cerr << "Не пойми неправильно, но это программа не пускает \"всяких\" людишек, которые пытаются пронести буквы ссобой, не надо так, дядя!";
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

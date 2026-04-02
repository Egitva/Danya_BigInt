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
private:
    void normalize();
public:
    //конструкторы с их перегрузками:
    BigInt(unsigned long long n = 0);
    BigInt(const string&);
    BigInt(const char*);
    BigInt(const BigInt&);

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
    friend BigInt operator^(const BigInt&, const BigInt&);

    //взятие корня
    friend BigInt sqrt(const BigInt& a);

    //Ввод и вывод
    friend ostream& operator<<(ostream&, const BigInt&);
    friend istream& operator>>(istream&, BigInt&);

    //Другие
    friend BigInt NthCatalan(int n);
    friend BigInt NthFibonacci(int n);
    friend BigInt Factorial(int n);

    //преобразование к типу стринг
    operator string() const;
    //преобразование к типу инт
    operator int() const;
};
// --------------------- Вспомогательная функция для base conversion ---------------------
int get_small_value(const BigInt& num) {
    if (Null(num)) return 0;
    if (num.digits.size() > 2) {
        throw std::runtime_error("Digit value too large for base conversion");
    }
    int val = 0;
    int p = 1;
    for (char d : num.digits) {
        val += static_cast<int>(d) * p;
        p *= 10;
    }
    return val;
}

// --------------------- normalize ---------------------
void BigInt::normalize() {
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
}

// --------------------- Конструкторы ---------------------
BigInt::BigInt(unsigned long long nr) {
    digits.clear();
    do {
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
    // normalize не требуется — нет ведущих нулей
}

BigInt::BigInt(const string& s) {
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(static_cast<unsigned char>(s[i])))
            throw std::invalid_argument("ERROR");
        digits.push_back(s[i] - '0');
    }
    normalize();
}

BigInt::BigInt(const char* s) {
    digits = "";
    int len = strlen(s);
    for (int i = len - 1; i >= 0; i--) {
        if (!isdigit(static_cast<unsigned char>(s[i])))
            throw std::invalid_argument("ERROR");
        digits.push_back(s[i] - '0');
    }
    normalize();
}

BigInt::BigInt(const BigInt& a) {
    digits = a.digits;
}

// --------------------- Вспомогательные функции ---------------------
bool Null(const BigInt& a) {
    return (a.digits.size() == 1 && a.digits[0] == 0);
}

int Length(const BigInt& a) {
    return a.digits.size();
}

int BigInt::operator[](const int index)const {
    if (digits.size() <= static_cast<size_t>(index) || index < 0)
        throw std::out_of_range("ERROR");
    return digits[index];
}

// --------------------- Сравнения ---------------------
bool operator==(const BigInt& a, const BigInt& b) {
    return a.digits == b.digits;
}

bool operator!=(const BigInt& a, const BigInt& b) {
    return !(a == b);
}

bool operator<(const BigInt& a, const BigInt& b) {
    int n = Length(a), m = Length(b);
    if (n != m)
        return n < m;
    while (n--) {
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    }
    return false;
}

bool operator>(const BigInt& a, const BigInt& b) {
    return b < a;
}

bool operator>=(const BigInt& a, const BigInt& b) {
    return !(a < b);
}

bool operator<=(const BigInt& a, const BigInt& b) {
    return a < b || a == b;
}

// --------------------- Присваивание ---------------------
BigInt& BigInt::operator=(const BigInt& a) {
    digits = a.digits;
    normalize();
    return *this;
}

// --------------------- Инкремент/декремент ---------------------
BigInt& BigInt::operator++() {
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9; i++)
        digits[i] = 0;
    if (i == n)
        digits.push_back(1);
    else
        digits[i]++;
    normalize();
    return *this;
}

BigInt BigInt::operator++(int temp) {
    BigInt aux = *this;
    ++(*this);
    return aux;
}

BigInt& BigInt::operator--() {
    if (digits[0] == 0 && digits.size() == 1)
        throw std::underflow_error("UNDERFLOW");
    int i, n = digits.size();
    for (i = 0; digits[i] == 0 && i < n; i++)
        digits[i] = 9;
    digits[i]--;
    while (n > 1 && digits[n - 1] == 0) {
        digits.pop_back();
        n--;
    }
    normalize();
    return *this;
}

BigInt BigInt::operator--(int temp) {
    BigInt aux = *this;
    --(*this);
    return aux;
}

// --------------------- Сложение/вычитание ---------------------
BigInt& operator+=(BigInt& a, const BigInt& b) {
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n; i++) {
        if (i < m)
            s = a.digits[i] + b.digits[i] + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = s % 10;
    }
    if (t)
        a.digits.push_back(t);
    a.normalize();
    return a;
}

BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt temp = a;
    temp += b;
    return temp;
}

BigInt& operator-=(BigInt& a, const BigInt& b) {
    if (a < b)
        throw std::underflow_error("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++) {
        if (i < m)
            s = a.digits[i] - b.digits[i] + t;
        else
            s = a.digits[i] + t;
        if (s < 0) {
            s += 10;
            t = -1;
        }
        else
            t = 0;
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0) {
        a.digits.pop_back();
        n--;
    }
    a.normalize();
    return a;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt temp = a;
    temp -= b;
    return temp;
}

// --------------------- Умножение ---------------------
BigInt& operator*=(BigInt& a, const BigInt& b) {
    if (Null(a) || Null(b)) {
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            v[i + j] += a.digits[i] * b.digits[j];
        }
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++) {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--)
        a.digits.pop_back();
    a.normalize();
    return a;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
    BigInt temp = a;
    temp *= b;
    return temp;
}

// --------------------- Деление ---------------------
BigInt& operator/=(BigInt& a, const BigInt& b) {
    if (Null(b))
        throw std::invalid_argument("Arithmetic Error: Division By 0");
    if (a < b) {
        a = BigInt();
        return a;
    }
    if (a == b) {
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * (BigInt)10 + (BigInt)a.digits[i] < b; i--) {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--) {
        t = t * (BigInt)10 + (BigInt)a.digits[i];
        for (cc = 9; (BigInt)cc * b > t; cc--);
        t -= (BigInt)cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for (i = 0; i < lgcat; i++)
        a.digits[i] = cat[lgcat - i - 1];
    a.digits.resize(lgcat);
    a.normalize();
    return a;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
    BigInt temp = a;
    temp /= b;
    return temp;
}

// --------------------- Остаток ---------------------
BigInt& operator%=(BigInt& a, const BigInt& b) {
    if (Null(b))
        throw std::invalid_argument("Arithmetic Error: Division By 0");
    if (a < b) {
        return a;
    }
    if (a == b) {
        a = BigInt();
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * (BigInt)10 + (BigInt)a.digits[i] < b; i--) {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--) {
        t = t * (BigInt)10 + (BigInt)a.digits[i];
        for (cc = 9; (BigInt)cc * b > t; cc--);
        t -= (BigInt)cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    a.normalize();
    return a;
}

BigInt operator%(const BigInt& a, const BigInt& b) {
    BigInt temp = a;
    temp %= b;
    return temp;
}

// --------------------- Возведение в степень ---------------------
BigInt& operator^=(BigInt& a, const BigInt& b) {
    BigInt Exponent = b;
    BigInt Base = a;
    a = BigInt(1);
    while (!Null(Exponent)) {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    a.normalize();
    return a;
}

BigInt operator^(const BigInt& a, const BigInt& b) {
    BigInt temp = a;
    temp ^= b;
    return temp;
}

// --------------------- divide_by_2 ---------------------
void divide_by_2(BigInt& a) {
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }
    while (a.digits.size() > 1 && !a.digits.back())
        a.digits.pop_back();
    a.normalize();
}

// --------------------- sqrt ---------------------
BigInt sqrt(const BigInt& a) {
    if (Null(a)) return BigInt(0);
    BigInt left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while (left <= right) {
        mid = BigInt();
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

// --------------------- Математические функции ---------------------
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

BigInt Factorial(int n) {
    BigInt f(1);
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

// --------------------- Ввод/вывод ---------------------
istream& operator>>(istream& in, BigInt& a) {
    string s;
    in >> s;
    if (s.empty()) {
        a = BigInt(0);
        return in;
    }
    for (char c : s) {
        if (!isdigit(static_cast<unsigned char>(c)))
            throw std::invalid_argument("INVALID NUMBER");
    }
    a.digits.clear();
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; i--) {
        a.digits.push_back(s[i] - '0');
    }
    a.normalize();
    return in;
}

ostream& operator<<(ostream& out, const BigInt& a) {
    if (Null(a)) {
        out << 0;
        return out;
    }
    for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; i--)
        out << static_cast<char>('0' + a.digits[i]);
    return out;
}

// --------------------- Преобразования ---------------------
BigInt::operator string() const {
    if (Null(*this)) return "0";
    string res;
    res.reserve(digits.size());
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--)
        res += '0' + digits[i];
    return res;
}

BigInt::operator int() const {
    if (digits.size() > 10)
        return 2147483647;
    long long val = 0;
    long long p = 1;
    for (char d : digits) {
        val += static_cast<long long>(d) * p;
        p *= 10;
    }
    if (val > 2147483647LL)
        return 2147483647;
    return static_cast<int>(val);
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

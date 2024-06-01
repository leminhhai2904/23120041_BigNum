#include "Stack.h"
#include "BigNum.h"

// Nhập xuất em đang làm mấy cái cơ bản thôi ạ, do em thấy làm nhập xuất kết hợp vs ký pháp Ba Lan
// thì sẽ hay hơn á anh
// Nạp chồng toán tử trích luồng, dùng để nhập vào số lớn.
istream& operator >> (istream& cin, BigInt& number)
{
    string s;
    cin >> s;

    number.digits.clear();
    number.sign = 0;

    int start = 0;
    if (s[0] == '-') {
        number.sign = 1;
        start = 1;
    }

    for (int i = start; i < s.size(); ++i)
        number.digits.push_back(s[i]);

    return cin;
}

// Nạp chồng toán tử chèn luồng, dùng để in ra số lớn.
ostream& operator << (ostream& cout, const BigInt& a)
{
    if (a.sign == 1) {
        cout << '-';
    }
    for (auto d : a.digits)
        cout << d;

    return cout;
}

// ----------------------------------------------

void add_zero(BigInt& a, int sz)
{
    // Đầu tiên đảo ngược số để tối ưu thời gian khi thêm phần tử.
    reverse(a.digits.begin(), a.digits.end());

    while (a.digits.size() < sz)
        a.digits.push_back('0');

    reverse(a.digits.begin(), a.digits.end());
}


// Đưa 2 số về cùng một size bằng các push các số 0 lên đầu.
void change(BigInt& a, BigInt& b)
{
    int sz = max(a.digits.size(), b.digits.size());
    add_zero(a, sz);
    add_zero(b, sz);
}



// Xóa các số 0 vô nghĩa ở đầu.
void del_zero(BigInt& a)
{
    reverse(a.digits.begin(), a.digits.end());

    while (a.digits.size() >= 2)
        if (a.digits.back() == '0')
            a.digits.pop_back();
        else
            break;

    reverse(a.digits.begin(), a.digits.end());
}   

void ConvertIntToBigInt(int a, BigInt& b) {
    b.digits.clear();
    while (a) {
        b.digits.push_back(a % 10 + '0');
        a /= 10;
    }
    reverse(b.digits.begin(), b.digits.end());
}
// ----------------------------------------------

bool operator < (BigInt a, BigInt b)
{
    if (a.sign != b.sign)
        return a.sign > b.sign;

    change(a, b);

    for (int i = 0; i < a.digits.size(); ++i) {
        if (a.digits[i] < b.digits[i]) {
            if (a.sign == 0)
                return true;
            else
                return false;
        }
        else if (a.digits[i] > b.digits[i]) {
            if (a.sign == 0)
                return false;
            else
                return true;
        }
    }
    return false;
}

bool operator <= (BigInt a, BigInt b)
{
    if (a.sign != b.sign)
        return a.sign > b.sign;

    change(a, b);

    for (int i = 0; i < a.digits.size(); ++i) {
        if (a.digits[i] < b.digits[i]) {
            if (a.sign == 0)
                return true;
            else
                return false;
        }
        else if (a.digits[i] > b.digits[i]) {
            if (a.sign == 0)
                return false;
            else
                return true;
        }
    }
    return true;
}


bool operator == (BigInt a, BigInt b)
{
    del_zero(a);
    del_zero(b);
    if (a.digits[0] == 0 && b.digits[0] == 0) {
        return true;
    }
    if (a.sign != b.sign || a.digits.size() != b.digits.size()) {
        return false;
    }
    change(a, b);

    for (int i = 0; i < a.digits.size(); ++i)
        if (a.digits[i] != b.digits[i]) 
            return false;

    return true;
}


bool operator < (BigInt a, int b) {
    BigInt c;
    ConvertIntToBigInt(b, c);
    return a < c;
}

bool operator <= (BigInt a, int b)
{
    BigInt c;
    ConvertIntToBigInt(b, c);
    return a <= c;
}

bool operator == (BigInt a, int b)
{
    BigInt c;
    ConvertIntToBigInt(b, c);
    return a == c;
}

BigInt operator+ (BigInt a, BigInt b) {
    change(a, b);
    BigInt result;
    int sz = a.digits.size();

    if (a.sign != b.sign) {
        if (a <= b) {
            result.sign = b.sign;
            result = b - a;
        }
        else {
            result.sign = a.sign;
            result = a - b;
        }
    }
    else {
        int rem = 0;
        for (int i = sz - 1; i >= 0; --i)
        {
            int x = a.digits[i] - '0' + b.digits[i] - '0' + rem;
            rem = x / 10;
            x = (x % 10) + '0';
            result.digits.push_back(x);
        }
        rem += '0';
        result.digits.push_back(rem);
        reverse(result.digits.begin(), result.digits.end());
        del_zero(result);
        result.sign = a.sign;
    }
    
    return result;
}

BigInt operator- (BigInt a, BigInt b) {
    change(a, b);
    BigInt result;
    int sz = a.digits.size();

    if (a.sign != b.sign) {
        if (b.sign == 0) {
            b.sign = 1;
        }
        else {
            b.sign = 0;
        }
        result = a + b;
        result.sign = a.sign;
    }
    else {
        if (a.sign == 0) {
            if (a < b) {
                result.sign = 1;
                BigInt c = a;
                a = b;
                b = c;
            }
            else {
                result.sign = 0;
            }

            int rem = 0;
            for (int i = sz - 1; i >= 0; --i)
            {
                int x = (a.digits[i] - '0') - (b.digits[i] - '0') - rem;
                if (x < 0)
                {
                    x += 10;
                    rem = 1;
                }
                else
                    rem = 0;
                x += '0';
                result.digits.push_back(x);
            }
            reverse(result.digits.begin(), result.digits.end());
            del_zero(result);
        }
        else {
            if (a < b) {
                result.sign = 1;
            }
            else {
                result.sign = 0;
                BigInt c = a;
                a = b;
                b = c;
            }

            int rem = 0;
            for (int i = sz - 1; i >= 0; --i)
            {
                int x = (a.digits[i] - '0') - (b.digits[i] - '0') - rem;
                if (x < 0)
                {
                    x += 10;
                    rem = 1;
                }
                else
                    rem = 0;
                x += '0';
                result.digits.push_back(x);
            }
            reverse(result.digits.begin(), result.digits.end());
            del_zero(result);
        }
    }

    return result;
}

BigInt operator* (BigInt a, BigInt b) {
    BigInt result;
    ConvertIntToBigInt(0, result);
    if (b == 0) {
        return result;
    }
    
    while (!(b <= 0)) {
        if (b.digits[b.digits.size() - 1] % 2 != 0) {
            result = result + a;
        }
        a = a * 2;
        b = b / 2;
    }
    return result;
}

BigInt operator/ (BigInt a, BigInt b)
{
    int sign;
    BigInt res;
    if (a.sign + b.sign == 1) {
        sign = 1;
    }
    else {
        sign = 0;
    }
    a.sign = b.sign = 0;
    res.digits.push_back('0'); // Ban đầu res = 0

    BigInt l, r;
    l.digits.push_back(1); // Gán l = 1.
    BigInt one;
    ConvertIntToBigInt(1, one);
    r = a; // Gán r = a.
    while (l <= r)
    {
        BigInt mid = (l + r) / 2;
        if (mid * b <= a)
        {
            res = mid;
            l = mid + one;
        }
        else
            r = mid - one;
    }
    res.sign = sign;
    return res;
}

BigInt operator* (BigInt a, int b) {
    BigInt result = a;
    while (--b) {
        result = result + a;
    }
    return result;
}

BigInt operator/ (BigInt a, int b) {
    BigInt result;
    if (b == 0) {
        cout << "Can't divide zero\n";
        return result;
    }
    else {
        long long cur = 0;
        if (b > 0) {
            result.sign = a.sign;
        }
        else {
            if (a.sign == 0) {
                result.sign = 1;
            }
            else {
                result.sign = 0;
            }
            b = 0 - b;
        }

        for (auto d : a.digits)
        {
            cur = cur * 10 + (d - '0');
            result.digits.push_back(cur / b + '0');
            cur %= b;
        }

        del_zero(result);
        return result;
    }
}

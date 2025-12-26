#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

class BigInt {
private:
    vector<char> v;

    void trim()
    {
        while (v.size() > 1 && v.back() == 0)
            v.pop_back();
    }

public:
    BigInt()
    {
        v.push_back(0);
        
    }

    BigInt(int num)
    {
        if (num == 0) v.push_back(0);
        else while (num > 0)
        {
            v.push_back(num % 10);
            num /= 10;
        }
    }

    BigInt(string s)
    {
        for (int i = s.size() - 1; i >= 0; --i)
            if (isdigit(s[i]))
                v.push_back(s[i] - '0');
        trim();
    }

    BigInt(const BigInt& other)
    {
        v = other.v;
        
    }

    int size() {
        return v.size();
        
    }

    BigInt operator[](int idx)
    {
        if (idx < 0 || idx >= v.size()) throw out_of_range("Index out of range");
        return BigInt((int)v[idx]);
    }

    bool operator==(const BigInt& b) const
    {
        return v == b.v;
    }

    BigInt operator++() {
        *this = *this + BigInt(1);
        return *this;
    }

    BigInt operator++(int) {
        BigInt temp = *this;
        *this = *this + BigInt(1);
        return temp;
    }

    void print() {
        for (int i = v.size() - 1; i >= 0; --i)
            cout << (char)(v[i] + '0');
    }

    friend ostream& operator<<(ostream& out, const BigInt& b) {
        if (b.v.size() <= 12) {
            for (int i = b.v.size() - 1; i >= 0; --i)
                out << (char)(b.v[i] + '0');
        } else {
            out << (char)(b.v.back() + '0') << '.';
            int count = 1;
            for (int i = b.v.size() - 2; i >= 0 && count < 7; --i, ++count)
                out << (char)(b.v[i] + '0');
            out << "e" << b.v.size() - 1;
        }
        return out;
    }

    BigInt operator+(BigInt b) {
        BigInt result;
        result.v.clear();
        int carry = 0;
        for (size_t i = 0; i < v.size() || i < b.v.size() || carry; ++i) {
            int d1 = (i < v.size()) ? v[i] : 0;
            int d2 = (i < b.v.size()) ? b.v[i] : 0;
            int sum = d1 + d2 + carry;
            result.v.push_back(sum % 10);
            carry = sum / 10;
        }
        result.trim();
        return result;
    }

    friend BigInt operator+(int a, BigInt b) {
        return BigInt(a) + b;
    }

    BigInt operator*(BigInt b) {
        BigInt result(0);
        result.v = vector<char>(v.size() + b.v.size(), 0);

        for (int i = 0; i < v.size(); ++i) {
            int carry = 0;
            for (int j = 0; j < b.v.size() || carry; ++j) {
                int bj = (j < b.v.size()) ? b.v[j] : 0;
                int cur = result.v[i + j] + v[i] * bj + carry;
                result.v[i + j] = cur % 10;
                carry = cur / 10;
            }
        }
        result.trim();
        return result;
    }

    bool operator<(const BigInt& b) const {
        if (v.size() != b.v.size()) return v.size() < b.v.size();
        for (int i = v.size() - 1; i >= 0; --i) {
            if (v[i] != b.v[i]) return v[i] < b.v[i];
        }
        return false;
    }

    BigInt operator-(BigInt b) {
        BigInt result;
        result.v.clear();
        int borrow = 0;

        for (size_t i = 0; i < v.size(); ++i) {
            int d1 = v[i];
            int d2 = (i < b.v.size()) ? b.v[i] : 0;
            int sub = d1 - d2 - borrow;
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.v.push_back(sub);
        }

        result.trim();
        return result;
    }

    BigInt operator/(BigInt b) {
        if (b == BigInt(0)) throw runtime_error("Division by zero");
        BigInt count(0), temp = *this;
        while (!(temp < b)) {
            temp = temp - b;
            count = count + BigInt(1);
        }
        return count;
    }

    BigInt operator%(BigInt b) {
        if (b == BigInt(0)) throw runtime_error("Modulo by zero");
        BigInt temp = *this;
        while (!(temp < b)) {
            temp = temp - b;
        }
        return temp;
    }

    BigInt fact_helper(BigInt acc, BigInt n) {
        if (n == BigInt(0) || n == BigInt(1)) return acc;
        return fact_helper(acc * n, n - BigInt(1));
    }

    BigInt fact() {
        return fact_helper(BigInt(1), *this);
    }

    BigInt fibo_helper(BigInt a, BigInt b, BigInt n) {
        if (n == BigInt(0)) return a;
        if (n == BigInt(1)) return b;
        return fibo_helper(b, a + b, n - BigInt(1));
    }

    BigInt fibo() {
        return fibo_helper(BigInt(0), BigInt(1), *this);
    }
};

void testUnit() {
    int space = 10;
    cout << "\a\nTestUnit:\n" << flush;
    system("whoami");
    system("date");

    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);

    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");

    cout << "n1(int)    :" << setw(space) << n1 << endl;
    cout << "s1(str)    :" << setw(space) << s1 << endl;
    cout << "n2(int)    :" << setw(space) << n2 << endl;
    cout << "s2(str)    :" << setw(space) << s2 << endl;
    cout << "n3(n2)     :" << setw(space) << n3 << endl;
    cout << "fibo(12345):" << setw(space) << fibo << endl;
    cout << "fact(50)   :" << setw(space) << fact << endl;
    cout << "imax       :" << setw(space) << imax << endl;
    cout << "big        :" << setw(space) << big << endl;
    cout << "big.print(): "; big.print(); cout << endl;

    cout << n2 << "/" << n1 << " = " << n2 / n1 << " rem " << n2 % n1 << endl;
    cout << "Fibo(" << fibo << ") = " << fibo.fibo() << endl;
    cout << "fact(" << fact << ") = " << fact.fact() << endl;

    cout << "10 + n1 = " << 10 + n1 << endl;
    cout << "n1 + 10 = " << n1 + 10 << endl;
    cout << "(n1 == s1)? --> " << ((n1 == s1) ? "true" : "false") << endl;
    cout << "n1++ = ?  --> before:" << n1++ << " after:" << n1 << endl;
    cout << "++s1 = ?  --> before:" << ++s1 << " after:" << s1 << endl;

    cout << "s2 * big = ? --> " << s2 * big << endl;
    cout << "big * s2 = ? --> " << big * s2 << endl;
}

int main() {
    testUnit();
    return 0;
}

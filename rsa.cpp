#include "rsa.h"
#include <QDir>
#include <QFile>
#include <iterator>
#include <iostream>
#include <QRandomGenerator>
RSA::RSA() {
open_exp = 0ull;
secret_exp = 0ull;
modulus = 0ull;
}
RSA::~RSA() {}
void RSA::GenerateKey() {
uint64_t p = 0ull, q = 0ull, euler = 0ull;
QRandomGenerator rand(time(0));
do {
p = 5000ull + rand.generate64() % 20000ull;
if (IsPrime(p)) break;
} while (true);
//generate q
do {
q = 5000ull + rand.generate64() % 20000ull;
if (q != p && IsPrime(q)) break;
} while (true);
modulus = p * q;
euler = (p - 1) * (q - 1);
open_exp = CalculateE(euler); //e
secret_exp = CalculateD(open_exp, euler); //d
}
bool RSA::IsPrime(uint64_t n, uint16_t iter) {
if (n < 4) return n == 2 || n == 3;
uint16_t s = 0;
uint64_t d = n - 1;
while ((d & 1) == 0) {
d >>= 1;
s++;
}
for (uint16_t i = 0; i < iter; i++) {
uint32_t a = 2 + rand() % (n - 3);
if (CheckComposite(n, a, d, s))
return false;
}
return true;
}
bool RSA::CheckComposite(uint64_t n, uint64_t a, uint64_t d, int32_t s) {
uint64_t x = Binpower(a, d, n);
if (x == 1 || x == n - 1)
return false;
for (int r = 1; r < s; r++) {
x = (uint64_t)x * x % n;
if (x == n - 1)
return false;
}
return true;
}
uint64_t RSA::Binpower(uint64_t base, uint64_t e, uint64_t mod) {
uint64_t result = 1;
base %= mod;
while (e) {
if (e & 1)
result = (uint64_t)result * base % mod;
base = (uint64_t)base * base % mod;
e >>= 1;
}
return result;
}
uint64_t RSA::CalculateE(uint64_t t) {
uint64_t e;
for (e = 2; e < t; e++)
if (GreatestCommonDivisor(e, t) == 1)
return e;
return -1;
}
uint64_t RSA::GreatestCommonDivisor(uint64_t e, uint64_t t) {
uint64_t temp;
while (e > 0){
temp = e;
e = t % e;
t = temp;
}
return t;
}
int64_t RSA::CalculateD(int64_t a, int64_t m) {
int64_t x, y;
gcdex(a, m, x, y);
x = (x % m + m) % m;
return x;
}
int64_t RSA::gcdex(int64_t a, int64_t b, int64_t& x, int64_t& y) {
if (a == 0) {
x = 0;
y = 1;
return b;
}
int64_t x1, y1;
int64_t d = gcdex(b % a, a, x1, y1);
x = y1 - (b / a) * x1;
y = x1;
return d;
}
uint8_t RSA::Encrypt(QString path, uint64_t sexp, uint64_t mod)
{
QFile filetoh(path);
if(filetoh.open(QFile::ReadOnly))
{
QCryptographicHash h(QCryptographicHash::Sha1);
if(!h.addData(&filetoh))
return FILE_NOT_OPEN;
filetoh.close();
QString hash = QString("%1").arg(QString(h.result().toHex()));
qDebug()<<hash;
std::string data = hash.toStdString();
std::vector<uint64_t> encrypt_hash(SHA_LEN);
for(size_t i = 0; i < SHA_LEN; ++i)
87
encrypt_hash[i] = Binpower(data[i], sexp, mod);
QString sign = QFileInfo(filetoh).fileName() + ".sig";
std::ofstream encrypted;
encrypted.open(sign.toLocal8Bit());
if (!encrypted.is_open()) return FILE_NOT_OPEN;
std::copy(encrypt_hash.begin(), encrypt_hash.end(), std::ostream_iterator<uint64_t>(encrypted, " "));
encrypted.close();
return OK;
}
}
std::string RSA::Decipher(QString path, uint64_t oexp, uint64_t mod)
{
std::ifstream encrypted(path.toLocal8Bit());
std::vector<uint64_t> encrypted_hash(SHA_LEN);
if (encrypted.is_open())
for (size_t i = 0; i < SHA_LEN; ++i)
encrypted >> encrypted_hash[i];
encrypted.close();
std::vector<uint8_t> decrypted_hash(SHA_LEN);
for (size_t i = 0; i < SHA_LEN; ++i)
decrypted_hash[i] = Binpower(encrypted_hash[i], oexp, mod);
std::string tmp(decrypted_hash.begin(), decrypted_hash.end());
return tmp;
}
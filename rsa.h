#ifndef RSA_H
#define RSA_H
#include <string>
#include <cstdint>
#include <QString>
#include <QCryptographicHash>
#define SHA_LEN 40
enum ERRORS
{
OK,
FILE_NOT_OPEN,
FILE_MIXED_UP
};
struct pKey
{
uint64_t modulus; //n
uint64_t open_exp; //e
};
class RSA
{
private:
bool IsPrime(uint64_t n, uint16_t iter = 5);
bool CheckComposite(uint64_t n, uint64_t a, uint64_t d, int32_t s);
uint64_t Binpower(uint64_t base, uint64_t e, uint64_t mod);
uint64_t CalculateE(uint64_t t);
uint64_t GreatestCommonDivisor(uint64_t e, uint64_t t);
int64_t CalculateD(int64_t a, int64_t m);
int64_t gcdex(int64_t a, int64_t b, int64_t& x, int64_t& y);
public:
RSA();
~RSA();
uint64_t modulus; //n
uint64_t secret_exp;//d
uint64_t open_exp; //e
void GenerateKey();
uint8_t Encrypt(QString path, uint64_t sexp, uint64_t mod);
std::string Decipher(QString path, uint64_t oexp, uint64_t mod);
};
#endif // RSA_H
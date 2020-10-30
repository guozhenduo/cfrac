#include <stdint.h>

//#define NDEBUG
#include <assert.h>

typedef struct fraction
{
    int numer; // numerator
    int denom; // denominator

} Fraction;

#define IS_IMPROPER_FRAC(frac) ((frac.numer > frac.denom) ? (2) : (1)) 
#define USE_RFC(frac, other_frac) (((frac.denom) != (other_frac.denom)))
#define USE_REDUC(frac) \
(gcd((frac.numer), (frac.denom)) != 1)
#define eq_frac(frac, other_frac) \
((frac.numer * other_frac.denom) == (frac.denom * other_frac.numer))
#define lt_frac(frac, other_frac) \
((frac.numer * other_frac.denom) < (frac.denom * other_frac.numer))
#define gt_frac(frac, other_frac) \
((frac.numer * other_frac.denom) > (frac.denom * other_frac.numer))
#define CAN_FOMATION_RATIO(frac, other_frac) \
((frac.numer * other_frac.denom) == \
 (frac.denom * other_frac.numer))
#define NOT_NULL(ptr) assert((ptr) != NULL)

typedef int int32_t;

void print_frac(const Fraction *frac, int put_line);
void fraction(Fraction *frac,int a,int b,int round);
void str_frac(const Fraction *self, char *str);
void rfc(Fraction *self, Fraction *other);
void to_inverse(Fraction *self);
void reduc_frac(Fraction *self);
Fraction inverse(Fraction self);
Fraction add_frac(Fraction self, Fraction other);
Fraction sub_frac(Fraction self, Fraction other);
Fraction mul_frac(Fraction self, Fraction other);
Fraction div_frac(Fraction self, Fraction other);
int cmp_frac(Fraction self, Fraction other);
Fraction improper_frac(int n, Fraction self);
float float_frac(const Fraction *self);

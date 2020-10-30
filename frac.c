#include "frac.h"
#include <stdio.h>

int gcd(int a, int b)
{
    register int temp = a % b;

    do
    {
        temp = a % b;
        a = b;
        b = temp;
    } while (temp);

    return a;
}

int lcm(int a, int b)
/* least common multiple */
{
    return (a * b) / (gcd(a, b));
}

void print_frac(const Fraction *self, int put_line)
{
    NOT_NULL(self);
    
    if (put_line == 1) printf("%d/%d%c",self->numer, self->denom, '\n');
    if (put_line == 0) printf("%d/%d",self->numer, self->denom);
}

void reduc_frac(Fraction *self)
{ 
    NOT_NULL(self);
    
    if (USE_REDUC(((Fraction) {self->numer, self->denom})))
    {
        register int temp = (int) (gcd(self->numer, self->denom));
        self->numer = self->numer / temp;
        self->denom = self->denom / temp;
    }
}

void fraction(Fraction *self,int a,int b,int reduce)
{
    NOT_NULL(self);
    assert(a);
    assert(b);
    
    self->numer = a;
    self->denom = b;

    if (reduce == 1) reduc_frac(self);
}

void rfc(Fraction *self, Fraction *other) 
/* reduction of fractions to a common denomminator */
{
    NOT_NULL(self);
    NOT_NULL(other);
    
    int common_mul = lcm(self->denom, other->denom);
    self->numer = (common_mul / (self->denom));
    self->denom = common_mul;
    other->numer = (common_mul / (other->denom));
    other->denom = common_mul;
}

void str_frac(const Fraction *self, char *str)
{
    NOT_NULL(self);
    NOT_NULL(str);
    
    sprintf(str, "%d/%d", 
    self->numer, self->denom);
}

Fraction add_frac(Fraction self, Fraction other)
{
    if (USE_RFC(self, other)) rfc(&self, &other);

    Fraction frac;
    fraction(&frac, self.numer + other.numer,
    self.denom, 1);

    return frac;
}

Fraction sub_frac(Fraction self, Fraction other)
{
    if (USE_RFC(self, other)) rfc(&self, &other);
    
    Fraction frac; 
    fraction(&frac, self.numer - other.numer, 
    self.denom, 1);
    
    return frac;
}

Fraction mul_frac(Fraction self, Fraction other)
{
    Fraction frac;

    fraction(&frac, self.numer * other.numer, 
    self.denom * other.denom, 1);

    return frac;
}

void to_inverse(Fraction *self) // to_inverse
{
    NOT_NULL(self);
    
    int temp = self->denom;
    self->denom = self->numer; 
    self->numer = temp;
    /* notes:
    The reciprocal is a fraction 
    whose numerator and denominator 
    are reversed,
    and 1/3 is inverse of 3*/
}

Fraction inverse(Fraction self)
{
    to_inverse(&self);

    return self;
}

Fraction div_frac(Fraction self, Fraction other)
{
    to_inverse(&other);
    
    return mul_frac(self, other);
    /* Fractional division is 
    the dividend multiplied by the 
    reciprocal of 
    the divisor */
}

int cmp_frac(Fraction self, Fraction other)
{
    if (eq_frac(self, other) == 1) return 1;
    if (lt_frac(self, other) == 1) return -1;
    if (gt_frac(self, other) == 1) return 1;

    return 2;
}

Fraction improper_frac(int n, Fraction self) // mixed number to improper fraction
{
    Fraction result;
    fraction(&result, n * self.denom + self.numer,
             self.denom, 1);

   return result; 
}

float float_frac(const Fraction *self)
{
    return ((float) self->numer) / \
           ((float) self->denom);
}

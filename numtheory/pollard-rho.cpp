/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Pollard Rho Factoring Algorithm
 *
 * Credit:
 *   Pollard.
 *   By Per Austrin
 */

#include "gcd and mulmod functions"

template <class T> inline T pollard_step(T x, T N) { 
  T r = mulmod(x, x, N); 
  if (++r == N) r = 0;
  return r; /* r = x^2+1 (mod N) */
}

/* Returns a non-trivial factor of N. (Note that if N is
 * prime, pollard_rho never returns) */
template <class T> T pollard_rho(T N, int maxiter = 500) {
  T x = random() % N, y = x, d;
  int iter = 0;
  if (!(N & 1)) return 2;  /* Check factor 2 */
  /* Small factor check. */
  for (d = 3; d <= 997; d += 2)
    if (N % d == 0) return d;

  for (d = 1; d == 1; ) {
    /* Reseed if too many iterations passed. */
    if (iter++ == maxiter)
      x = y = random() % N, iter = 0;
    x = pollard_step(x, N);
    y = pollard_step(pollard_step(y, N), N);
    d = gcd(y - x, N);
    if (d == N) d = 1;
  }
  return d;
}

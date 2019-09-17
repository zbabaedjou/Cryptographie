# RSA modulo en commun 

Une personne  C communique avec une deux  A et B, en utilisant le même module RSA n commun, avec des paires de clés distinctes (eA, dA) et (eB, dB).
 
Notons  (n, eA) la clé publique de A et (n, eB) la clé publique de B.
 On suppose de plus que eA et eB sont premiers entre eux (ce qui est le plus général).
On peut trouver x et y tels que :
xeA + yeB = 1. (coefficients de bezout)
Si un expéditeur C envoie un message m à A et B, il envoie :
cA = meA mod n,
cB = meB mod n.
Alors tout le monde est capable de retrouver m par la formule :
m = cA^x*cB^y mod n.

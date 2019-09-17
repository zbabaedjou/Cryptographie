# DFA sur le DES (15ème tour)
	Projet réalisé Ziadath Babaedjou - Mars 2019
Objectif : 
================================================================
	Obtenir La clé du Chiffrement DES en se basant sur les résultats d’une attaque par injection de faute,

Données :
================================================================ 
	Il a été mis en notre possession un message claire un message chiffré sans faute et 32 messages chiffrés avec faute( Faute insérée à la sortie du 15ème tour)

Fonctionnement
================================================================

L’objectif de l’attaque par injection de faute (DFA) est de pouvoir retrouver la clé du chiffrement en insérant consciemment des erreurs pendant le chiffrement.

	Dans le cas du DES, cette attaque provoque la modification d’un bit de sortie à un tour donné. Ce qui permettra de retrouver une partie de la clé. Et donc en effectuant cette procédure plusieurs fois sur le même tour et en s’assurant de ne pas insérer l’erreur au même endroit à chaque fois, on pourrait retrouver la clé Secrète.

	Lorsque l’attaque est effectuée au 15ème tour du DES (ce qui est le cas dans ce exercice), c’est le bloc de bit R15 qui est affecté(en modifiant un ou des bits , 1 devient 0 ou 0 devient 1). Le bloc obtenue sera appelé R15*. Ces modification se propage  dans le calcule de la fonction F (F=P[S(E(R15) XOR K16)] et affecte les deux derniers bloc R16 ( R16=L15 XOR F(R15)) et L16(L16=R15), On aura donc en sortie  R16* et L16* avec :

R16*= L15 XOR F(R15*,K16)
L16*= R15*
E : La fonction d’expansion qui fait passer  R15  de 32bits à 48 bits
S : La qui prend en entrée 6 bits et en ressort 4.

##Comment retrouver la clé : 

### On cherche d’abord K16
	On calcule d’abord R16 XOR R16*

R16 XOR R16*= L15 XOR F(R15) XOR  L15 XOR F(R15*)
		   = F(R15) XOR F(R15*)
		   = P(S(E(R15) XOR K16)) XOR P(S(E(R15*) XOR K16))

Ensuite on calcul P-1(R16 XOR R16*) avec P-1 la permutation inverse de P
P-1(R16 XOR R16*)= P-1[P(S(E(R15) XOR K16)) XOR P(S(E(R15*) XOR K16))]
		       =(S(E(R15) XOR K16) XOR S(E(R15*) XOR K16) 


A cette étape, seule  K ,,16,, est inconnue.  Pour la retrouver, on va  calculer pour chaque chiffrée avec faute (S(E(R ,,15,, )i XOR K’) XOR S(E(R ,,15*,,) ,,i,, XOR K’) où i représente le numéro de la Sbox affectée(déterminé en faisant le R ,,15,, XOR R ,,15*,, ) et K ’ une clé de 6 bits Générer aléatoirement. 
La sortie de ce calcule sera comparé avec avec les 4 bits de P ^^-1^^ (R ,,16,, XOR R ,,16*,, ) qui correspondent à cette Sbox . On va utiliser 26  K ^^’^^ différent pour chaque chiffré. Si après comparaison les bits sont identiques  On va stocker le K ^^’^^ dans une tables tout en tenant compte du numéro de la Sbox. On aura en moyenne 4 clé qui marcherons pour chaque chiffré. Enfin,  pour chaque Sbox on fera l’intersection des K ^^’^^ pour en retirer le bon.
On aura à cette étape la clé K ,,16,,  en concaténant le bon K’ de chaque Sbox dans l’ordre.
Avec K ,,16,,  on pourra retrouver K en effectuant le processus inverse de la génération de sous clé du DES et en faisant ensuite une recherche exhaustive de 2 ^^8^^ .


## Détermination de K Complet
	Avec le K16 précédemment trouvé, on pourra retrouver la complète de 64 bits.
En effet les 64 bits ne sont pas t=tous utilisé. Au début de la génération des clés, on effectue un permutation PC1  sur la clé. Puis on obtient un clé de 56 bits (8 bit qui sont des bit de parité sont retirés). Ensuite ses 56 bits passent par une seconde  permutation  PC2 , après  leur décalage à gauche i bits, puis on obtient une clé de 48 bit qui sera utiliser dans un tours du DES( 8 bits sont alors perdu). Cette dernière étape est réalisée à chaque tour en variant la valeur de i de 1 à 2 selon le tour. 
	Le tableau ci dessous récapitule le nombre de bit décalé par tour :
  

1 ----> 1
2 ----> 1
3 ----> 2
4 ----> 2
5 ----> 2
6 ----> 2
7 ----> 2
8 ----> 2
9 ----> 1
10 ---> 2
11 ---> 2
12 ---> 2
13 ---> 2
14 ---> 2
15 ---> 2
16 ---> 1


Au 16ème tour, le nombre de décalage fait 2 ^^8^^ et vu que le décalage est fait sur chaque bit de 2 ^^8^^ bits de la clé de 56 bits, chaque bits revient à ça place initiale. Et donc la clé  K ,,16,,  correspond à  K ^^1^^ . 
Ceci étant, pour retrouver K, on aura juste à faire passer notre  K ^^16^^ dans l’inverse de la permutation PC ^^2^^ (PC ^^2^^inv) puis dans l’inverse de la permutation de PC ^^1^^ (PC ^^1^^inv) . 
Le code fourni permet d'acquérir des chaînes de caractères et de vérifier que ces chaînes contiennent une S-expression valide et évaluer des formes basiques de scheme telle que define , set! ,if
il inclus aussi la gestion des erreurs de syntaxe dans l'intérpréteur 
Ce code fonctionne aussi bien en mode interactif qu'en mode script. 
Votre tâche sera de le compléter de façon à lire ces chaînes, extraire les objets Scheme qu'elles contiennent et afficher les objet ainsi acquis.  

Le répertoire est organisé ainsi : 
- Makefile pour compiler soit en mode debug (afficher les traces du programme) soit en mode release (produit final)
- src : qui contient le code C de l'interpréteur.
- include : qui contient toutes les définitions de types et prototypes de votre programme.
- tests_step0 : tests de la bonne formation de la S-expression et recopiage de la chaine entrée sur la sortie.
- tests_step1 : tests de l'affichage de notre S-expression construite en arbre binaire.
- tests_step2 : tests de l'interprétation des symboles internes et externes à scheme.
- tests_step3 : tests de l'interprétation des primitives et de la gestion de l'artihmétique

--- pour compiler le code en mode debug (il créé l'exécutable 'scheme')
$ make debug 

--- pour le lancer en mode interactif 
$ ./scheme 

--- pour le lancer en mode script 
$ ./scheme monFichier.scm

--- pour le lancer sur le fichier 02_readint.scm
$ ./scheme tests/02_readint.scm

--- pour lancer le programme de test sur l'ensemble des fichiers de tests_step0 en mode batch (non interactif)
$ ../testing/simpleUnitTest.sh -b -e ./scheme tests/simple/*.scm

--- pour créer l'archive à envoyer au profs (cela vous créé un tgz avec votre nom et la date)
$ make tarball

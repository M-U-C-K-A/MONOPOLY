# pour gerer les parametres

chaque utilisateur a accées a un panel dit "parametre" 
avec des reglages comme 

- couleurs ? on : off
- map récapitulatif ? on : off
- card des joueurs ? on : off
- lancement auto des dé ? on : off
- désactiver les couleurs ? on : off
- se rename ? on : off !cette option peut posé des soucis !
- langue ? [fr,en,es,de,it,ru] !cette option peut posé des soucis !

et un fichier config.yml qui contient les parametres par defaut
des utilisateurs. accesible uniquement par l'administrateur.

### ce panel doit permetre de :

- changer l'argent d'un joueur
- exclure un joueur de la partie
- changer de position un joueur
- adapter les valeurs (tour de prison maximum)
- prix sortie de prison
- valeur de la case départ


## Points à vérifier ou ajouter

1. **Gestion des Parties :**
   - Sauvegarder et charger une partie.
   - Recommencer une partie sans redémarrer l'application.

2. **Interactions des Joueurs :**
   - Ajouter un chat en ligne pour que les joueurs puissent communiquer.
   - Intégrer des échanges entre joueurs pour permettre des transactions (argent, propriétés).

3. **Mécanique de Jeu :**
   - Définir des règles pour les propriétés (achat, vente, hypothèques).
   - Gérer les cartes Chance et Caisse de Communauté avec leurs effets.

4. **Événements Spéciaux :**
   - Intégrer des événements spéciaux comme des pénalités pour les joueurs qui vont en prison ou des bonus pour des actions spécifiques.

5. **Gestion des Dés :**
   - Assurer que le système de lancement des dés fonctionne correctement, avec des effets en cas de doubles (comme un second lancement).

6. **Statistiques et Suivi :**
   - Mettre en place un système de statistiques pour suivre les performances des joueurs (argent gagné/perdu, propriétés possédées).
   - Ajouter un historique des transactions pour chaque joueur.

7. **Interface Utilisateur :**
   - Assurer une interface graphique ou une interface utilisateur en ligne de commande conviviale.
   - Offrir des options de personnalisation pour les utilisateurs, comme des thèmes ou des styles d'affichage.

8. **Paramètres de Jeu :**
   - Inclure des paramètres de difficulté pour les bots si vous en ajoutez, comme agressivité ou stratégie.
   - Proposer un mode de jeu rapide ou classique avec des règles simplifiées.
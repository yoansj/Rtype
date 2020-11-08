# RFC Serveur

## 1. Démarrage du serveur

Au départ l'utilisateur doit renseigner le port du serveur
```./r-type_server <port>```
Il doit renseigner un port valide sinon le serveur ne pourra pas démmarer

## 2. Lancement du client

Lorsque le client souhaite jouer il dispose de deux choix :

- Créer une partie

- Rejoindre une partie

## 2.1 Création d'une partie

Lorsque l'utilisateur crée une partie, le serveur attribue alors un numéro a la partie afin qu'elle puisse êtrre rejointe par d'autres joueurs. La communication s'effectue en TCP dans le lobby.

Lorsqu'une partie est créée un nouveau thread est créé par le serveur, ce thread servira pour toute la partie ainsi que pour le lobby.

Le thread se ferme si la partie est terminée ou si il n'y a aucun joueur connecté.

## 2.2 Rejoindre une partie

Lorsque le joueur souhaite rejoindre une partie il doit renseigner le numéro de la partie, si le numéro est correct alors il se connecte à la partie

## 3. Lobby

Dans le lobby le maître de jeu (premier joueur connecté) décide de quand il souhaite lancer la partie, le serveur envoie des paquets (TCP) toutes les x secondes afin de vérifier que les joueurs soient toujours connectés, les couleurs des joueurs sont attribuées en fonction de leur ordre d'arrivée.

Numéro du joueur | Couleur
--- | --- |
1   | Bleu
2   | Rouge
3   | Jaune
4   | Vert

Dans le lobby le maître du jeu peut sélectionner quels monstres vont apparaître durant la partie.

## 4. Lancement de la partie

Lors du lancement de la partie le serveur devra charger les monstres sélectionnés par le maître du jeu, ensuite le thread basculera afin d'appeler les fonctions du jeu et le jeu pourra alors commencer. A partir de ce moment la la connexion utilisée sera de l'UDP.

## 5. Thread principal

Durant le déroulement de la partie le thread principal du serveur reçoit les paquets de tous les clients connectés.

Chaque paquet devra disposer d'un ```id``` permettant de savoir à quelle partie (et donc a quel thread il est rattaché), ainsi lorsque le thread principal devra process ce paquet il saura quoi en faire.

Type de paquet | Action a effectuer
---            | --
Création de partie | Ouvrir un nouveau thread afin de créer un lobby, attribuer un id a cette partie et connecter le joueur qui a effectué la création au lobby
Rejoindre une partie | Chercher la partie correspondant au numéro envoyé par le client puis le connecter à cette partie
Paquets de jeu | Paquet donnant des informations sur le déroulement de la partie, par exemple la position ou encore les hp du joueur

Durant la partie les clients envoient des informations selon les actions qu'ils effectuent.
Le serveur est alors chargé de redistribuer ces informations aux autres clients afin qu'ils prennent conaissance de ce qu'il se passe dans la partie.

## 5.1 Contenu d'un paquet de jeu

Tous les paquets de jeu disposent de certaines informations communes telles que :

- Type du paquet : Numéro qui indique a quelle structure correspond le paquet envoyé (voir les structures ci-dessous)
- Index de l'envoyeur : Numéro entre 0 et 3 qui permet de savoir quel joueur a envoyé le paquet
- Id de la partie : Id qui correspond a la partie et au thread


Cette liste de paqutes décrit les paquets qui peuvent être envoyés ou reçus par le client

Type de paquet de jeu | Contenu du paquet | Action effectuée par le serveur | Action effectuée par le client
--- | --- | --- | --- |
Paquet de position | Position en x et en y du joueur | Le serveur vérifie la collision. En cas de collision avec une entité qui subit des dégats le serveur envoie un paquet pour dire au joueur qu'il a subit des dégats. Le serveur broadcast le paquet aux autres joueurs. | L'entité qui correspond au joueur est déplacée par rapport aux infirmations du paquet
Paquet de statut | Santé, armes | Le serveur broadcast le paquet aux autres clients | Le client update les sprites des autres joueurs en fonction du paquet reçu
Paquet d'entité | Contient des infos sur une entité | Rien | Le client affiche l'entité sur son écran
Paquet de partie | Permet de savoir si la partie est sur pause ou si des joueurs ont quitté | Renvoie aux autres clients | Fait pause ou fait disparaître le joueur et affiche un message
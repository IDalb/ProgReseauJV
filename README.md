Ce projet contient une socket universel (Windows et Posix) permettant d’envoyer un message a un serveur et de le recevoir en réponse.
Pour faire fonctionner les programmes, il faut dans un premier temps lancer le serveur (il est possible de mettre `ipv4` en argument pour n'accepter que les connections ipv4). Il faut ensuite lancer le client avec en argument l’ip du serveur et le message à envoyer.
Exemple :
```
ServerProject.exe
ClientProject.exe 127.0.0.1 helo
```

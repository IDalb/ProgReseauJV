Ce projet contient une socket universel (Windows et Posix) permettant d’envoyer un message a un serveur et de le recevoir en réponse.
Pour faire fonctionner les programmes, il faut dans un premier temps lancer le serveur avec l’argument `ipv4` ou `ipv6` pour sélectionner le type d’ip utilisé. Il faut ensuite lancer le client avec en argument l’ip du serveur et le message à envoyer.
Exemple :
```
ServerProject.exe ipv4
ClientProject.exe 127.0.0.1 helo
```

# Raven

Raven est un projet prototype visant à uniformiser le back-end de toute les applications ayant besoin d’un serveur Node.JS. Raven peut ainsi être vu comme une somme de services disponibles pour les applications. L’application n’ayant qu'à appeler le service dont elle a besoin sans se soucier de comment cela a été développé. Pour illustrer, traditionnellement quand une application a besoin de communiquer avec une base de données SQL, le développeur doit réécrire le code permettant de communiquer avec ladite base de données SQL. Cela peut être long, rébarbatif, contre productif et induisant une perte de temps pour le développeur. La philosophie de Raven est de supprimer ce gaspillage de temps inutile, chaque fonctionnalité est vue comme un service accessible par toute les applications supportées par Raven. Pour reprendre, dans l’exemple précédent Raven possède déjà un service permettant de dialoguer avec les bases de données SQL. Avec Raven le développeur aurait juste eu besoin de faire appel au service de dialogue correspondant sans avoir à tout re-développer. Sur ce principe, différents services sont déjà disponibles dans Raven comme la gestion des dialogue avec les API Facebook et Gmail, la gestion des bases de données SQL, la gestion de l’authentification d’utilisateur etc…

# Installation et lancement:

Installation:
    $ npm install

Lancement:
    $ npm start


# Ajouter une application:

Pour ajouter une application ajouter la dans le dossier Raven/App. Une fois celà fait ajouter dans le plugin FrontApps (/Plugins/Kernel/FrontApps.js) la ligne suivante
self.plugins.WebAPI.addApplication("URL_de_l'application","chemin_vers_l'application")
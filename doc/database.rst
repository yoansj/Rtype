Sqlite ressources
-------------------

| https://stackoverflow.com/questions/7183761/sqlite-how-to-bind-and-insert-date-from-c

- sqlite3_exec:

| https://www.sqlite.org/c3ref/exec.html

| https://dba.stackexchange.com/questions/221721/how-to-structure-table-in-mysql-for-group-chat-application

Ctor
----

    ::

        fetch un fichier de conf qui defini les table
        en meme temps recuperer le nom de chaque field pour les tables
        (qui va etre necessaire pour les requetes)

Command
--------

    ::

        Les commandes tu type select, update, insert, delete vous etres wrapper dans des methodes 
        et retourneront une string afin de chainer la requete

Complement des commandes
------------------------

    ::

        implementer complement de commandes du type:
        where, group by etc...

.. code :: cpp 

    template<typename ... Args>
    Request command(std::vector<string> fields, Args ...args);

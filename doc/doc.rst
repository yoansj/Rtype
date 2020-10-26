Lien sujet:
--------------

| https://intra.epitech.eu/module/2020/B-CPP-500/PAR-5-1/acti-409186/project/file/B-CPP-500_babel.pdf

Lien UML:
---------

- server:

| https://app.diagrams.net/#G1_LuVaR1d6ouV4LyZ5OuJ-jaRA4u9gFP0

- client:

| https://app.diagrams.net/#G1P1GAW1067o8lIkZp2941GVOU7MYNFG7X

Boost ASIO, Server Boost
-------------------------

  ::

    ref: https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio.html

    Boost Asio est une lib cross plateform utilisé pour le networking, et low level I/O programming, utilisé comme un model asynchrone(thread, concurrent model)

    desc: https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/overview/rationale.html

    include: BSD Socket, APIs; permit abstraction of class for a higher level communication such as HTTP

    https://www.boost.org/doc/libs/1_65_0/doc/html/boost_asio/overview/networking/bsd_sockets.html

    example here:
        https://www.boost.org/doc/libs/1_63_0/doc/html/boost_asio/examples.html

    build tcp socket from endpoint:
        https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/reference/basic_stream_socket/basic_stream_socket.html

    acceptor:
        https://www.boost.org/doc/libs/1_65_0/doc/html/boost_asio/reference/ip__tcp/acceptor.html
    
    ctor example:
        https://www.boost.org/doc/libs/1_63_0/doc/html/boost_asio/example/cpp11/echo/async_tcp_echo_server.cpp
        https://www.boost.org/doc/libs/1_71_0/doc/html/boost_asio/example/cpp17/coroutines_ts/chat_server.cpp
    https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

Qt Network
-----------

    ::

        Lien genérique pour les dépendances et tous : https://doc.qt.io/qt-5/qtnetwork-index.html#:~:text=Qt%20Network%20provides%20a%20set%20of%20APIs%20for,over%20HTTP%20are%20handled%20by%20various%20C%2B%2B%20classes.
        Qt Network provides a set of APIs for programming applications that use TCP/IP. Operations such as requests, cookies, and sending data over HTTP are handled by various C++ classes.

        Peut le combiner avec ssl pour plus de securité

        https://doc.qt.io/qt-5/qtnetwork-programming.html


Port Audio
-----------
    
    ::

        ref: http://www.portaudio.com/

        Cross plateform; enable you to write simple prog in C or C++; intended to promote audio exchange between users; has APIs to record audio and play sound



Opus/VOIP protocol
-----------------------------

    ::
        
        ref: https://opus-codec.org/

Storage and stream audio; audio transmission; RFC 6716
“Opus can handle a wide range of audio applications, including Voice over IP”


Conan
---------

    ::

        Cpp package manager

        public epitech conan: have boost + port audio libs + (bincrafter ?) => https://bintray.com/epitech/public-conan

        Bincrafter for network protocol ? => host byte order/ network byte order ??


Rq: Les liens conan concernant les repos c’est plus une liste de packet que tu peux installer; et le dernier ça parle des bincrafter utilisé pour les protocol internet: MQTT, HTTP etc...

=> ref : https://bincrafters.github.io/ ; “provider of binary packages,”


UML
------

…

Liens
------

    ::

        https://en.wikipedia.org/wiki/Session_Initiation_Protocol

Questions:
----------

    ::

        The protocol MUST be a client/server protocol but voice transport MUST be client to client (the server can have a proxy mode for conference calls or NAT-ed clients).

        The Babel project aims to create an SIP-like Voice Over IP (VOIP) protocol. It MUST be usable over the Internet (no multicast or anything LAN specific). => 

        UML structural or behavioral diagram

        client-client mais proxy ? => ducoup ça passe par le server pour les calls

===============================================


Format organisation :
---------------------

    ::

        séparer le projet en plusieurs mini tache, les mettre dans un backlog (on utilisera jira)
        gitlab voir si ça prend du temps à mettre en place ou à prendre en main

        test suite: google test ?

        meeting daily task: sur discord (en 10 ligne environ) => on parle de ce qu’on a fait et ce qu’on va faire

        Pour le cross platform on essaye d’apporter la modif sur windows à la fin de chaque tache

	UML: draw.io

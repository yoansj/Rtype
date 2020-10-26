Message Cathegories
-------------------

============ ========== ========= ==============
  ActionDB     Notif     Error     Action VOIP
============ ========== ========= ==============
  groupe      il est co  ex: 404   call
  chat        appel      
============ ========== ========= ==============

Message Types
--------------

========================= ===================== ======================= =========================
     ActionDB                 Notif              Error                        Action VOIP
========================= ===================== ======================= =========================
  601 create profil        201 get group         401 pseudo exist       501 notif call
  602 amend profil         202 get profil        402 auth failed        502 accept call
  603 create group         203 user added        403 msg not send       503 quit call
  604 add ctact group      204 user quit group   404 fail call          504 exchange data
  605 quit group           205 ctc added         405 profil not added   505 request info call
  606 add ctact            206 ctc deleted       406 ctc not exist      506 info call
  607 delete ctact         207 get groups        407 user exist         507 distribute info call
  608 login                208 get contacts        
========================= ===================== ======================= =========================

Message arguments
-----------------

======== ===========================================
  Code                      Arguments
======== ===========================================
  601     (pseudo, password)
  602     (pseudo, password, pp)
  603     (group_name)
  604     (id_group, pseudo)
  605     (id_group, pseudo)
  606     (pseudo)
  607     (pseudo)
  608     (pseudo, password)
  201     (id_group, group_name, list(pseudo), last_update_date)
  202     (pp, pseudo, status)
  203     (id_group, pseudo)
  204     (id_group, pseudo)
  205     (pp, pseudo, status)
  206     (pseudo)
  207     (list (id_group, group_name, list(pseudo), last_update_date))
  208     (list (pp, pseudo, status))
  401     (None)
  402     (None)
  403     (None)
  404     (None)
  405     (None)
  406     (None)
  407     (None)
  501     (id_group, list_pseudo, address, port)
  502     (pseudo, id_group)
  503     (pseudo, id_group)
  504     (pseudo, data, id_group)
  505     (id_group)
  506     (address, port, id_group)
  507     (id_group, list(address, port, pseudo))
======== ===========================================


Structure message
-----------------

  .. code:: c

        struct mssg_proto {
            message type: 
            
            std::string;
        };
        

UDP hole punching
-----------------

::

   link: https://networkengineering.stackexchange.com/questions/47276/how-udp-hole-punching-works

   udp hol punching: https://en.wikipedia.org/wiki/UDP_hole_punching
   stun: https://en.wikipedia.org/wiki/STUN

   both peer want exchnage their public ip addres to communicat, to do this they exchange those data through an existing connected server.
   they get know their public api address by sending a binding request to an external stun server that look like that in dns resolving name: _stun._udp@example.com usually they run on 3478 for udp protocol.
   Once they get their public address through stun server, they send it to the server.
   And start their handshkae connection by sending simultaneously paquet that enables NAT to let the connection open (hole punching), after that during the connection both client of to keep the connection alive by sending keep alive paquet

Sequential Diagram for protocol communication
---------------------------------------------

::

  Client                                          Server                                            Clients
    |                                                |                                                  |
    |                                                |                                                  |
    |                                                |                                                  |
    |---------------[call request(501)]------------> | --------------------[call notif]---------------> |
    |                                                |                                                  |
    |                                                |                                                  |
  (if noresponse ?)                                                                                     |
    |                                                |                                                  |
    |                                                |                                                  |
    |<-----------------------------------[server end call after 5min]---------------------------------> |
    |                                                |                                                  |
    |                                                |                                                  |
  (else)                                                                                                |
    |                                                |                                                  |
    |                                                | <---------------[accept call]------------------- |
    |                                                |                                                  |
    |<-------------[request info call]-------------- | -------------[request info call]---------------> |
    |                                                |                                                  |
    |-----------------[info call]------------------> | <---------------[info call]--------------------- |
    |                                                |                                                  |
    |<----------[distribute info call]-------------- | -----------[distribute info call]--------------> |
    |                                                |                                                  |
    |                                                |                                                  |
    |<--------------------------------------[transfert data]------------------------------------------> |
    |                                                |                                                  |
    |                                                |                                                  |
    |--------------------[quit call]---------------> |                                                  |
    |                                                |                                                  |
    |                                                | -----------------[quit call]-------------------> |



  Client                                          Server                                            Clients
    |                                                |                                                  |
    | -----------[create groupe (603)]-------------> |                                                  |
    |                                                |                                                  |
    | <------------[group ID (201)]----------------- |                                                  |
    |                                                |                                                  |
    |                                                |                                                  |
    |                                                |                                                  |
    | -------[add contact to groupe (604)]---------> |                                                  |
    |                                                |                                                  |
  (if user already exist)
    |                                                |                                                  |
    | <---------[profil not added (405)]------------ |                                                  |
    |                                                |                                                  |
  (else)
    |                                                |                                                  |
    |<------------[get group (201)]----------------- | --------------[user added (203)]---------------> |
    |                                                |                                                  |
    |                                                |                                                  |
    |                                                |                                                  |
    | -----------[quit groupe (605)]---------------> |                                                  |
    |                                                |                                                  |
    | <-----------[user left (204)]----------------- | --------------[user left (204)]----------------> |

    
  Client                                          Server                                            Clients
    |                                                |                                                  |
    | ---------------[add ctc(606)]----------------> |                                                  |
    |                                                |                                                  |
    (if ctc not exists)                                                                                 
    |                                                |                                                  |
    | <--------[profil not added(405)]-------------- |                                                  |
    |                                                |                                                  |
    (else)                                                                                              |
    |                                                |                                                  |
    | <----------------[ctc added(205)]------------- |------------------[ctc added(205)]--------------> |
    |                                                |                                                  |
    
    | --------------[delete ctc(607)]--------------> |                                                  |
    |                                                |                                                  |
    (if ctc not exist (in your ctc list)             |                                                  |
    |                                                |                                                  |
    | <-------------[ctc not exists(406)]----------- |                                                  |
    |                                                |                                                  |
    (else)                                                                                              |
    |                                                |                                                  |
    | <-------------[ctc deleted(206)]-------------- | ---------------[ctc deleted(206)]--------------> |


  Client                                          Server                                            Clients
    |                                                |                                                  |
    |-------------[create profil (601)]------------> |                                                  |
    (if pseudo exist)
    |                                                |                                                  |
    | <----------[pseudo exist (401)]--------------  |                                                  |
    |                                                |                                                  |
    (else)
    |                                                |                                                  |
    | <----------[profil created (202)]--------------|                                                  |
    |                                                |                                                  |
    |                                                |                                                  |
    |                                                |                                                  |
    |                                                |                                                  |
    |-----------[amend profile (602)]--------------> |                                                  |
    |                                                |                                                  |
    (if pseudo exist)
    |                                                |                                                  |
    | <----------[pseudo exist (401)]--------------  |                                                  |
    |                                                |                                                  |
    (else)                                                                                              |
    |                                                |                                                  |
    | <------------[get profil (202)]--------------- | --------------[get profil (202)]---------------> |
    |                                                |                                                  |
    |                                                |                                                  |
    |---------------[login (608)]------------------> |                                                  |
    |                                                |                                                  |
    (if account not exist)
    |                                                |                                                  |
    | <-------[account doesn't exist (402)]--------- |                                                  |
    |                                                |                                                  |
    (else)                                                                                              |
    |                                                |                                                  |
    |<-------------[get profil (202)]--------------- | --------------[get profil (202)]---------------> |
    |<------------[get contacts (208)]-------------- |                                                  |
    |<-------------[get groups (207)]--------------- |                                                  |

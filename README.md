# 2425_ESE_TPLinux_WERHENI_DEVAUX

## TP Linux Embarqué
 ## 1.1 Préparation de la carte SD
 
Avant de commencer, nous procéderons au flashage de la carte SD en utilisant l’image fournie par Terasic.

 ![image](https://github.com/user-attachments/assets/ecd2a030-d734-4f0b-ab77-e3d74cc01f61)

Ensuite, nous cliquerons sur 'Lire'.
 
![image](https://github.com/user-attachments/assets/7172c83d-5ec1-431e-be1f-d4309a79f1e2)

## 1.2 Démarrage

Ensuite, nous insérerons la carte SD fraîchement programmée, connecterons la carte VEEK-MT2S, puis allumerons l’appareil à l’aide du bouton rouge. Les voyants se mettront à clignoter et un système Linux démarrera.

![image](https://github.com/user-attachments/assets/add01c5b-57df-4c10-921c-18e1689eab46)

## 1.3 Connexion au système
## 1.3.1 Liaison série

Le premier moyen pour se connecter sur un objet embarqué, c’est très souvent
par le port série. Une fois que l’on aura eu accès au DE-10, on configurera le
réseau, pour pouvoir ensuite y accéder via ssh.
Tout d’abord, déterminer le port à utiliser pour se connecter à la carte.
Il y a plusieurs ports USB sur la carte :

— 2 hôtes usb A

— 1 usb B : max blaster pour la programmation

— 1 usb mini : uart to usb ← c’est celui-là qui nous intéresse

## 1.3.2 Utilisez un logiciel de liaison série

Sous Linux, nous utiliserons Minicom pour nous connecter via le port série.

<img width="1085" alt="Screenshot 2024-12-02 at 14 50 01" src="https://github.com/user-attachments/assets/fddfda87-db4d-4af2-b02c-bfa3fc81a8f8">

Minicom affiche la version utilisée (2.9), le port série détecté (/dev/tty.usbserial-AK050GOR), et les paramètres de communication configurés (115200 baud, 8N1). Le système cible fonctionne sous Ubuntu 16.04.2 LTS et demande un nom d'utilisateur pour se connecter, ce qui indique que l'accès au terminal est protégé par des identifiants. Les paramètres affichés confirment que le terminal est configuré correctement, mais il reste en mode hors ligne jusqu'à ce que la connexion soit établie avec succès en fournissant les identifiants appropriés. Ce processus est typique pour configurer ou déboguer des systèmes embarqués.


## Une fois connecté au SoC :
Pour vous identifier :

— login : root

— password : aucun (vraiment rien, ne tapez que sur entrée)

## 1.reboot

<img width="1085" alt="Screenshot 2024-12-02 at 14 52 16" src="https://github.com/user-attachments/assets/b90b9d05-e0f6-40b1-8cd3-c810a2806ea8">

Loggez-vous à nouveau. L’image copiée précédemment n’occupe pas la totalité de la carte SD.et la taille occupé par l'utilisateur egale à 1.3G

## 2.df -h
```
root@DE10-Standard:~# df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/root        14G  1.3G   12G  10% /
devtmpfs        375M     0  375M   0% /dev
tmpfs           376M     0  376M   0% /dev/shm
tmpfs           376M  9.8M  366M   3% /run
tmpfs           5.0M  4.0K  5.0M   1% /run/lock
tmpfs           376M     0  376M   0% /sys/fs/cgroup
tmpfs            76M     0   76M   0% /run/user/0
root@DE10-Standard:~# 
```
Cette commande est utile pour surveiller l'espace disque et l'utilisation des systèmes de fichiers montés. Elle montre que le système a encore beaucoup d'espace disponible, notamment sur la partition principale / avec seulement 10% d’utilisation. Les systèmes de fichiers temporaires (comme tmpfs) sont presque vides, indiquant une faible utilisation des ressources.

## 3. ./expand_rootfs.sh

est utilisé pour maximiser l'utilisation de l'espace disque disponible en étendant la partition racine et en redimensionnant le système de fichiers, souvent après avoir installé une image système sur un périphérique de stockage.

## 4. ./resize2fs_once

Des scripts sont fournis pour augmenter la taille du système de fichiers et profiter de l’ensemble de la carte SD :

```
root@DE10-Standard:~# ./resize2fs_once
Starting resize2fs_once
resize2fs 1.42.13 (17-May-2015)
The filesystem is already 3656192 (4k) blocks long.  Nothing to do!

The filesystem has been enlarged upon.
root@DE10-Standard:~# 
```


### Config  IP

la commande ifconfig exécutée dans un terminal Linux. Elle affiche les informations réseau de l'interface Ethernet eth0. L'adresse IP attribuée à cette interface est 192.168.0.254, qui est utilisée pour identifier le périphérique sur le réseau local. L'adresse de diffusion (broadcast) est 192.168.0.255, permettant de communiquer avec tous les appareils sur le même sous-réseau. Le masque de sous-réseau est 255.255.255.0, indiquant que le réseau est subdivisé en 256 adresses possibles (de 192.168.0.0 à 192.168.0.255).

```
ifconfig
eth0: inet addr:192.168.0.254  Bcast:192.168.0.255  Mask:255.255.255.0
```

on test avec un ping (depuis le terminal hors Minicom)
```
(base) hugodevaux@MacBook-Air-de-Hugo ~ % ping 192.168.0.254
PING 192.168.0.254 (192.168.0.254): 56 data bytes
64 bytes from 192.168.0.254: icmp_seq=0 ttl=64 time=23.006 ms
64 bytes from 192.168.0.254: icmp_seq=1 ttl=64 time=7.516 ms
64 bytes from 192.168.0.254: icmp_seq=2 ttl=64 time=3.054 ms
64 bytes from 192.168.0.254: icmp_seq=3 ttl=64 time=6.847 ms
64 bytes from 192.168.0.254: icmp_seq=4 ttl=64 time=10.026 ms
64 bytes from 192.168.0.254: icmp_seq=5 ttl=64 time=6.523 ms
^C

--- 192.168.0.254 ping statistics ---
6 packets transmitted, 6 packets received, 0.0% packet loss
round-trip min/avg/max/stddev = 3.054/9.495/23.006/6.378 ms
(base) hugodevaux@MacBook-Air-de-Hugo ~ %
```

<img width="848" alt="Screenshot 2024-12-02 at 15 36 42" src="https://github.com/user-attachments/assets/dc74c4f6-5f6b-4841-822f-73b7497f2c05">


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

Est utilisé pour maximiser l'utilisation de l'espace disque disponible en étendant la partition racine et en redimensionnant le système de fichiers, souvent après avoir installé une image système sur un périphérique de stockage.

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

## 1.3.3 Configuration réseau
Branchez la carte VEEK sur le switch via un câble réseau

— À l’aide de la commande ifconfig, Nous allons vérifier que la carte dispose d’une adresse IP,

— Éditer le fichier /etc/network/interfaces de la manière suivante :

source-directory /etc/network/interfaces.d

auto eth0

iface eth0 inet dhcp

allow-hotplug eth0


### Config  IP

la commande ifconfig exécutée dans un terminal Linux. Elle affiche les informations réseau de l'interface Ethernet eth0. L'adresse IP attribuée à cette interface est 192.168.0.254, qui est utilisée pour identifier le périphérique sur le réseau local. L'adresse de diffusion (broadcast) est 192.168.0.255, permettant de communiquer avec tous les appareils sur le même sous-réseau. Le masque de sous-réseau est 255.255.255.0, indiquant que le réseau est subdivisé en 256 adresses possibles (de 192.168.0.0 à 192.168.0.255).

```
ifconfig
eth0: inet addr:192.168.0.254  Bcast:192.168.0.255  Mask:255.255.255.0
```
## ping <adresse_ip>

Nous allons Rebooter une nouvelle fois, et là normalement vous allons avoir une adresse IP correcte. Et on test avec un ping (depuis le terminal hors Minicom)

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
## PermitEmptyPasswords yes

Nous allons vérifier le fichier de configuration SSH situé à /etc/ssh/sshd_config, en portant une attention particulière à la ligne suivante :

<img width="848" alt="Screenshot 2024-12-02 at 15 36 42" src="https://github.com/user-attachments/assets/dc74c4f6-5f6b-4841-822f-73b7497f2c05">


## 1.4 Découverte de la cible
## 1.4.1 Exploration des dossiers /sys/class et /proc

Explorez un peu votre environnement, par exemple :

— Répertoires présent sous la racine

— Dans /proc : cpuinfo, ioports, iomem. Utilisez les commandes cat, less ou more pour voir le contenu des fichiers.

— Le répertoire /sys/class contient des entrées nouvelles (par raport à un PC classique), saurez vous les reconnaître ? En particulier, explorez les répertoires suivants :

— /sys/class/leds/fpga_ledX/

— /proc/ioport

— /proc/iomem

— /proc/device-tree/sopc@0 à comparer avec le fichier iomem.

## 1.4.2 Compilation croisée

Pour cette partie, nous allons utiliser VirtualBox, accompagné d’une machine virtuelle Linux déjà configurée, qui vous permettra d’effectuer la compilation directement sur votre PC.

![image](https://github.com/user-attachments/assets/b123ead0-cad8-405d-8c48-b7ece5b906e2)

VirtualBox est un logiciel de virtualisation gratuit qui permet d'exécuter plusieurs systèmes d'exploitation sur un même ordinateur. Il crée des machines virtuelles (VM) pour tester des configurations ou des applications sans affecter le système principal.

Dans cette section, nous allons démarrer la machine virtuelle (VM):

![image](https://github.com/user-attachments/assets/d195fa8a-b8b2-4877-981c-5fa663c25fe6)

## 1.4.3 Hello world !

Nous allons utiliser un simple programme en C qui affiche le message 'Hello World!', comme le montre l'image ci-dessous.

![image](https://github.com/user-attachments/assets/dd0ab4d6-8290-45db-8371-cf0b21499192)

Pour compiler sur la VM, Nous allons utilisez le cross-compilateur :

![image](https://github.com/user-attachments/assets/cc90d3d3-76ac-480e-84fb-f69ed0ff9d0f)

Puisque la carte SoC est connectée au réseau, nous allons utiliser la commande suivante pour tester le transfert :

<img width="726" alt="Screenshot 2024-12-02 at 16 55 55" src="https://github.com/user-attachments/assets/92bfe0b0-41fc-44c2-b879-cf8fc8c6f67d">

## 1.4.4 Accès au matériel

Un certain nombre de drivers sont fournis. Comme tous les drivers sous Linux, ils sont accessible sous forme de fichiers. Par exemple pour allumer l’une des LED rouge de la carte, il suffit d’écrire un ’1’ dans le bon fichier

![image](https://github.com/user-attachments/assets/079903b6-c70c-40a5-b93d-bba9701c028a)

La commande echo "1" > /sys/class/leds/fpga_led1/brightness est utilisée dans un environnement Linux pour contrôler une LED connectée à un FPGA (Field Programmable Gate Array). 

## un programme en C pour un chenillard
Le programme présenté est écrit en C et permet de contrôler une LED connectée à un FPGA en modifiant sa luminosité via le système de fichiers sysfs sous Linux. Il commence par définir le chemin d'accès à la LED et un délai en millisecondes. Dans la fonction main, il ouvre le fichier /sys/class/leds/fpga_led1/brightness en mode écriture, puis entre dans une boucle où il alterne entre allumer et éteindre la LED en écrivant "1" ou "0" dans ce fichier. Entre chaque changement d'état, il attend le délai spécifié pour contrôler la fréquence de clignotement de la LED.

![image](https://github.com/user-attachments/assets/57396499-0e08-45dc-9b78-4a1d9ebf95d5)

## Test 
![Capture d'écran 2024-12-02 171124](https://github.com/user-attachments/assets/c44d163f-cc60-45b2-90e5-c8d701c20244)



## TP2

## 2.1 Accès aux registres

## 2.2 Compilation de module noyau sur la VM

Pour compiler des modules noyau dans la VM, Nous allons besoin des paquets suivant :

1. sudo apt install linux-headers-amd64
   
![image](https://github.com/user-attachments/assets/4df1b5e5-ec0c-4b2e-b96a-06b9fa5a72cd)

2. sudo apt install bc

![image](https://github.com/user-attachments/assets/96e95ddf-ba1d-463d-83ea-978d852817f4)


![image](https://github.com/user-attachments/assets/fc85777a-1683-4c38-b8ec-3c58531fd692)

chargez le et vérifiez que le module fonctionne bien (sudo dmesg).

![image](https://github.com/user-attachments/assets/e9b3440b-77c3-40f6-9b9a-e3098cc2c4cb)



![image](https://github.com/user-attachments/assets/d34bb478-156e-4d5a-a8f8-2fa023511045)

![image](https://github.com/user-attachments/assets/c6f64eb5-2c77-489e-81d4-c9df7d1878e5)

Afficher les Messages du Noyau avec dmesg
Lorsque le module est chargé, il écrit souvent des messages dans les logs du noyau. Vous pouvez les afficher avec :

![image](https://github.com/user-attachments/assets/8a4ea5b1-6e1c-41dc-b059-e828c795fb75)

Décharger le Module avec rmmod
Pour retirer (décharger) le module du noyau, utilisez :

![image](https://github.com/user-attachments/assets/d620097c-7f4f-47ca-a79d-da363d59a93e)

Vérifier les Messages du Noyau après le Déchargement
Une fois le module déchargé, utilisez à nouveau dmesg pour vérifier les messages :

![image](https://github.com/user-attachments/assets/75a754f4-3854-40bb-a0bf-74bc05734871)

![image](https://github.com/user-attachments/assets/6109597a-23da-4707-92dc-effa84c65e76)

![image](https://github.com/user-attachments/assets/9d13a668-b578-4f70-94b0-5446ed2657ad)


### 2.3.2 Récupéreation de la configuration actuelle du noyau



- FTP pour transferer la config (filezilla)
- which arm-linux-gnueabihf-gcc
- export

Les lignes commençant par export servent à définir des variables d'environnement qui seront utilisées par le système de compilation du noyau Linux. 

Le tiret à la fin du chemin sert de préfixe pour tous les outils de la chaîne de cross-compilation. Le système ajoutera automatiquement le nom de l'outil nécessaire après ce tiret.
(ex arm-linux-gnueabihf-gcc, arm-linux-gnueabihf-ld)

![image](https://github.com/user-attachments/assets/ba273523-d197-47a6-a6b6-f2d97ebc25fb)

## 2.3.4 Chenillard (Yes !)


![image](https://github.com/user-attachments/assets/b6ccddbf-dddf-4c38-9cac-5b635e0c7a6d)

##  Device tree TP3




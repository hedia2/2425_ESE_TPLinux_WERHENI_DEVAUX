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


<img width="726" alt="Screenshot 2024-12-02 at 16 55 55" src="https://github.com/user-attachments/assets/92bfe0b0-41fc-44c2-b879-cf8fc8c6f67d">

![image](https://github.com/user-attachments/assets/079903b6-c70c-40a5-b93d-bba9701c028a)


```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char path[100];
    
    if (argc != 3) {
        printf("Usage: %s <numero_led> <etat>\n", argv[0]);
        return 1;
    }
    
    snprintf(path, sizeof(path), "/sys/class/leds/fpga_led%s/brightness", argv[1]);
    
    fp = fopen(path, "w");
    if (fp == NULL) {
        printf("Erreur ouverture fichier\n");
        return 1;
    }
    
    fprintf(fp, "%s", argv[2]);
    fclose(fp);
    
    return 0;
}
```

On test:
```
root@DE10-Standard:~# ./ledControl.o 1 1
```
La LED s'allume !

## un programme en C pour un chenillard

![image](https://github.com/user-attachments/assets/57396499-0e08-45dc-9b78-4a1d9ebf95d5)

## Test 
![Capture d'écran 2024-12-02 171124](https://github.com/user-attachments/assets/c44d163f-cc60-45b2-90e5-c8d701c20244)








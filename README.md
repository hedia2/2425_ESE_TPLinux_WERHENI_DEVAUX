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

<img width="1085" alt="Screenshot 2024-12-02 at 14 50 01" src="https://github.com/user-attachments/assets/fddfda87-db4d-4af2-b02c-bfa3fc81a8f8">
<img width="1085" alt="Screenshot 2024-12-02 at 14 52 16" src="https://github.com/user-attachments/assets/b90b9d05-e0f6-40b1-8cd3-c810a2806ea8">

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

Après reboot:
```
root@DE10-Standard:~# ./resize2fs_once
Starting resize2fs_once
resize2fs 1.42.13 (17-May-2015)
The filesystem is already 3656192 (4k) blocks long.  Nothing to do!

The filesystem has been enlarged upon.
root@DE10-Standard:~# 
```

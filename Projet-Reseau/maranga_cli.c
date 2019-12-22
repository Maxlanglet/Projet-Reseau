//Maxime Langlet 000427821
/*
Ce travail a été inspirer par le TP9, il aura donc beaucoup de similitude avec celui-ci
*/

#define	_DEFAULT_SOURCE			/* Utilise les implémentation POSIX des fonctions réseaux */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#define PORT 1664
#define	INIT_TAILLE_BUFFER  1024			/* Taille initiale du buffer */

#define max(x,y) ( x < y ? y : x )

int main (int argc, char **argv) {

  struct sockaddr_in clientAddr, servrAddr;

  int port, res;
  char pseudo[INIT_TAILLE_BUFFER];

  int local_socket;
  // Comme c'est un entier qui va transiter sur le réseau, on utilise un type de données
  // particulier qui garantit la taille en mémoire de ce dernier
  uint32_t packet_size;
  int longueur_chaine;

  // Cette variable sert dans le cas où l'envoi (utilisation de send) nécessite plusieurs appels
  char *str_parser;
  int taille_envoyee = 0;

  // Les vriables nécessaires pour la réception d'un message
  char str_buffer[INIT_TAILLE_BUFFER];
  int taille_recue = 0;

  fd_set lecture; //variable multiplexage

  memset(&clientAddr, 0, sizeof(struct sockaddr_in));//copie 0 sur toute la structure de clientAddr
  memset(&servrAddr, 0, sizeof(struct sockaddr_in));

  //renvoie l'ordre correcte des parametres
  if (argc!=4) {
    fprintf (stderr, "maranga_cli adresse_ip_server port pseudonyme\n");
    return EXIT_FAILURE;
  }

//convertit l'adresse internet et la stock en binaire, puis on test si l'operation c'est fait avec succes
  res = inet_aton(argv[1], &servrAddr.sin_addr);
  if (!res) {
    fprintf (stderr, "[-] Impossible de convertir l'adresse <%s>\n", argv[1]);
    return EXIT_FAILURE;
  }


//variable declarées pour les messages d'erreurs
  errno = 0;
//convertion du port en long int
  port = strtol(argv[2], NULL, 10);
  if (errno!=0 && port ==0) {
    perror("[-] Impossible de convertir le port");
    return EXIT_FAILURE;
  }

//convetion representation memoire
  servrAddr.sin_port = htons(port);
  servrAddr.sin_family = AF_INET;

//creation socket
  local_socket = socket(PF_INET, SOCK_STREAM, 0);
  if (local_socket==-1) {
    fprintf (stderr, "[-] Imposible d'ouvrir le socket\n");
    return EXIT_FAILURE;
  }
  printf("[+]Socket client creer.\n");

//Préparation de la structure d'adresse de socket locale
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = htons(0);
  clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);


//Lien entre le descripteurs de fichier et la structure
  res = bind(local_socket,(struct sockaddr*) &clientAddr, sizeof( struct sockaddr_in));
  if (res==-1) {
    fprintf (stderr, "[-] Impossible de lier le socket et la structure d'adresse.\n");
    close (local_socket);                   /* On ferme le socket avant de quitter */
    return EXIT_FAILURE;
  }


//Connection au server
  res = connect(local_socket, (struct sockaddr*) &servrAddr, sizeof(struct sockaddr_in));
  if (res==-1) {
    fprintf(stderr, "[-] Impossible de se connecter au server\n" );
    close(local_socket);
    return EXIT_FAILURE;
  }
  printf("[+] Connection au server etablie\n");


//Initialisation de l'envoi du pseudo
  strcpy(pseudo, argv[3]);
  longueur_chaine = strlen(pseudo);
  packet_size=htonl(longueur_chaine);

//Envois de la taille du pseudo
  res = send(local_socket, &packet_size, sizeof(uint32_t), 0);
  if (res==-1) {
    fprintf(stderr, "[-] Imposible d'envoyer la taille du pseudonyme\n");
    close(local_socket);
    return EXIT_FAILURE;
  }

//Envois du pseudo
  for (str_parser = pseudo, taille_envoyee = 0; taille_envoyee<longueur_chaine; ) {
    res = send(local_socket, str_parser, longueur_chaine-taille_envoyee, 0);
    if (res==-1) {
      fprintf(stderr, "[-] Impossible d'envoyer le pseudonyme\n");
      close(local_socket);
      return EXIT_FAILURE;
    }
    taille_envoyee +=res;
    str_parser +=res;
  }

//On rentre dans la boucle qui essentiellement recois le message d'acceuil
  while (1) {

//recois la taille de l'info
    res = recv(local_socket, &packet_size, sizeof(uint32_t), 0);
    if (res==-1) {
      fprintf(stderr, "[-] Erreur reception de la taille du message d'acceuil\n");
      close(local_socket);
      return EXIT_FAILURE;
    }
    longueur_chaine = ntohl(packet_size);


//recois l'info
    for (str_parser = str_buffer, taille_recue=0; taille_recue< longueur_chaine; ) {
      res = recv(local_socket, str_parser, longueur_chaine-taille_recue, 0);

      if (res==-1) {
        fprintf(stderr, "[-] Impossible de recevoir le message d'acceuil\n");
        break;
      }
      taille_recue+=res;
      str_parser+=res;
    }
    str_buffer[taille_recue] = '\0';
    if (taille_recue != longueur_chaine) {
      fprintf(stderr, "[-] Reception partielle : %s \n", str_buffer);
    }
    else{
      printf("[+] %s\n", str_buffer);
      break;
    }
  }
  //Pareillement ci-dessous, ici nous recevons le premier anagramme
  int continue_loop = 1;
  while (continue_loop) {
    res = recv(local_socket, &packet_size, sizeof(uint32_t), 0);
    if (res==-1) {
      fprintf(stderr, "[-] Erreur reception de la taille du message d'acceuil\n");
      close(local_socket);
      return EXIT_FAILURE;
    }
    longueur_chaine = ntohl(packet_size);

    for (str_parser = str_buffer, taille_recue=0; taille_recue< longueur_chaine; ) {
      res = recv(local_socket, str_parser, longueur_chaine-taille_recue, 0);

      if (res==-1) {
        fprintf(stderr, "[-] Impossible de recevoir le message d'acceuil\n");
        break;
      }
      taille_recue+=res;
      str_parser+=res;
    }
    str_buffer[taille_recue] = '\0';
    if (taille_recue != longueur_chaine) {
      fprintf(stderr, "[-] Reception partielle : %s \n", str_buffer);
    }
    else{
      printf("[+] %s\n", str_buffer);
      continue_loop = 0;
    }
  }

//Cette boucle ci enverra ce qui a été taper par le clavier et recevra la reponse du client jusqu'a ce qu'on ecrive "!quit"
  while (1) {

//Multiplexage


    FD_ZERO (&lecture);
    FD_SET (STDIN_FILENO, &lecture);
    FD_SET (local_socket, &lecture);

    res = select(1+max(STDIN_FILENO, local_socket), &lecture, NULL, NULL, NULL);
    if (res==-1) {
      perror("[-] Erreur multiplexage");
      close(local_socket);
      return EXIT_FAILURE;
    }
//Si c'est le clavier, on lit le message et on l'envoie
    if (FD_ISSET(STDIN_FILENO, &lecture)) {
      fgets(str_buffer, INIT_TAILLE_BUFFER, stdin);
      longueur_chaine = strlen(str_buffer);

      if (str_buffer[longueur_chaine-1]=='\n') {
        str_buffer[longueur_chaine - 1] = '\0';
        longueur_chaine--;
      }

      packet_size = htonl(longueur_chaine);
      res = send(local_socket, &packet_size, sizeof(uint32_t), 0);
      if (res==-1) {
        fprintf(stderr, "[-] Imposible d'envoyer la taille du message\n");
        close(local_socket);
        //La Fermeture du socket est importante pour envoyé une notification au server, evitant que le server n'attende pour rien
        return EXIT_FAILURE;
      }

      for (str_parser = str_buffer, taille_envoyee = 0; taille_envoyee<longueur_chaine; ) {
        res = send(local_socket, str_parser, longueur_chaine-taille_envoyee, 0);
        if (res==-1) {
          fprintf(stderr, "[-] Impossible d'envoyer le message\n");
          close(local_socket);
          //La Fermeture du socket est importante pour envoyé une notification au server, evitant que le server n'attende pour rien

          return EXIT_FAILURE;
        }
        taille_envoyee +=res;
        str_parser +=res;
      }
//Si le str_buffer est "!quit" on quitte le server
      if (strcmp(str_buffer, "!quit")==0) {
        close(local_socket);
        printf("[+] Deconnecter du server\n");
        return EXIT_FAILURE;
      }
    }
/* Si c'est le socket, on lit et on affiche le message recu */
    if (FD_ISSET(local_socket, &lecture)) {
      res = recv(local_socket, &packet_size, sizeof(uint32_t), 0);
      if (res==-1) {
        fprintf(stderr, "[-] Erreur reception de la taille\n");
        close(local_socket);
        return EXIT_FAILURE;
      }
      longueur_chaine = ntohl(packet_size);

      for (str_parser = str_buffer, taille_recue=0; taille_recue< longueur_chaine; ) {
        res = recv(local_socket, str_parser, longueur_chaine-taille_recue, 0);

        if (res==-1) {
          fprintf(stderr, "[-] Impossible de recevoir le message\n");
          break;
        }
        else if(res==0){
          printf("[+] Fermeture socket cote server\n");
          break;
        }
        taille_recue+=res;
        str_parser+=res;
      }

      str_buffer[taille_recue] = '\0';
      if (taille_recue != longueur_chaine) {
        fprintf(stderr, "[-] Reception partielle : %s \n", str_buffer);
      }
      else{
        printf("[+] %s\n", str_buffer);
      }
    }
  }

  close(local_socket);
  return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

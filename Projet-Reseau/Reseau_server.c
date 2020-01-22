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
#include  <sys/mman.h>

#include "personal_strings.h"
#include "anagram.h"
#define PORT 1664
#define	INIT_TAILLE_BUFFER 1024			/* Taille initiale du buffer de réception */

//structure representant la base de données
typedef struct joueurs{
    int score ;
    char pseudo[20];
}joueurs;

//Initialisation de la base de données
joueurs* Tableau(int nombre_joueurs){
    joueurs* tableau_initial = malloc(nombre_joueurs*sizeof(joueurs));
    return tableau_initial;
}
//Insertion d'un nouveau joueur
joueurs* insererJoueurs(int nombre_joueurs, joueurs* tableau){
    tableau = realloc(tableau, nombre_joueurs*sizeof(joueurs));
    return tableau;
}

int nombre_joueurs=0;



int main (int argc, char **argv){

  int res, local_socket, port;
  struct sockaddr_in servrAddr;

  // Les variables nécessaires pour la réception et l'envoi d'un message
  char* str_parser;
  char str_buffer[INIT_TAILLE_BUFFER];
  char message_acceuil[INIT_TAILLE_BUFFER];
  char pseudo[INIT_TAILLE_BUFFER];

  joueurs* liste_joueurs = Tableau(1);
  int pos_joueurs=0;

  int taille_recue = 0;
  int taille_envoyee = 0;





  memset(&servrAddr, 0, sizeof(struct sockaddr_in));

  if (argc < 3) {
    printf("[-] Mauvais nombre d'arguments : port chemin_vers_dictionnaire message_acceuil\n");//port chemin_vers_dictionnaire message_acceuil
    return EXIT_FAILURE;
  }

  errno=0;
  port = strtol(argv[1], NULL, 10);//conversion du port en int avec test
  if (errno!=0 && port==0) {
    printf("[-] Impossible de convertir le port <%s>", argv[1]);
    return EXIT_FAILURE;
  }
  //Préparation de la structure d'adresse de socket locale

  servrAddr.sin_port = htons(port);
  servrAddr.sin_family=AF_INET;
  servrAddr.sin_addr.s_addr=htonl(INADDR_ANY);//inet_addr("127.0.0.1");

//Creation d'un socket
  local_socket = socket(PF_INET,SOCK_STREAM,0);
  if (local_socket==-1) {
    printf("[-] Impossible d'ouvrir le socket\n");
    return EXIT_FAILURE;
  }


  //Lien entre le descripteurs de fichier et la structure

  res = bind(local_socket,(struct sockaddr*)&servrAddr, sizeof(servrAddr));
  if (res < 0) {
    close(local_socket);
    printf("[-]Erreur dans le bind\n");
    return EXIT_FAILURE;
  }

//Ecoute d'un client
  res = listen(local_socket, 100);
  if (res==0) {
    printf("[+]En ecoute...\n");
  }
  else{
    printf("[-]Erreur dans l'écoute\n");
    close(local_socket);
    return EXIT_FAILURE;
  }






  while (1) {
    //Variable necesaire pour la taille des messages et pour creer un enfant par un fork
    uint32_t packet_size;
    int longueur_chaine;
    int pid;
    socklen_t addr_size_client;
    int socket_client;
    struct sockaddr_in adresse_client;

    //Accept la connection avec un client

    socket_client = accept(local_socket, (struct sockaddr*)&adresse_client, &addr_size_client);
		if(local_socket < 0){
      printf("[-] Connexion impossible\n");
			continue;
		}
		printf("[+] Connection accptee %s:%d\n", inet_ntoa(adresse_client.sin_addr), ntohs(adresse_client.sin_port));
    nombre_joueurs++;


    //On recoit la taille du pseudoyme d'un client
    res = recv(socket_client, &packet_size, sizeof(uint32_t), 0);
    if (res==-1) {
      fprintf(stderr, "[-] Erreur reception de la taille du pseudonyme\n");
      close(local_socket);
      return EXIT_FAILURE;
    }
    longueur_chaine = ntohl(packet_size);


//On recoit le pseudonyme du client
    for (str_parser = str_buffer, taille_recue=0; taille_recue< longueur_chaine; ) {
      res = recv(socket_client, str_parser, longueur_chaine-taille_recue, 0);

      if (res==-1) {
        fprintf(stderr, "[-] Impossible de recevoir le pseudonyme\n");
        break;
      }
      taille_recue+=res;
      str_parser+=res;
    }
    str_buffer[taille_recue] = '\0';
    if (taille_recue != longueur_chaine) {
      fprintf(stderr, "[-] Reception partielle du pseudonyme : %s \n", str_buffer);
    }
    else{
      printf("[+] Pseudonyme recus : %s\n", str_buffer);
    }

//Et on le stock dans une variable pour ensuite l'inserer dans la base de donnees
    memset(pseudo, 0, sizeof pseudo);
    strcpy(pseudo, str_buffer);

    if (nombre_joueurs==1) {
      strcpy(liste_joueurs[0].pseudo, pseudo);
      pos_joueurs=0;
    }
    else{
      for (int i = 0; i < nombre_joueurs; i++) {
        if (strcmp(liste_joueurs[i].pseudo, pseudo)==0) {
          pos_joueurs=i;
        }
        else{
          pos_joueurs=nombre_joueurs-1;
          insererJoueurs(nombre_joueurs, liste_joueurs);
          strcpy(liste_joueurs[pos_joueurs].pseudo, pseudo);
        }
      }
    }


    if((pid = fork()) == 0){

//On est dans le processus enfant, c'est ici que nous envoyons le message d'acceuil par le meme proceder que precedemment

      memset(str_buffer, 0, sizeof str_buffer);
      memset(message_acceuil, 0, sizeof message_acceuil);

      for (int i = 2; i < argc; i++) {
        strcat(message_acceuil, argv[i]);
        strcat(message_acceuil, " ");
      }

      strcat(str_buffer, message_acceuil);
      longueur_chaine = strlen(str_buffer);//redefinition de la longueur de la chaine qu'on va envoyer
      packet_size = htonl(longueur_chaine);

      res = send(socket_client, &packet_size, sizeof(uint32_t),0);
      if (res==-1) {
        printf("[-] Impossible d'envoyer la taille du message au client\n");
        close(socket_client);
        continue;
      }

      for (str_parser=str_buffer, taille_envoyee=0; taille_envoyee<longueur_chaine; ) {
        res = send(socket_client, str_parser, longueur_chaine-taille_envoyee, 0);
        if (res==-1) {
          printf("[-] Impossible d'envoyer le message\n");
          close(socket_client);
          continue;
        }
        taille_envoyee += res;
        str_parser += res;
      }

      //definition des variables pour le score et le dictionnaire

      int continue_loop=1;
      int score_inst=0;

      int ret_val;
      dict_t dico;
      anagram_t anagram;

      //Initialisation du dictionnaire
      ret_val = init_dico (&dico, "dictionnaire");
      if (ret_val == -1){
        perror ("[-] Erreur initialisation dictionnaire ");
        return EXIT_FAILURE;
      }
      init_anagram (&anagram);
      ret_val = new_anagram (&anagram, &dico);
      if (ret_val == -1){
          perror ("[-] Erreur création d'un nouvel anagramme");
          free_anagram (&anagram);
          free_dico (&dico);

          return EXIT_FAILURE;
      }

//Initialisation de la taille de l'annagramme a envoyer
      longueur_chaine = strlen(anagram.mot_courant.str);
      score_inst = longueur_chaine;
      packet_size = htonl(longueur_chaine);

      res = send(socket_client, &packet_size, sizeof(uint32_t),0);
      if (res==-1) {
        printf("[-] Impossible d'envoyer la taille du message au client\n");
        close(socket_client);
        continue;
      }
//Envois de l'annagramme
      for (str_parser=anagram.mot_courant.str, taille_envoyee=0; taille_envoyee<longueur_chaine; ) {
        res = send(socket_client, str_parser, longueur_chaine-taille_envoyee, 0);
        if (res==-1) {
          printf("[-] Impossible d'envoyer le message\n");
          close(socket_client);
          continue;
        }
        taille_envoyee += res;
        str_parser += res;
      }


//Boucle qui consistera a recevoir la reponse du client et a renvoyer un nouvel anagram dans le cas d'une soluiton
      do {

        res = recv(socket_client, &packet_size, sizeof(uint32_t), 0);
        if (res==-1) {
          printf("[-] Erreur reception de la taille\n");
          close(socket_client);
          continue;
        }


        longueur_chaine = ntohl(packet_size);
        if (longueur_chaine > INIT_TAILLE_BUFFER - 1){
          longueur_chaine = INIT_TAILLE_BUFFER - 1;
        }


        for (str_parser=str_buffer, taille_recue=0; taille_recue<longueur_chaine; ) {
          res = recv(socket_client, str_parser, longueur_chaine-taille_recue, 0);
          if (res==-1) {
            printf("[-] Impossible de recevoir le message\n");
            close(socket_client);
            continue;
          }
          else if(res==0){
            printf("[-]Fermeture socket cote client\n");// pas sur de devoir garder ca
          }
          taille_recue += res;
          str_parser += res;
        }


        str_buffer[taille_recue] = '\0';
        if (taille_recue != longueur_chaine) {
          printf("[-] Reception partielle :%s\n", str_buffer);
        }

//Nous regardons ici si la reponse du client et correcte et si oui nous donnons un nouvel anagramme
        if(is_solution (&anagram, str_buffer)){
          /*
          La liste de joueurs, ou chaque joueurs est representer par une structure, a été utiliser pour tenter de "retenir" le score de chaque
          joueurs qui se sont connecter au server, malheureusement malgré mes essais en essayant avec les fonctions pipe() en creant une
          chaine de message, je n'ai pas reussis a faire fonctionner cette partie si du travail. Voila la raison de l'utilisation d'une
          structure et d'une liste de joueurs.
          Sans vouloir etre déplacé, pourriez vous, si ce n'est pas trop demander et si vous avez le temps, me communiquez la solution a ce
          probleme. J'ai passé un temps important sur ce sujet sans solution et je suis curieux de savoir la solution après tout.
          Merci d'avance.
          */
          liste_joueurs[pos_joueurs].score += score_inst;//addition du score
          char ch[INIT_TAILLE_BUFFER];
          sprintf(ch, "Bravo vous avez remporter %d point (total : %d)", score_inst, liste_joueurs[pos_joueurs].score);

          //Envois du message de felicitations
          longueur_chaine = strlen(ch);
          packet_size = htonl(longueur_chaine);

          res = send(socket_client, &packet_size, sizeof(uint32_t),0);
          if (res==-1) {
            printf("[-] Impossible d'envoyer la taille du message au client\n");
            close(socket_client);
            continue;
          }

          for (str_parser=ch, taille_envoyee=0; taille_envoyee<longueur_chaine; ) {
            res = send(socket_client, str_parser, longueur_chaine-taille_envoyee, 0);
            if (res==-1) {
              printf("[-] Impossible d'envoyer le message\n");
              close(socket_client);
              continue;
            }
            taille_envoyee += res;
            str_parser += res;
          }

          //Initialisation du nouvel anagramme et envois de celui ci
          ret_val = new_anagram (&anagram, &dico);
          if (ret_val == -1){
              perror ("[-] Erreur création d'un nouvel anagramme");
              free_anagram (&anagram);
              free_dico (&dico);

              return EXIT_FAILURE;
          }
          longueur_chaine = strlen(anagram.mot_courant.str);
          score_inst = longueur_chaine;
          packet_size = htonl(longueur_chaine);

          res = send(socket_client, &packet_size, sizeof(uint32_t),0);
          if (res==-1) {
            printf("[-] Impossible d'envoyer la taille du message au client\n");
            close(socket_client);
            continue;
          }

          for (str_parser=anagram.mot_courant.str, taille_envoyee=0; taille_envoyee<longueur_chaine; ) {
            res = send(socket_client, str_parser, longueur_chaine-taille_envoyee, 0);
            if (res==-1) {
              printf("[-] Impossible d'envoyer le message\n");
              close(socket_client);
              continue;
            }
            taille_envoyee += res;
            str_parser += res;
          }
        }
        //Processus enfant interrompu dans le cas ou le client ce deconnecte
        if(strcmp(str_buffer, "!quit") == 0){
          printf("[+] Deconnection client %s:%d\n", inet_ntoa(adresse_client.sin_addr), ntohs(adresse_client.sin_port));
          continue_loop = 0;
        }
      } while(continue_loop);
      close(socket_client);
		}
  }
  close(local_socket);
  free(liste_joueurs);
  return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

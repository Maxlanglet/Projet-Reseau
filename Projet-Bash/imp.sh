#!/bin/bash
#Maxime Langlet 000427821

[ "$#" -ne "4" ] && echo "Mauvais nombre d'arguments" >&2 && exit 1

#repertoire
[ ! -e "${1}" ] && echo "Chemin du dossier repertoire incorrect" >&2 && exit 1

# aborescence cible
[ ! -e "${2}" ] && mkdir ${2}

# repertoire poubelle
[ ! -e "${3}" ] && mkdir ${3}


[ ! -d "${1}" ] && echo "${1} n'est pas un dossier" >&2 && exit 0

#Si notre fichier n'existe pas, on crée le fichier de conflits, s'assuer qu'il faut bien faire ca
[ ! -e "${4}" ] && touch ${4}

#Reinitialise le fichier de conflits
[ -e "${4}" ] && echo > "${4}" && echo "Conflits entre les fichiers: " > "${4}"


#Quelques variables que nous utiliserons plus tard
dir_a_explorer="$1"
dir_cible="$2"
dir_conflit="$4"
dir_poubelle="$3"
dir_temporaire=""

joueur_noir=""
couleur_noir=""
joueur_blanc=""
couleur_blanc=""
joueur_noir2=""
joueur_blanc2=""
date=""
round=""
resultat=""
resultat_blanc=""
resultat_noir=""
#fonction qui renomera le fichier pgn que nous copierons
function rename_file() {
  couleur="$1"
  nom_adversaire="$2"
  date="$3"
  round="$4"
  resultat="$5"
  file="$6"
  dinit="$7" #directoire initial
  dir="$8" #directoire dans lequel se trouve le fichier a renommer
  cd ${dir}
  mv $6 ${1}_${2}_${3}_${4}_${5}.pgn
  cd ${dinit}
  return 0
}
#fonction qui crée un dossier étant donné un nom
function create_dir() {
  dinit="$1" #directoire dans lequel on est
  dir="$2" #dir ou on veut le creer
  nom_du_joueur="$3" #nom du directoire
  cd ${dir}
  mkdir ${nom_du_joueur}
  cd ${dinit}
  return 0
}
#Notre fonction récursive
function test()  {
  local dir_initial="$(pwd)"
  for fichier in *;do

    if [[ ${fichier: -4} == ".pgn" ]]; then
      joueur_noir=`grep "Black" ${fichier}`
      joueur_blanc=`grep "White" ${fichier}`
      round=`grep "Round" ${fichier}`
      resultat=`grep "Result" ${fichier}`
      resultat=`grep "Result" ${fichier}`
      date=`grep "Date" ${fichier}`

      joueur_noir2=$(echo ${joueur_noir} | cut -d'"' -f2)
      joueur_blanc2=$(echo ${joueur_blanc} | cut -d'"' -f2)

      joueur_noir3=(${joueur_noir2})
      joueur_blanc3=(${joueur_blanc2})

      chemin_fichier="$(pwd)/${fichier}"

      if [ ${#joueur_noir3[@]} -ge 2 ]; then nom_noir="${joueur_noir3[0]}-${joueur_noir3[1]}"; else nom_noir=${joueur_noir3}; fi
      if [ ${#joueur_blanc3[@]} -ge 2 ]; then nom_blanc="${joueur_blanc3[0]}-${joueur_blanc3[1]}"; else nom_blanc=${joueur_blanc3}; fi

      round2=$(echo ${round} | cut -d'"' -f2)
      resultat2=$(echo ${resultat} | cut -d'"' -f2)
      date2=$(echo ${date} | cut -d'"' -f2)
      if [[ ${resultat2} == "1-0" ]]; then
        resultat_blanc="G"
        resultat_noir="D"
      elif [[ ${resultat2} == "0-1" ]]; then
        resultat_blanc="D"
        resultat_noir="G"
      else
        resultat_blanc="N"
        resultat_noir="N"
      fi


      cd ${dir_cible}
      #Attention peut etre aucune extension a voir
      if [ -f ${nom_noir}.* ]; then
        #echo "${nom_noir} noir"
        mv ${nom_noir}.* ${dir_poubelle}
      fi
      if [ -f ${nom_noir} ]; then
        #echo "${nom_noir} noir"
        mv ${nom_noir} ${dir_poubelle}
      fi
      if [ -d "${nom_noir}" ]; then
        cd ${nom_noir}
        dir_temporaire="$(pwd)"
        nom="Noir_${nom_blanc}_${date2}_${round2}_${resultat_noir}.pgn"
        if [ -f "${nom}" ]; then
          echo ${chemin_fichier} ">>" ${dir_temporaire}"/"${nom}>> "${dir_conflit}"
          cd ${dir_initial}
        else
          cd ${dir_initial}
          cp ${fichier} ${dir_temporaire}
          cd ${dir_temporaire}
          rename_file $"Noir" ${nom_blanc} ${date2} ${round2} ${resultat_noir} ${fichier} ${dir_initial} ${dir_temporaire}
          cd ${dir_initial}
        fi
      else
        create_dir ${dir_initial} ${dir_cible} ${nom_noir}
        cd ${dir_cible}
        cd ${nom_noir}
        dir_temporaire="$(pwd)"
        cd ${dir_initial}
        cp ${fichier} ${dir_temporaire}
        cd ${dir_temporaire}
        rename_file $"Noir" ${nom_blanc} ${date2} ${round2} ${resultat_noir} ${fichier} ${dir_initial} ${dir_temporaire}
        cd ${dir_initial}
      fi
      cd ${dir_initial}

      cd ${dir_cible}
      if [ -f ${nom_blanc}.* ]; then
        #echo "${nom_blanc} blanc"
        mv ${nom_blanc}.* ${dir_poubelle}
      fi
      if [ -f ${nom_blanc} ]; then
        #echo "${nom_blanc} blanc"
        mv ${nom_blanc} ${dir_poubelle}
      fi
      if [ -d "${nom_blanc}" ]; then
        cd ${nom_blanc}
        dir_temporaire="$(pwd)"
        nom="Blanc_${nom_noir}_${date2}_${round2}_${resultat_blanc}.pgn"
        if [ -f "${nom}" ]; then
          echo ${chemin_fichier} ">>" ${dir_temporaire}"/"${nom}>> "${dir_conflit}"
          cd ${dir_initial}
        else
          cd ${dir_initial}
          cp ${fichier} ${dir_temporaire}
          cd ${dir_temporaire}
          rename_file $"Blanc" ${nom_noir} ${date2} ${round2} ${resultat_blanc} ${fichier} ${dir_initial} ${dir_temporaire}
          cd ${dir_initial}
        fi
      else
        create_dir ${dir_initial} ${dir_cible} ${nom_blanc}
        cd ${dir_cible}
        cd ${nom_blanc}
        dir_temporaire="$(pwd)"
        cd ${dir_initial}
        cp ${fichier} ${dir_temporaire}
        cd ${dir_temporaire}
        rename_file $"Blanc" ${nom_noir} ${date2} ${round2} ${resultat_blanc} ${fichier} ${dir_initial} ${dir_temporaire}
        cd ${dir_initial}
      fi
      cd ${dir_initial}
    fi
  done

  for fichier in *;do
    [ -d "${fichier}" ] && cd "${fichier}" && test && cd "${dir_initial}"
    #if [ -d "${fichier}" ]; then
        #cd "${fichier}"
        #test
        #cd "${dir_initial}"
    #fi
  done
  return 0
}

cd "${dir_a_explorer}" && test

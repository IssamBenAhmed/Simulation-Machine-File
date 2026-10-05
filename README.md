# Simulation Stochastique d'une File d'Attente M/M/1

> Projet d'ingénierie et de simulation système — **ISIMA (Clermont Auvergne INP)**, 2ème année (ZZ2).

Cette application propose une simulation événementielle discrète d'une file d'attente à un guichet unique de type **M/M/1** (loi de Poisson pour les arrivées, loi exponentielle pour les durées de service, discipline de service FIFO).  
Elle intègre une interface graphique développée en **C++ / C++/CLI (Windows Forms)** sous Visual Studio permettant la configuration interactive des paramètres stochastiques et l'analyse des métriques en temps réel.

---

## 📊 Modélisation Mathématique

Le système modélise le fonctionnement classique d'un service (guichet de poste, serveur de traitement réseau, caisse) :
- **Taux d'arrivée ($\lambda$) :** Intervalle moyen entre les arrivées successives des entités.
- **Taux de service ($\mu$) :** Durée moyenne nécessaire au traitement d'une entité au guichet.
- **Taux d'intensité du trafic :** $\rho = \frac{\lambda}{\mu}$.
- **Métriques calculées :**
  - Nombre moyen d'entités dans la file et dans le système en fonction du temps.
  - Temps d'attente moyen par entité.
  - Taux d'occupation effectif de la ressource serveur.

---

## 🖥️ Fonctionnalités du Logiciel

- **Saisie dynamique des paramètres :**
  - Durée totale de la simulation (en unités de temps discrètes).
  - Temps moyen d'inter-arrivée.
  - Temps moyen de traitement.
- **Visualisation et Journalisation :**
  - Affichage console / RichTextBox des événements en temps réel (arrivées, débuts de service, départs).
  - Traçage des courbes d'évolution du nombre d'entités dans le système.
  - Calcul et affichage des statistiques agrégées en fin d'exécution.

---

## 🛠️ Environnement & Technologies

- **Langage :** C++ / C++/CLI
- **Framework Graphique :** Windows Forms (.NET Framework)
- **Environnement de développement :** Microsoft Visual Studio 2022
- **Architecture :** Séparation du moteur de simulation stochastique (`simuler_avec_parametres`) et de la couche de présentation graphique (`form_main.h`).

---

## 🚀 Compilation et Exécution

1. Ouvrir le fichier solution `ConsoleApplication1.sln` avec **Visual Studio 2022**.
2. S'assurer que la charge de travail **« Développement Desktop en C++ »** avec le composant **« Prise en charge de C++/CLI »** est installée.
3. Sélectionner la configuration `Debug` ou `Release` en `x64`.
4. Compiler et lancer (`F5` ou `Ctrl+F5`).

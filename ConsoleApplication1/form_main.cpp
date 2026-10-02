#include "stdafx.h"
#include "form_main.h"

#include <iomanip>
#include <sstream>

gcroot<System::Windows::Forms::RichTextBox^> richTextBox1;

static void ecrire_texte(const std::string& texte)
{
	if (richTextBox1.operator->() != nullptr)
	{
		richTextBox1->AppendText(gcnew System::String(texte.c_str()));
	}
}

void initfile(t_file& f)
{
	f.debut = 0;
	f.fin = 0;
	f.nb_piece = 0;
}

void initmachine(t_machine& m)
{
	m.etat = 0;
	m.DPE = 0;
	m.contenu.identifiant = -1;
	m.contenu.date_entree_systeme = 0;
	m.contenu.date_acces_serveur = 0;
	m.contenu.date_fin_serveur = 0;
	m.contenu.etat = "vide";
	m.contenu.lieu = "machine";
}

void initsortie(t_sortie& s)
{
	s.nb_piece = 0;
}

void initentree(t_entree& e)
{
	e.nb_piece = 0;
}

void ajouterfile(t_file& f, const t_piece& p)
{
	if (f.nb_piece >= taillefile)
	{
		std::ostringstream oss;
		oss << "[t=" << p.date_entree_systeme << "] file pleine, client " << p.identifiant << " refuse\n\n";
		ecrire_texte(oss.str());
		return;
	}

	f.liste[f.fin] = p;
	f.fin = (f.fin + 1) % taillefile;
	++f.nb_piece;
}

bool retirerfile(t_file& f, t_piece& p)
{
	if (f.nb_piece == 0)
	{
		return false;
	}

	p = f.liste[f.debut];
	f.debut = (f.debut + 1) % taillefile;
	--f.nb_piece;
	return true;
}

void ajoutermachine(t_machine& m, t_piece& p, int t, int temps_service)
{
	p.date_acces_serveur = t;
	p.etat = "en_service";
	p.lieu = "machine";
	m.contenu = p;
	m.etat = 1;
	m.DPE = t + temps_service;
}

void ajoutermachine(t_machine& m, t_piece& p, int t)
{
	ajoutermachine(m, p, t, tempsmachine);
}

bool retirer_machine(t_machine& m, t_piece& p, int t)
{
	if (m.etat == 0)
	{
		return false;
	}

	p = m.contenu;
	p.date_fin_serveur = t;
	p.etat = "termine";
	p.lieu = "sortie";
	m.etat = 0;
	m.DPE = 0;
	m.contenu.identifiant = -1;
	m.contenu.etat = "vide";
	m.contenu.lieu = "machine";
	return true;
}

void deposersortie(t_sortie& s, const t_piece& p)
{
	if (s.nb_piece >= maxp)
	{
		return;
	}

	s.liste[s.nb_piece] = p;
	++s.nb_piece;
}

void log_client(const t_piece& p, int t, const std::string& action)
{
	std::ostringstream oss;
	oss << "[t=" << std::setw(2) << t << "] client " << std::setw(2) << p.identifiant
		<< "  |  etat = " << std::setw(11) << p.etat
		<< "  |  lieu = " << std::setw(8) << p.lieu;

	if (!action.empty())
	{
		oss << "  |  " << action;
	}

	oss << "\n\n";
	ecrire_texte(oss.str());
}

void simuler_avec_parametres(int duree_simu, int interarrivee, int duree_traitement, std::vector<std::pair<int, int>>& points_systeme)
{
	points_systeme.clear();
	t_entree entree;
	t_file file;
	t_machine machine;
	t_sortie sortie;

	initfile(file);
	initmachine(machine);
	initsortie(sortie);
	initentree(entree);

	if (interarrivee <= 0) interarrivee = 2;
	if (duree_traitement <= 0) duree_traitement = 4;
	if (duree_simu <= 0) duree_simu = 32;

	{
		std::ostringstream oss;
		oss << "========================================\n\n";
		oss << "           DEBUT DE SIMULATION          \n\n";
		oss << "========================================\n\n";
		oss << "Duree de simulation : " << duree_simu << "\n\n"
			<< "Interarrivee        : " << interarrivee << "\n\n"
			<< "Temps de service    : " << duree_traitement << "\n\n";
		oss << "----------------------------------------\n\n";
		ecrire_texte(oss.str());
	}

	int nb_arrives = 0;
	int nb_refuses = 0;
	int prochain_arrivee = 0;
	std::vector<t_piece> clients_termines;

	for (int horloge = 0; horloge <= duree_simu; ++horloge)
	{
		// 1. Arrivee des clients a l'instant horloge
		while (prochain_arrivee <= duree_simu && prochain_arrivee == horloge)
		{
			++nb_arrives;
			t_piece client;
			client.identifiant = nb_arrives;
			client.date_entree_systeme = horloge;
			client.date_acces_serveur = -1;
			client.date_fin_serveur = -1;
			client.etat = "attente";
			client.lieu = "file";

			if (entree.nb_piece < maxp)
			{
				entree.liste[entree.nb_piece] = client;
				++entree.nb_piece;
			}

			log_client(client, horloge, "arrivee");

			int nb_avant = file.nb_piece;
			ajouterfile(file, client);
			if (file.nb_piece == nb_avant)
			{
				++nb_refuses;
			}
			prochain_arrivee += interarrivee;
		}

		// 2. Fin de service sur la machine a l'instant horloge
		if (machine.etat == 1 && machine.DPE == horloge)
		{
			t_piece termine;
			if (retirer_machine(machine, termine, horloge))
			{
				log_client(termine, horloge, "fin de traitement");
				deposersortie(sortie, termine);
				clients_termines.push_back(termine);
			}
		}

		// 3. Debut de service si machine disponible
		if (machine.etat == 0)
		{
			t_piece suivant;
			if (retirerfile(file, suivant))
			{
				ajoutermachine(machine, suivant, horloge, duree_traitement);
				log_client(machine.contenu, horloge, "debut de traitement");
			}
		}

		int clients_systeme = file.nb_piece + (machine.etat == 1 ? 1 : 0);
		points_systeme.push_back(std::make_pair(horloge, clients_systeme));
	}

	{
		std::ostringstream oss;
		oss << "----------------------------------------\n\n";
		oss << "     FIN DE SIMULATION (t = " << duree_simu << ")    \n\n";
		oss << "----------------------------------------\n\n";
		oss << "Clients arrives   : " << nb_arrives << "\n\n";
		oss << "Clients servis    : " << clients_termines.size() << "\n\n";
		oss << "En cours machine  : " << (machine.etat == 1 ? 1 : 0) << "\n\n";
		oss << "En file d'attente : " << file.nb_piece << "\n\n";
		if (nb_refuses > 0)
		{
			oss << "Clients refuses   : " << nb_refuses << " (file pleine)\n\n";
		}
		oss << "--- Recapitulatif des clients servis ---\n\n";
		ecrire_texte(oss.str());
	}

	for (size_t i = 0; i < clients_termines.size(); ++i)
	{
		const t_piece& c = clients_termines[i];
		std::ostringstream oss;
		oss << "Client " << std::setw(2) << c.identifiant
			<< "  |  entree = " << std::setw(2) << c.date_entree_systeme
			<< "  |  acces machine = " << std::setw(2) << c.date_acces_serveur
			<< "  |  sortie = " << std::setw(2) << c.date_fin_serveur
			<< "  |  temps total = " << std::setw(2) << (c.date_fin_serveur - c.date_entree_systeme)
			<< "\n\n";
		ecrire_texte(oss.str());
	}

	if (machine.etat == 1)
	{
		std::ostringstream oss;
		oss << "Client " << std::setw(2) << machine.contenu.identifiant
			<< "  |  entree = " << std::setw(2) << machine.contenu.date_entree_systeme
			<< "  |  acces machine = " << std::setw(2) << machine.contenu.date_acces_serveur
			<< "  |  (en cours de traitement sur machine, fin prevue a t=" << machine.DPE << ")\n\n";
		ecrire_texte(oss.str());
	}

	if (file.nb_piece > 0)
	{
		std::ostringstream oss;
		oss << file.nb_piece << " client(s) en attente dans la file au moment de l'arret.\n\n";
		ecrire_texte(oss.str());
	}
}

void simuler()
{
	std::vector<std::pair<int, int>> dummy;
	simuler_avec_parametres(32, 2, tempsmachine, dummy);
}

void simuler_arrivee_simultanee()
{
	t_entree entree;
	t_file file;
	t_machine machine;
	t_sortie sortie;

	initfile(file);
	initmachine(machine);
	initsortie(sortie);
	initentree(entree);

	entree.nb_piece = 8;
	for (int i = 0; i < entree.nb_piece; ++i)
	{
		entree.liste[i].identifiant = i + 1;
		entree.liste[i].date_entree_systeme = 0;
		entree.liste[i].date_acces_serveur = -1;
		entree.liste[i].date_fin_serveur = -1;
		entree.liste[i].etat = "arrive";
		entree.liste[i].lieu = "entree";
	}

	{
		std::ostringstream oss;
		oss << "--- debut simulation avec arrivee simultanee ---\n";
		ecrire_texte(oss.str());
	}

	int horloge = 0;
	int prochain_client = 0;
	int nb_refuses = 0;
	const int HORLOGE_MAX = 50000;

	while ((sortie.nb_piece + nb_refuses < entree.nb_piece) &&
	       (machine.etat == 1 || file.nb_piece > 0 || prochain_client < entree.nb_piece) &&
	       (horloge < HORLOGE_MAX))
	{
		while (prochain_client < entree.nb_piece && entree.liste[prochain_client].date_entree_systeme == horloge)
		{
			t_piece client = entree.liste[prochain_client];
			client.etat = "attente";
			client.lieu = "file";
			log_client(client, horloge, "arrivee");
			int nb_avant = file.nb_piece;
			ajouterfile(file, client);
			if (file.nb_piece == nb_avant)
			{
				++nb_refuses;
			}
			++prochain_client;
		}

		if (machine.etat == 1 && machine.DPE == horloge)
		{
			t_piece termine;
			if (retirer_machine(machine, termine, horloge))
			{
				log_client(termine, horloge, "fin de traitement");
				deposersortie(sortie, termine);
			}
		}

		if (machine.etat == 0)
		{
			t_piece suivant;
			if (retirerfile(file, suivant))
			{
				ajoutermachine(machine, suivant, horloge, tempsmachine);
				log_client(machine.contenu, horloge, "debut de traitement");
			}
		}

		++horloge;
	}

	{
		std::ostringstream oss;
		oss << "\n--- fin simulation ---\n\n";
		oss << "clients traites : " << sortie.nb_piece << "\n\n";
		if (nb_refuses > 0)
		{
			oss << "clients refuses : " << nb_refuses << "\n\n";
		}
		ecrire_texte(oss.str());
	}

	for (int i = 0; i < sortie.nb_piece; ++i)
	{
		const t_piece& c = sortie.liste[i];
		std::ostringstream oss;
		oss << "client " << c.identifiant
			<< "  |  entree = " << c.date_entree_systeme
			<< "  |  acces machine = " << c.date_acces_serveur
			<< "  |  sortie = " << c.date_fin_serveur
			<< "  |  temps total = " << (c.date_fin_serveur - c.date_entree_systeme)
			<< "\n\n";
		ecrire_texte(oss.str());
	}
}

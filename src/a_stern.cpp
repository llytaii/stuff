#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

struct Kante;

// Knoten speichert Name, Koordinaten, optimal gefundene Kosten, Vorgänger und alle Kanten zu anderen Knoten.
struct Knoten{
  Knoten() = delete;

  Knoten(char _name, float _x, float _y, float _z) : name{_name}, x{_x}, y{_y}, z{_z}{};

  char name;
  float x, y, z;
  float kosten;

  Knoten* vorgaenger = nullptr;
  std::vector<Kante> verbindungen;
};

// Kante speichert Start- und Endknoten der Verbindung und berechnet die Kosten
struct Kante{
  Kante() = delete;

  Kante(Knoten* _k1, Knoten* _k2 ) : start{_k1}, end{_k2}
  {
    float x, y, z;
    x = end->x - start->x;
    y = end->y - start->y;
    z = end->z - start->z;

    kosten = std::sqrt(x * x + y * y + z * z);
  };

  float kosten;
  Knoten* start;
  Knoten* end;
};

// Graph nimmt Liste an Knoten und Kanten und initialisiert die Verbindungen per Knoten
struct Graph
{
  Graph() = delete;

  Graph(std::vector<Knoten>& _knoten, std::vector<Kante> _kanten) : knoten{_knoten}
  {
    // setze Verbindungen für jeden Knoten
    for(size_t i = 0; i < _kanten.size(); ++i)
      _kanten[i].start->verbindungen.push_back(_kanten[i]);

    // setze hohe Kosten (eigentlich MAX_INT) und gebe aus
    std::cout << "\nKnoten : erreichbare Knoten\n";
    for(auto& k : knoten)
    {
      k.kosten = 1'000'000;

      // Ausgabe aller erreichbaren Knoten
      std::cout << std::setw(6) << k.name << " : ";
      for(auto& kante : k.verbindungen)
        std::cout << kante.end->name << ' ';
      std::cout << std::endl;
    }
  };

  std::vector<Knoten>& knoten;
};

// Helper Enum für benannte Indizies
enum NAME{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    MAX
};

// dijkstra mit Graph _g und Startknoten _s
std::vector<Knoten*> dijkstra(Graph& _g, NAME _s)
{
  auto& knoten = _g.knoten;
  
  knoten[_s].kosten = 0;

  Knoten* aktueller_knoten;
  std::vector<Knoten*> open_list;
  open_list.push_back(&knoten[_s]);
  std::vector<Knoten*> closed_list;

  while(open_list.size())
  {
    // Knoten mit geringsten Kosten wird aktueller Knoten
    aktueller_knoten = open_list[0];
    open_list.erase(open_list.begin());

    // Kosten update aller Verbindungen des aktuellen Knotens
    for(Kante& kante : aktueller_knoten->verbindungen)
    {
      if(kante.end->kosten > (aktueller_knoten->kosten + kante.kosten))
      {
        kante.end->kosten = aktueller_knoten->kosten + kante.kosten;
        kante.end->vorgaenger = aktueller_knoten;
      }

      // Push back in open_list, falls noch nicht in openlist und closed list
      if(std::find(open_list.begin(), open_list.end(), kante.end) == open_list.end() && std::find(closed_list.begin(), closed_list.end(), kante.end) == closed_list.end())
        open_list.push_back(kante.end);
    }

    // abgehandelten aktuellen Knoten in closed_list
    closed_list.push_back(aktueller_knoten);

    
    // sortieren nach Kosten, aufsteigend
    std::sort(open_list.begin(), open_list.end(), [](Knoten* k1, Knoten* k2){
      return k1->kosten < k2->kosten;
    });
  }

  return closed_list;
}

int main()
{
  std::vector<Knoten> knoten{
    {'A', 12, 0, 2}, 
    {'B', 5, 0, 5},  
    {'C', 20, 0, 5}, 
    {'D', 3, 0, 10}, 
    {'E', 10, 0, 10}, 
    {'F', 16, 0, 10}, 
    {'G', 5, 0, 15}, 
    {'H', 13, 0, 15}, 
    {'I', 20, 0, 13}, 
    {'J', 9, 0, 20}, 
    {'K', 20, 0, 20}, 
  };

  std::vector<Kante> kanten{
    {&knoten[A], &knoten[B]},
    {&knoten[A], &knoten[C]},
    {&knoten[B], &knoten[D]},
    {&knoten[B], &knoten[E]},
    {&knoten[C], &knoten[I]},
    {&knoten[C], &knoten[E]},
    {&knoten[D], &knoten[G]},
    {&knoten[E], &knoten[F]},
    {&knoten[E], &knoten[B]},
    {&knoten[F], &knoten[H]},
    {&knoten[G], &knoten[H]},
    {&knoten[G], &knoten[J]},
    {&knoten[H], &knoten[I]},
    {&knoten[H], &knoten[K]},
    {&knoten[I], &knoten[K]},
  };

  Graph g{knoten, kanten};

  // print closed list
  std::cout << "\nFinale Closed List:\n";
  auto v = dijkstra(g, A);
  for(auto e : v)
    std::cout << "Name: " << e->name << "  Kosten: " << std::setw(7) << e->kosten << "  Vorgänger: " << ((e->vorgaenger) ? e->vorgaenger->name : '0') << std::endl;


  // print shortest pathes
  std::cout << "\nKnoten : billigster Pfad\n";
  for(auto e : v)
  {
    std::cout << std::setw(6) << e->name << " : ";
    Knoten* tmp = e->vorgaenger;
    while(tmp)
    {
      std::cout << tmp->name << ' ';
      tmp = tmp->vorgaenger;
    }
    std::cout << std::endl;
  }
  
  return 0;
}
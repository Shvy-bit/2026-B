// Example program
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;
vector<int> V,W;

/* \ \ \ \ \ / / / / / */
constexpr int CUI = 20251200; //Reemplace por su propio CUI
/* / / / / / \ \ \ \ \ */

constexpr int N_REPS = 1;

/* * * * * * * * DECLARACIONES * * * * * * * */

// MÃ¡quina de generaciÃ³n de nÃºmeros aleatorios
mt19937 Rand (CUI);

// Variables de conteo estadÃ­stico
unsigned long long int cont_comparaciones = 0, cont_escrituras = 0;

// MediciÃ³n de tiempo (en microsegundos) desde transcurrido(true) hasta transcurrido()
typedef uint_fast64_t t_transcurrido; // Definido en microsegundos
constexpr double __MedidaTiempo = 1000000.0;    // Define microsegundos
clock_t __inicio_transcurrido = clock();
inline t_transcurrido transcurrido(bool reiniciar);

inline t_transcurrido transcurrido(bool reiniciar = false) {
  if ( reiniciar ) __inicio_transcurrido = clock();
  return ((__MedidaTiempo*double(clock()-__inicio_transcurrido))/double(CLOCKS_PER_SEC));
};

template < class RandomIt >
void SelectionSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void SelectionSort ( RandomIt b, RandomIt e, Compare comp );

template < class RandomIt >
void HeapSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void HeapSort ( RandomIt b, RandomIt e, Compare comp );
template < class RandomIt, class Compare >
void HeapSiftUp ( RandomIt b, RandomIt e, RandomIt i, Compare comp );

template < class RandomIt >
void InsertionSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void InsertionSort ( RandomIt b, RandomIt e, Compare comp );

template < class RandomIt >
void MergeSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void MergeSort ( RandomIt b, RandomIt e, Compare comp );
template < class RandomIt, class Compare >
void MergeSortC ( RandomIt b, RandomIt e, Compare comp, RandomIt ob );

template < class RandomIt >
void QuickSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void QuickSort ( RandomIt b, RandomIt e, Compare comp );
template < class RandomIt, class Compare >
RandomIt Partition ( RandomIt b, RandomIt e, Compare comp );

template < class RandomIt >
void IntroSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void IntroSort ( RandomIt b, RandomIt e, Compare comp );


typedef void ( *t_ordenamiento ) ( vector<int>::iterator, vector<int>::iterator ); // tipo de funciÃ³n de ordenamiento

template < t_ordenamiento _ordenamiento >
void EvaluaOrdenamiento ( string s_ordenamiento, int n );
void EvaluaOrdenamientos ();


/* * * * * * * * IMPLEMENTACIONES * * * * * * * */

// SELECTION SORT
template < class RandomIt >
void SelectionSort ( RandomIt b, RandomIt e ) {
  SelectionSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void SelectionSort ( RandomIt b, RandomIt e, Compare comp ) {

  // Para todos los elementos (menos el Ãºltimo)
  for (RandomIt s = b; std::distance ( s, e - 1 ) /* > 0 */; s++ ) {

    // Buscar el elemento m con menor (o mayor) llave
    RandomIt m = s;
    for ( RandomIt i = s + 1; std::distance ( i, e ) /* > 0 */; i++ ) {
      cont_comparaciones++;
      if ( comp ( *i, *m ) ) m = i;
    }

    // Remueve m de I para anexarlo en S
    if ( m != s ) {
      cont_escrituras+=3; // swap(a,b) escribe t=a;a=b;b=t;
      swap ( *s, *m );
    }
  }
}


// HEAP SORT Y FUNCIONES DE AYUDA

template < class RandomIt >
void HeapSort ( RandomIt b, RandomIt e ) {
  HeapSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void HeapSort ( RandomIt b, RandomIt e, Compare comp ) {
  // Basado en Floyd (1964) pero con raÃ­z:0; padre_i:(i-1)/2; hijos_i:2*i+1,2*i+2;

  // BottomUpBuildHeap: Construye heap desde el Ãºltimo padre hacia arriba
  for ( RandomIt i = b + ( std::distance ( b, e ) - 2 ) / 2; std::distance ( b, i ) /* > 0 */; --i )
    HeapSiftUp ( b, e, i, comp );
  // Nota: Deja el Ãºltimo SiftUp para ser el primero del siguiente ciclo

  // Repitiendo repara la heap y retira el primer elemento de la heap
  for ( RandomIt i = e; std::distance ( b, i ) > 1; ) {
    HeapSiftUp ( b, i, b, comp );
    cont_escrituras+=3;
    --i; swap ( *i, *b );
  }
}

template < class RandomIt, class Compare >
void HeapSiftUp ( RandomIt b, RandomIt e, RandomIt i, Compare comp ) {
  // Basado en Floyd (1964) pero con raÃ­z:0; padre_i:(i-1)/2; hijos_i:2*i+1,2*i+2;

  // Copia la raiz del sub-Ã¡rbol
  cont_escrituras++;
  auto t = *i;

  // selecciona al primer hijo
  RandomIt c = b + 2*std::distance ( b, i ) + 1;

  // mientras existan hijos
  while ( c < e ) {

    // si son dos hijos, selecciona al mayor hijo
    if ( c + 1 < e ) {
      cont_comparaciones++;
      if ( comp ( *c, *(c+1) ) ) c++;
    }

    // si el mayor hijo es mayor que la raiz
    cont_comparaciones++;
    if ( comp ( t, *c ) ) {
      // cierne, mueve i al lugar donde estaba el hijo mayor
      cont_escrituras++;
      *i = *c;
      i = c;
      // y selecciona al siguiente hijo
      c = b + 2*std::distance ( b, i ) + 1;
    } else break;
  }

  // pone la copia de la raiz vieja en su sitio
  cont_escrituras++;
  *i = t;
}


// INSERTION SORT

template < class RandomIt >
void InsertionSort ( RandomIt b, RandomIt e ) {
  InsertionSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void InsertionSort ( RandomIt b, RandomIt e, Compare comp ) {
  if (!std::distance(b, e)) return;

  for (RandomIt s = b + 1; std::distance(s, e); s++) {
    cont_comparaciones++;
    if (comp(s[-1], *s)) continue;

    RandomIt i = s - 2;
    while(comp(*s, *i)) {
      cont_comparaciones++;
      cont_escrituras++;
      //if (!std::distance(b, i)) break;
      i--; //Bajo la certeza que en la rotación se le aumentara en 1, i puede apuntar a index -1
    };
    cont_escrituras += 2; //Para tener en cuenta el desplazamiento
    std::rotate(i + 1, s, s + 1);
  }
}


// MERGE SORT Y FUNCIONES DE AYUDA

template < class RandomIt >
void MergeSort ( RandomIt b, RandomIt e ) {
  MergeSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void MergeSort ( RandomIt b, RandomIt e, Compare comp ) {
  if ( std::distance ( b, e ) <= 1 ) return;

  // Hace una sola copia y luego llama a la funciÃ³n de ayuda
  typedef typename std::iterator_traits<RandomIt>::value_type ItVT;
  std::vector < ItVT > A ( b, e ); // copia [b,e)
  MergeSortC ( A.begin(), A.end(), comp, b );
}

template < class RandomIt, class Compare >
void MergeSortC ( RandomIt b, RandomIt e, Compare comp, RandomIt ob ) {
  // Recuerde: Ordene la copia existente en [b, m) y [m, e) mezclando en [ ob, ob +{e-b} )
  // Recomiendo calcular primero las posiciones para		RandomIt m, om, oe;
  // No necesita implementar Merge por separado, puede implementarlo al final dentro de esta funciÃ³n
  // IMPLEMENTE AQUÃ

}


// QUICKSORT Y FUNCIONES DE AYUDA

template < class RandomIt >
void QuickSort ( RandomIt b, RandomIt e ) {
  QuickSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void QuickSort ( RandomIt b, RandomIt e, Compare comp ) {

  // Cambia a InsertionSort con threshold 16
  if ( std::distance ( b, e ) <= 16 ) {
    InsertionSort ( b, e, comp );
    return;
  }

  RandomIt m = Partition ( b, e, comp );

  // Resuelve recursivamente ambos lados
  QuickSort ( b, m, comp );
  QuickSort ( m, e, comp );
}

template < class RandomIt, class Compare >
RandomIt Partition ( RandomIt b, RandomIt e, Compare comp ) {
    // Seleccione el pivote p como la mediana de tres (primero, medio, Ãºltimo)
    cont_escrituras++;
    auto p = *b;
    // IMPLEMENTE AQUI

    // Use la particiÃ³n eficiente de Hoare
    // Parta los elementos en [b, e) segÃºn el pivote p
    // Devuelva el punto medio m para las siguientes recursiones
}


// INTROSORT Y FUNCIONES DE AYUDA

template < class RandomIt >
void IntroSort ( RandomIt b, RandomIt e ) {
  IntroSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void IntroSort ( RandomIt b, RandomIt e, Compare comp ) {
  // Reutilice la implementaciÃ³n de Partition de Quicksort
  // Cree las funciones de ayuda adicionales que necesite
  // IMPLEMENTE AQUÃ

}


template < t_ordenamiento _ordenamiento >
void EvaluaOrdenamiento ( string s_ordenamiento ) {
  V = W;
  cout << s_ordenamiento << '\t' << V.size() << '\t';
  // Reinicia
  cont_comparaciones = cont_escrituras = 0;
  transcurrido(true);
  _ordenamiento (V.begin(), V.end());
  cout << transcurrido() << '\t';
  cout << cont_comparaciones << '\t';
  cout << cont_escrituras << '\t';
  cout << 2*cont_comparaciones + cont_escrituras << endl;


  // Unit Test: verifica si ordena bien
  for(auto i=V.begin()+1;i<V.end();i++) if (*(i-1)!=*i-1) {
    cout << "ALGO ANDA MAL, NO ORDENA BIEN!!!\n";
    for ( auto &i: V ) cout << i << ", ";
    cout << endl;
    exit(1);
  }
}

void EvaluaOrdenamientos ( ) {
  //Inicia pruebas
  // vector<int> T = {4096,32768,262144,2097152,16777216,134217728,1073741824};
  vector<int> T = {16,64,256,1024,4096,16384,65536};
  Rand.seed(CUI);
  cout << "Algo.\tN\ttiempo\tcomps.\tescrts.\tlects." << endl;
  for ( int i = N_REPS; i /* > 0 */; --i ) for ( auto t : T ) {
    W.resize(t);
    iota ( W.begin(), W.end(), 0 );
    shuffle ( W.begin(), W.end(), Rand );

    EvaluaOrdenamiento<&SelectionSort>("Sel");
    EvaluaOrdenamiento<&HeapSort>("Heap");
    EvaluaOrdenamiento<&InsertionSort>("Ins");
    // EvaluaOrdenamiento<&MergeSort>("Merge");
    // EvaluaOrdenamiento<&QuickSort>("Quick");
    // EvaluaOrdenamiento<&IntroSort>("Intro");
  }
}

int main() {
  EvaluaOrdenamientos();
}